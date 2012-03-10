#ifndef READER_H
#define READER_H

#include <fstream>

#include <boost/asio.hpp>

class reader
{
public:
	reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump, unsigned int timestamp_delta);
	~reader();

	boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
	std::ofstream* dump;
	unsigned int timestamp_delta;
};

#endif // READER_H
