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

//Main service interface.
class service
{
public:

	//We link service to filesystem directory where it should operate (read from / write to)
	service(boost::filesystem::path default_path) : service_default_path(default_path) {std::cout << "\nCreated a Service";}

	virtual ~service(void){std::cout << "\nDestroyed a Service";}

	//We pass user request to service for future inspection
	virtual bool service_call(http_request request, boost::shared_ptr<boost::asio::ip::tcp::socket> socket){return 1;} // bool for service execution status

	//Here we provide default service model with some frequently used methods


	
	boost::filesystem::path get_default_path(void) {
		return service_default_path;
	}
	
	void set_default_path(boost::filesystem::path default_path) {
		service_default_path = default_path;
	}

protected:
	boost::filesystem::path service_default_path;

};

#endif