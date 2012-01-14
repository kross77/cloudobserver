#ifndef OBSERVER_READER_H
#define OBSERVER_READER_H

#include <fstream>

#include <boost/asio.hpp>

class observer_reader
{
public:
	observer_reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump, unsigned int timestamp_delta);
	~observer_reader();

	boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
	std::ofstream* dump;
	unsigned int timestamp_delta;
};

#endif // OBSERVER_READER_H
