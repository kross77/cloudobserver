#include "observer_writer.h"

observer_writer::observer_writer(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump)
	: HEADER_LENGTH(13), SIGNATURE1(0x46), SIGNATURE2(0x4C), SIGNATURE3(0x56),
	VERSION(1), TAG_HEADER_LENGTH(11), TAGTYPE_AUDIO(8), TAGTYPE_VIDEO(9), TAGTYPE_DATA(18)
{
	this->socket = socket;
	this->dump = dump;

	this->width = 320;
	this->height = 240;

	this->header = NULL;
	this->buffered_timestamp = 0;
	this->key_frames = false;
}

observer_writer::~observer_writer()
{
	this->socket->close();

	if (this->dump != NULL)
	{
		this->dump->close();
		delete dump;
	}

	for (std::set<observer_reader*>::iterator i = this->readers.begin(); i != this->readers.end(); ++i)
		delete *i;

	delete[] this->header;

	for (std::vector<std::pair<char*, int> >::iterator i = this->script_data.begin(); i != this->script_data.end(); ++i)
		delete[] i->first;
	this->script_data.clear();

	for (std::vector<std::pair<char*, int> >::iterator i = this->tags_buffer.begin(); i != this->tags_buffer.end(); ++i)
		delete[] i->first;
	this->tags_buffer.clear();
}

void observer_writer::connect_reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump)
{
	boost::mutex::scoped_lock lock(this->mutex);
	socket->send(boost::asio::buffer(this->header, HEADER_LENGTH));
	if (dump != NULL)
		dump->write(this->header, HEADER_LENGTH);
	for (std::vector<std::pair<char*, int> >::iterator i = this->script_data.begin(); i != this->script_data.end(); ++i)
	{
		socket->send(boost::asio::buffer(i->first, i->second));
		if (dump != NULL)
			dump->write(i->first, i->second);
	}

	bool tag_header = true;
	for (std::vector<std::pair<char*, int> >::iterator i = this->tags_buffer.begin(); i != this->tags_buffer.end(); ++i)
	{
		if (tag_header)
		{
			// Get timestamp.
			unsigned int timestamp = to_ui24((unsigned char*)i->first, 4);
			// Update timestamp.
			unsigned int modified_timestamp = timestamp - this->buffered_timestamp;
			char* modified_timestamp_ptr = (char*)(&modified_timestamp);

			char* modified_tag_header = new char[TAG_HEADER_LENGTH];
			memcpy(modified_tag_header, i->first, TAG_HEADER_LENGTH);
			modified_tag_header[4] = modified_timestamp_ptr[2];
			modified_tag_header[5] = modified_timestamp_ptr[1];
			modified_tag_header[6] = modified_timestamp_ptr[0];

			socket->send(boost::asio::buffer(modified_tag_header, TAG_HEADER_LENGTH));
			if (dump != NULL)
				dump->write(modified_tag_header, TAG_HEADER_LENGTH);

			delete[] modified_tag_header;
		}
		else
		{
			socket->send(boost::asio::buffer(i->first, i->second));
			if (dump != NULL)
				dump->write(i->first, i->second);
		}

		tag_header = !tag_header;
	}
	this->readers.insert(new observer_reader(socket, dump, this->buffered_timestamp));
}

void observer_writer::process()
{
	try
	{
		// FLV header
		this->header = new char[HEADER_LENGTH];
		boost::asio::read(*this->socket, boost::asio::buffer(this->header, HEADER_LENGTH));
		if (this->dump != NULL)
			this->dump->write(this->header, HEADER_LENGTH);
		// Signature
		if ((SIGNATURE1 != this->header[0]) || (SIGNATURE2 != this->header[1]) || (SIGNATURE3 != this->header[2]))
			throw flv_format_violation_exception();
		// Version
		if (VERSION != this->header[3])
			throw flv_format_violation_exception();
		// TypeFlags
		if (0 != (this->header[4] >> 3))
			throw flv_format_violation_exception();
		//bool audio = (((this->header[4] & 0x4) >> 2) == 1);
		if (0 != ((this->header[4] & 0x2) >> 1))
			throw flv_format_violation_exception();
		//bool video = ((this->header[4] & 0x1) == 1);
		// DataOffset
		unsigned int data_offset = to_ui32((unsigned char*)this->header, 5);
		// PreviousTagSize0
		if (0 != to_ui32((unsigned char*)this->header, 9))
			throw flv_format_violation_exception();

		// FLV body
		while (this->socket->is_open())
		{
			// FLV tag header
			char* tag_header = new char[TAG_HEADER_LENGTH];
			boost::asio::read(*this->socket, boost::asio::buffer(tag_header, TAG_HEADER_LENGTH));
			if (this->dump != NULL)
				this->dump->write(tag_header, TAG_HEADER_LENGTH);
			// TagType
			if ((tag_header[0] != TAGTYPE_AUDIO) && (tag_header[0] != TAGTYPE_VIDEO) && (tag_header[0] != TAGTYPE_DATA))
				throw flv_format_violation_exception();
			// DataSize
			unsigned int data_size = to_ui24((unsigned char*)tag_header, 1) + 4;
			// Timestamp
			unsigned int timestamp = to_ui24((unsigned char*)tag_header, 4);
			// TimestampExtended
			//unsigned int timestamp_extended = tagHeader[7];
			// StreamID
			if (0 != to_ui24((unsigned char*)tag_header, 8))
				throw flv_format_violation_exception();
			// Data
			char* tag_data = new char[data_size];
			boost::asio::read(*this->socket, boost::asio::buffer(tag_data, data_size));
			if (this->dump != NULL)
				this->dump->write(tag_data, data_size);

			boost::mutex::scoped_lock lock(this->mutex);
			if ((tag_header[0] == TAGTYPE_VIDEO) && (1 == (tag_data[0] & 0xF0) >> 4))
			{
				this->key_frames = true;
				for (std::vector<std::pair<char*, int> >::iterator i = this->tags_buffer.begin(); i != this->tags_buffer.end(); ++i)
					delete[] i->first;
				this->tags_buffer.clear();
				this->buffered_timestamp = timestamp;
			}

			if (tag_header[0] == TAGTYPE_DATA)
			{
				this->width = (int)get_double_variable_from_flv_script_tag(tag_data, data_size, "width");
				this->height = (int)get_double_variable_from_flv_script_tag(tag_data, data_size, "height");

				this->script_data.push_back(std::pair<char*, int>(tag_header, TAG_HEADER_LENGTH));
				this->script_data.push_back(std::pair<char*, int>(tag_data, data_size));
			}

			if (this->key_frames)
			{
				this->tags_buffer.push_back(std::pair<char*, int>(tag_header, TAG_HEADER_LENGTH));
				this->tags_buffer.push_back(std::pair<char*, int>(tag_data, data_size));
			}
			else
				this->buffered_timestamp = timestamp;

			std::set<observer_reader*> disconnected_readers;
			for (std::set<observer_reader*>::iterator i = this->readers.begin(); i != this->readers.end(); ++i)
			{
				// Update timestamp.
				unsigned int modified_timestamp = timestamp - (*i)->timestamp_delta;
				char* modified_timestamp_ptr = (char*)(&modified_timestamp);

				char* modified_tag_header = new char[TAG_HEADER_LENGTH];
				memcpy(modified_tag_header, tag_header, TAG_HEADER_LENGTH);
				modified_tag_header[4] = modified_timestamp_ptr[2];
				modified_tag_header[5] = modified_timestamp_ptr[1];
				modified_tag_header[6] = modified_timestamp_ptr[0];

				// Write tag.
				try
				{
					(*i)->socket->send(boost::asio::buffer(modified_tag_header, TAG_HEADER_LENGTH));
					(*i)->socket->send(boost::asio::buffer(tag_data, data_size));
					if ((*i)->dump != NULL)
					{
						(*i)->dump->write(modified_tag_header, TAG_HEADER_LENGTH);
						(*i)->dump->write(tag_data, data_size);
					}
				}
				catch (boost::system::system_error &e)
				{
					std::cout << "Cloud Service: Reader connection was closed." << std::endl;
					delete *i;
					disconnected_readers.insert(*i);
				}

				delete[] modified_tag_header;
			}

			for (std::set<observer_reader*>::iterator i = disconnected_readers.begin(); i != disconnected_readers.end(); ++i)
				this->readers.erase(*i);

			if (!this->key_frames && (tag_header[0] != TAGTYPE_DATA))
			{
				delete[] tag_header;
				delete[] tag_data;
			}
		}
	}
	catch (boost::system::system_error)
	{
		std::cout << "Cloud Service: Writer connection was closed." << std::endl;
	}
	catch (flv_format_violation_exception)
	{
		std::cout << "Cloud Service: FLV format violation exception was thrown." << std::endl;
	}
}

double observer_writer::get_double_variable_from_flv_script_tag(char* script_tag_data, int data_size, std::string variable_name)
{
	char* script_data = new char[data_size + 1];
	for (int i = 0; i < data_size; ++i)
		script_data[i] = script_tag_data[i] == '\0' ? ' ' : script_tag_data[i];
	script_data[data_size] = '\0';
	std::string tag_data(script_data);
	delete[] script_data;

	int index = tag_data.find(variable_name) + variable_name.length() + 1;
	double result;
	char* reversed = (char*)(&result);
	for (int i = 0; i < 8; ++i)
		reversed[7 - i] = script_tag_data[index + i];
	return result;
}

unsigned short observer_writer::to_ui16(unsigned char* value, int start_index)
{
	return (unsigned short)(value[start_index] << 8 | value[start_index + 1]);
}

unsigned int observer_writer::to_ui24(unsigned char* value, int start_index)
{
	return (unsigned int)(value[start_index] << 16 | value[start_index + 1] << 8 | value[start_index + 2]);
}

unsigned int observer_writer::to_ui32(unsigned char* value, int start_index)
{
	return (unsigned int)(value[start_index] << 24 | value[start_index + 1] << 16 | value[start_index + 2] << 8 | value[start_index + 3]);
}
