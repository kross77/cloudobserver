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
	reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump, unsigned int timestamp_delta);
	~reader();

	void send_data_tag(flv_tag tag);
	void send_script_tag(flv_tag tag);

	boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
	std::ofstream* dump;
	unsigned int timestamp_delta;
};

#endif // READER_H
