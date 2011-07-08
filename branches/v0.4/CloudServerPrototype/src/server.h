#ifndef SERVER_H
#define SERVER_H

// Map (for Boost Extension), Socket Utils
//#include "utilities.h"
//General STD
#include <sstream>
#include <set>

//Boost
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/timer.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

//CF
#include <http.h>

//General Service header Class\Interface
//#include "../service-interface/service.hpp"
#include "printer.h"

class server
{
public:
	// TODO: turn int config into boost.ptree based real config file
	server(int config);
	virtual ~server();
	void acceptor_loop();
	void user_info(boost::asio::ip::tcp::socket& socket);
private:
	void request_response_loop(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
	boost::thread *acceptor_thread;
	int _config;
	printer *print;

};

#endif //SERVER_H