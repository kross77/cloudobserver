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
	//We pass user request to service for future inspection
	virtual bool service_call(http_request request, boost::shared_ptr<boost::asio::ip::tcp::socket> socket) = 0;
};

#endif