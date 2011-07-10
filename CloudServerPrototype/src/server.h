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

//General Service header Class\Interface
//#include "../service-interface/service.hpp"

class server
{
public:
	// TODO: turn int config into ptree based real config file
	server(int config);

	virtual ~server();
	void acceptor_loop();
	void user_info(boost::asio::ip::tcp::socket &socket);
private:
	void request_response_loop(boost::shared_ptr<boost::asio::ip::tcp::socket> socket); //Each request received by server will be sent to a new thread and processed by request_response_loop

	server_utils *util;

	// Main server thread
	boost::thread *acceptor_thread; 

	//TODO: replace with ptree
	int _config; 

	//TODO: get rid of ptr to only one service, replace with some sort of set of services.
	boost::shared_ptr<service> file_service_ptr;


};

#endif //SERVER_H