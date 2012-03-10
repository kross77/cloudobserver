#include "reader.h"

using namespace std;

reader::reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<ofstream> dump) : socket(socket), dump(dump), timestamp_delta(0), alive(true) { }

reader::~reader()
{
	socket->close();

	if (dump != NULL)
		dump->close();
}

bool reader::is_alive()
{
	return alive;
}

void reader::process()
{
	while (socket->is_open())
	{
		boost::mutex::scoped_lock lock(mutex);
		while (buffer.empty())
			condition.wait(lock);

		flv_tag tag = buffer.front();
		lock.unlock();

		try
		{
			if (tag.header[0] == TAGTYPE_DATA)
			{
				socket->send(boost::asio::buffer(tag.header.get(), TAG_HEADER_LENGTH));
				socket->send(boost::asio::buffer(tag.data.get(), tag.data_size));
				if (dump != NULL)
				{
					dump->write((char *)tag.header.get(), TAG_HEADER_LENGTH);
					dump->write((char *)tag.data.get(), tag.data_size);
				}
			}
			else
			{
				// Update timestamp.
				unsigned int modified_timestamp = tag.timestamp - timestamp_delta;
				unsigned char* modified_timestamp_ptr = (unsigned char*)(&modified_timestamp);

				boost::scoped_array<unsigned char> modified_tag_header(new unsigned char[TAG_HEADER_LENGTH]);
				memcpy(modified_tag_header.get(), tag.header.get(), TAG_HEADER_LENGTH);
				modified_tag_header[4] = modified_timestamp_ptr[2];
				modified_tag_header[5] = modified_timestamp_ptr[1];
				modified_tag_header[6] = modified_timestamp_ptr[0];

				socket->send(boost::asio::buffer(modified_tag_header.get(), TAG_HEADER_LENGTH));
				socket->send(boost::asio::buffer(tag.data.get(), tag.data_size));
				if (dump != NULL)
				{
					dump->write((char *)modified_tag_header.get(), TAG_HEADER_LENGTH);
					dump->write((char *)tag.data.get(), tag.data_size);
				}
			}
		}
		catch (boost::system::system_error &e)
		{
			break;
		}
		lock.lock();
		buffer.pop_front();
	}
	alive = false;
}

void reader::send_tag(flv_tag tag)
{
	boost::mutex::scoped_lock lock(mutex);
	buffer.push_back(tag);
	condition.notify_one();
}

void reader::set_timestamp_delta(unsigned int timestamp)
{
	timestamp_delta = timestamp;
}
