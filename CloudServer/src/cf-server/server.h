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
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

//Thread safe logging
#include <log_util.h>
#include <thread_pool.h>

#include "server_utils.h"
#include "user_control.h"

class server
{
public:
	server(boost::property_tree::ptree config);
	~server();
	void acceptor_loop();
	boost::property_tree::ptree get_configuration();
	server_utils *util;
private:
	void request_response_loop(boost::shared_ptr<boost::asio::ip::tcp::socket> socket); //Each request received by server will be sent to a new thread and processed by request_response_loop
	void user_info(boost::asio::ip::tcp::socket &socket);
	void server_services_list(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response);
	void server_service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
	boost::thread *acceptor_thread;
	user_control *uac;
	boost::shared_ptr<thread_pool> threads_pool;
	int request_max_time;
};

#endif //SERVER_H