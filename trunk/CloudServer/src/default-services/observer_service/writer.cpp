#include "writer.h"

using namespace std;

writer::writer(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, ofstream* dump) : socket(socket), dump(dump), width(320), height(240), header(NULL), buffered_timestamp(0), key_frames(false), HEADER_LENGTH(13), SIGNATURE1(0x46), SIGNATURE2(0x4C), SIGNATURE3(0x56), VERSION(1), TAG_HEADER_LENGTH(11), TAGTYPE_AUDIO(8), TAGTYPE_VIDEO(9), TAGTYPE_DATA(18) { }

writer::~writer()
{
	socket->close();

	if (dump != NULL)
	{
		dump->close();
		delete dump;
	}

	for (set<reader*>::iterator i = readers.begin(); i != readers.end(); ++i)
		delete *i;

	delete[] header;

	for (vector<flv_tag>::iterator i = script_data.begin(); i != script_data.end(); ++i)
	{
		delete[] i->header;
		delete[] i->data;
	}
	script_data.clear();

	for (vector<flv_tag>::iterator i = tags_buffer.begin(); i != tags_buffer.end(); ++i)
	{
		delete[] i->header;
		delete[] i->data;
	}
	tags_buffer.clear();
}

void writer::connect_reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, ofstream* dump)
{
	boost::mutex::scoped_lock lock(mutex);
	socket->send(boost::asio::buffer(header, HEADER_LENGTH));
	if (dump != NULL)
		dump->write(header, HEADER_LENGTH);
	for (vector<flv_tag>::iterator i = script_data.begin(); i != script_data.end(); ++i)
	{
		socket->send(boost::asio::buffer(i->header, TAG_HEADER_LENGTH));
		socket->send(boost::asio::buffer(i->data, i->data_size));
		if (dump != NULL)
		{
			dump->write(i->header, TAG_HEADER_LENGTH);
			dump->write(i->data, i->data_size);
		}
	}

	for (vector<flv_tag>::iterator i = tags_buffer.begin(); i != tags_buffer.end(); ++i)
	{
		// Get timestamp.
		unsigned int timestamp = to_ui24((unsigned char*)i->header, 4);
		// Update timestamp.
		unsigned int modified_timestamp = timestamp - buffered_timestamp;
		char* modified_timestamp_ptr = (char*)(&modified_timestamp);

		char* modified_tag_header = new char[TAG_HEADER_LENGTH];
		memcpy(modified_tag_header, i->header, TAG_HEADER_LENGTH);
		modified_tag_header[4] = modified_timestamp_ptr[2];
		modified_tag_header[5] = modified_timestamp_ptr[1];
		modified_tag_header[6] = modified_timestamp_ptr[0];

		socket->send(boost::asio::buffer(modified_tag_header, TAG_HEADER_LENGTH));
		socket->send(boost::asio::buffer(i->data, i->data_size));
		if (dump != NULL)
		{
			dump->write(modified_tag_header, TAG_HEADER_LENGTH);
			dump->write(i->data, i->data_size);
		}

		delete[] modified_tag_header;
	}
	readers.insert(new reader(socket, dump, buffered_timestamp));
}

void writer::process()
{
	try
	{
		// FLV header
		header = new char[HEADER_LENGTH];
		boost::asio::read(*socket, boost::asio::buffer(header, HEADER_LENGTH));
		if (dump != NULL)
			dump->write(header, HEADER_LENGTH);
		// Signature
		if ((SIGNATURE1 != header[0]) || (SIGNATURE2 != header[1]) || (SIGNATURE3 != header[2]))
			throw flv_format_violation_exception();
		// Version
		if (VERSION != header[3])
			throw flv_format_violation_exception();
		// TypeFlags
		if (0 != (header[4] >> 3))
			throw flv_format_violation_exception();
		//bool audio = (((header[4] & 0x4) >> 2) == 1);
		if (0 != ((header[4] & 0x2) >> 1))
			throw flv_format_violation_exception();
		//bool video = ((header[4] & 0x1) == 1);
		// DataOffset
		unsigned int data_offset = to_ui32((unsigned char*)header, 5);
		// PreviousTagSize0
		if (0 != to_ui32((unsigned char*)header, 9))
			throw flv_format_violation_exception();

		// FLV body
		while (socket->is_open())
		{
			flv_tag tag;
			// FLV tag header
			tag.header = new char[TAG_HEADER_LENGTH];
			boost::asio::read(*socket, boost::asio::buffer(tag.header, TAG_HEADER_LENGTH));
			if (dump != NULL)
				dump->write(tag.header, TAG_HEADER_LENGTH);
			// TagType
			if ((tag.header[0] != TAGTYPE_AUDIO) && (tag.header[0] != TAGTYPE_VIDEO) && (tag.header[0] != TAGTYPE_DATA))
				throw flv_format_violation_exception();
			// DataSize
			tag.data_size = to_ui24((unsigned char*)tag.header, 1) + 4;
			// Timestamp
			unsigned int timestamp = to_ui24((unsigned char*)tag.header, 4);
			// TimestampExtended
			//unsigned int timestamp_extended = tagHeader[7];
			// StreamID
			if (0 != to_ui24((unsigned char*)tag.header, 8))
				throw flv_format_violation_exception();
			// Data
			tag.data = new char[tag.data_size];
			boost::asio::read(*socket, boost::asio::buffer(tag.data, tag.data_size));
			if (dump != NULL)
				dump->write(tag.data, tag.data_size);

			boost::mutex::scoped_lock lock(mutex);
			if ((tag.header[0] == TAGTYPE_VIDEO) && (1 == (tag.data[0] & 0xF0) >> 4))
			{
				key_frames = true;
				for (vector<flv_tag>::iterator i = tags_buffer.begin(); i != tags_buffer.end(); ++i)
				{
					delete[] i->header;
					delete[] i->data;
				}
				tags_buffer.clear();
				buffered_timestamp = timestamp;
			}

			if (tag.header[0] == TAGTYPE_DATA)
			{
				width = (int)get_double_variable_from_flv_script_tag(tag.data, tag.data_size, "width");
				height = (int)get_double_variable_from_flv_script_tag(tag.data, tag.data_size, "height");

				script_data.push_back(tag);
			}

			if (key_frames)
				tags_buffer.push_back(tag);
			else
				buffered_timestamp = timestamp;

			set<reader*> disconnected_readers;
			for (set<reader*>::iterator i = readers.begin(); i != readers.end(); ++i)
			{
				// Update timestamp.
				unsigned int modified_timestamp = timestamp - (*i)->timestamp_delta;
				char* modified_timestamp_ptr = (char*)(&modified_timestamp);

				char* modified_tag_header = new char[TAG_HEADER_LENGTH];
				memcpy(modified_tag_header, tag.header, TAG_HEADER_LENGTH);
				modified_tag_header[4] = modified_timestamp_ptr[2];
				modified_tag_header[5] = modified_timestamp_ptr[1];
				modified_tag_header[6] = modified_timestamp_ptr[0];

				// Write tag.
				try
				{
					(*i)->socket->send(boost::asio::buffer(modified_tag_header, TAG_HEADER_LENGTH));
					(*i)->socket->send(boost::asio::buffer(tag.data, tag.data_size));
					if ((*i)->dump != NULL)
					{
						(*i)->dump->write(modified_tag_header, TAG_HEADER_LENGTH);
						(*i)->dump->write(tag.data, tag.data_size);
					}
				}
				catch (boost::system::system_error &e)
				{
					cout << "Cloud Service: Reader connection was closed." << endl;
					delete *i;
					disconnected_readers.insert(*i);
				}

				delete[] modified_tag_header;
			}

			for (set<reader*>::iterator i = disconnected_readers.begin(); i != disconnected_readers.end(); ++i)
				readers.erase(*i);

			if (!key_frames && (tag.header[0] != TAGTYPE_DATA))
			{
				delete[] tag.header;
				delete[] tag.data;
			}
		}
	}
	catch (boost::system::system_error)
	{
		cout << "Cloud Service: Writer connection was closed." << endl;
	}
	catch (flv_format_violation_exception)
	{
		cout << "Cloud Service: FLV format violation exception was thrown." << endl;
	}
}

double writer::get_double_variable_from_flv_script_tag(char* script_tag_data, int data_size, string variable_name)
{
	char* script_data = new char[data_size + 1];
	for (int i = 0; i < data_size; ++i)
		script_data[i] = script_tag_data[i] == '\0' ? ' ' : script_tag_data[i];
	script_data[data_size] = '\0';
	string tag_data(script_data);
	delete[] script_data;

	int index = tag_data.find(variable_name) + variable_name.length() + 1;
	double result;
	char* reversed = (char*)(&result);
	for (int i = 0; i < 8; ++i)
		reversed[7 - i] = script_tag_data[index + i];
	return result;
}

unsigned short writer::to_ui16(unsigned char* value, int start_index)
{
	return (unsigned short)(value[start_index] << 8 | value[start_index + 1]);
}

unsigned int writer::to_ui24(unsigned char* value, int start_index)
{
	return (unsigned int)(value[start_index] << 16 | value[start_index + 1] << 8 | value[start_index + 2]);
}

unsigned int writer::to_ui32(unsigned char* value, int start_index)
{
	return (unsigned int)(value[start_index] << 24 | value[start_index + 1] << 16 | value[start_index + 2] << 8 | value[start_index + 3]);
}
