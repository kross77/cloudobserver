#ifndef SERVER_H
#define SERVER_H

//General STD
#include <sstream>
#include <set>
#include <map>
//Boost
//Minimal server includes
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <http.h>
#include "printer.h"
//Minimal extension includes
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
	// TODO: turn int config into ptree based real config file
	server(int config);

	virtual ~server();
	void acceptor_loop();
	void user_info(boost::asio::ip::tcp::socket &socket);
private:
	void request_response_loop(boost::shared_ptr<boost::asio::ip::tcp::socket> socket); //Each request received by server will be sent to a new thread and processed by request_response_loop
	boost::shared_ptr<service> create_service(std::string library_name, std::string class_name_inside_lib); // Creates class that is inherited from service class\interface. 
	printer *print; // For requests printing in request_response_loop
	extension_utils *util; // For services creation from shared libraries
	boost::filesystem::path server_root_path; // Server path (by default app path) //TODO: make it configurable via config ptree
	boost::thread *acceptor_thread; // Main server thread
	//TODO: replace with ptree
	int _config; 

	//TODO: get rid of ptr to only one service, replace with some sort of set of services.
	boost::shared_ptr<service> file_service_ptr;


};

#endif //SERVER_H