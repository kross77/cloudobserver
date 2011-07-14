#ifndef CLOUD_READER_H
#define CLOUD_READER_H

#include <fstream>

#include <boost/asio.hpp>

class cloud_reader
{
public:
	cloud_reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump, unsigned int timestamp_delta);
	~cloud_reader();

	boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
	std::ofstream* dump;
	unsigned int timestamp_delta;
};

#endif // CLOUD_READER_H
