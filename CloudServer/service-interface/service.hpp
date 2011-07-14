#ifndef SERVICE_HPP
#define SERVICE_HPP
// STD
#include <iostream>
#include <string>

////Boost-Extension
//#include <typeinfo>
//#include <boost/extension/extension.hpp>

//Boost-FileSystem
#include <boost/filesystem.hpp>

//Boost-PropertyTree
#include <boost/property_tree/ptree.hpp>

//Boost-ASIO
#include <boost/asio.hpp>

//CF
#include <http.h>

//Main service interface.
class service
{
public:

	//We link service to filesystem directory where it should operate (read from / write to)
	service(boost::property_tree::ptree config)
	{
		std::cout << "\nCreated a Service";
	}

	~service(void){std::cout << "\nDestroyed a Service" << std::endl;}

	//We pass user request to service for future inspection
	virtual bool service_call(http_request request, boost::shared_ptr<boost::asio::ip::tcp::socket> socket){return 1;} // bool for service execution status
};

#endif