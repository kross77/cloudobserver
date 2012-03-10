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
