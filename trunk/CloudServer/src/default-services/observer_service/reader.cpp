#include "reader.h"

using namespace std;

reader::reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, ofstream* dump, unsigned int timestamp_delta)
{
	this->socket = socket;
	this->dump = dump;
	this->timestamp_delta = timestamp_delta;
}

reader::~reader()
{
	this->socket->close();

	if (this->dump != NULL)
	{
		this->dump->close();
		delete dump;
	}
}
