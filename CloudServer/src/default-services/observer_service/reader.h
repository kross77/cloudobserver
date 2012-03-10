#ifndef READER_H
#define READER_H

#include <fstream>

#include <boost/asio.hpp>
#include <boost/scoped_array.hpp>

#include "flv_format.h"
#include "flv_tag.h"

class reader
{
public:
	reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<std::ofstream> dump);
	~reader();

	void send_tag(flv_tag tag);
	void set_timestamp_delta(unsigned int timestamp);

	boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
	boost::shared_ptr<std::ofstream> dump;
	unsigned int timestamp_delta;
};

#endif // READER_H
