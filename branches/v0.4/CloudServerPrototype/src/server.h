#ifndef SERVER_H
#define SERVER_H

// Map (for Boost Extension), Socket Utils
//#include "utilities.h"
//General STD
#include <sstream>
#include <set>
#include <map>
//Boost
//minimal server includes
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <http.h>
#include "printer.h"
//minimal extension includes
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/shared_library.hpp>
#include <boost/extension/type_map.hpp>
#include <boost/extension/convenience.hpp>
#include "extension_utils.h"
//General Service header Class\Interface
#include "../service-interface/service.hpp"


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
	extension_utils *util;

};

#endif //SERVER_H