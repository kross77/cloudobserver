#ifndef SERVICE_HPP
#define SERVICE_HPP
// STD
#include <iostream>
#include <string>

//Boost-Extension
#include <typeinfo>
#include <boost/extension/extension.hpp>

//Boost-FileSystem
#include <boost/filesystem.hpp>

//Boost-ASIO
#include <boost/asio.hpp>

//CF
#include <http.h>

//TODO: Remove using namespace
using namespace boost::asio::ip;
using namespace boost::filesystem;

//Main service interface.
class BOOST_EXTENSION_EXPORT_DECL service
{
public:

	//We link service to filesystem directory where it should operate (read from / write to)
	service(path default_path) : service_default_path(default_path) {std::cout << "\nCreated a Service";}

	virtual ~service(void){std::cout << "\nDestroyed a Service";}

	//We pass user request to service for future inspection
	virtual bool service_call(http_request request, boost::shared_ptr<tcp::socket> socket){return 1;} // bool for service execution status

	//Here we provide default service model with some frequently used methods


	
	path get_default_path(void) {
		return service_default_path;
	}
	
	void set_default_path(path default_path) {
		service_default_path = default_path;
	}

protected:
	path service_default_path;

};

#endif