#include "cloud_reader.h"

cloud_reader::cloud_reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump, unsigned int timestamp_delta)
{
	this->socket = socket;
	this->dump = dump;
	this->timestamp_delta = timestamp_delta;
}

cloud_reader::~cloud_reader()
{
	this->socket->close();

	if (this->dump != NULL)
	{
		this->dump->close();
		delete dump;
	}
}
