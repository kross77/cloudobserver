#ifndef SERVER_H
#define SERVER_H

//General STD
#include <sstream>
#include <set>
#include <map>
//Boost
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "server_utils.h"

class server
{
public:
	server(boost::property_tree::ptree config);
	virtual ~server();
	void acceptor_loop();
	boost::property_tree::ptree get_configuration();
	server_utils *util;
private:
	void request_response_loop(boost::shared_ptr<boost::asio::ip::tcp::socket> socket); //Each request received by server will be sent to a new thread and processed by request_response_loop
	void user_info(boost::asio::ip::tcp::socket &socket);
	std::map<boost::thread::id, boost::thread*> threads_pool;
	boost::thread *acceptor_thread;
};

#endif //SERVER_H