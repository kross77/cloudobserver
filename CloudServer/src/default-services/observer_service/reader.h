#ifndef READER_H
#define READER_H

#include <fstream>
#include <list>

#include <boost/asio.hpp>
#include <boost/scoped_array.hpp>
#include <boost/thread.hpp>

#include "flv_format.h"
#include "flv_tag.h"

class reader
{
public:
	reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<std::ofstream> dump);
	~reader();

	bool is_alive();
	void process();
	void send_tag(flv_tag tag);
	void set_timestamp_delta(unsigned int timestamp);

	boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
	boost::shared_ptr<std::ofstream> dump;
	unsigned int timestamp_delta;
private:
	bool alive;
	std::list<flv_tag> buffer;

	boost::mutex mutex;
	boost::condition_variable condition;
};

#endif // READER_H
