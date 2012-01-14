#include "observer_reader.h"

observer_reader::observer_reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump, unsigned int timestamp_delta)
{
	this->socket = socket;
	this->dump = dump;
	this->timestamp_delta = timestamp_delta;
}

observer_reader::~observer_reader()
{
	this->socket->close();

	if (this->dump != NULL)
	{
		this->dump->close();
		delete dump;
	}
}
