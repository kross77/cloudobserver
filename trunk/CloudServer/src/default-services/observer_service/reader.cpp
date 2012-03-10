#include "reader.h"

using namespace std;

reader::reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, ofstream* dump, unsigned int timestamp_delta) : socket(socket), dump(dump), timestamp_delta(timestamp_delta) { }

reader::~reader()
{
	socket->close();

	if (dump != NULL)
	{
		dump->close();
		delete dump;
	}
}

void reader::send_tag(flv_tag tag)
{
	if (tag.header[0] == TAGTYPE_DATA)
	{
		socket->send(boost::asio::buffer(tag.header, TAG_HEADER_LENGTH));
		socket->send(boost::asio::buffer(tag.data, tag.data_size));
		if (dump != NULL)
		{
			dump->write(tag.header, TAG_HEADER_LENGTH);
			dump->write(tag.data, tag.data_size);
		}
	}
	else
	{
		// Update timestamp.
		unsigned int modified_timestamp = tag.timestamp - timestamp_delta;
		char* modified_timestamp_ptr = (char*)(&modified_timestamp);

		boost::scoped_array<char> modified_tag_header(new char[TAG_HEADER_LENGTH]);
		memcpy(modified_tag_header.get(), tag.header, TAG_HEADER_LENGTH);
		modified_tag_header[4] = modified_timestamp_ptr[2];
		modified_tag_header[5] = modified_timestamp_ptr[1];
		modified_tag_header[6] = modified_timestamp_ptr[0];

		socket->send(boost::asio::buffer(modified_tag_header.get(), TAG_HEADER_LENGTH));
		socket->send(boost::asio::buffer(tag.data, tag.data_size));
		if (dump != NULL)
		{
			dump->write(modified_tag_header.get(), TAG_HEADER_LENGTH);
			dump->write(tag.data, tag.data_size);
		}
	}
}
