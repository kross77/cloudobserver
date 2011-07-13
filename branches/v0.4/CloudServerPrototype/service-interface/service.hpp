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
		set_config(config);
		auto_close_socket = true;
		std::cout << "\nCreated a Service";
	}

	~service(void){std::cout << "\nDestroyed a Service" << std::endl;}

	//We pass user request to service for future inspection
	virtual bool service_call(http_request request, boost::shared_ptr<boost::asio::ip::tcp::socket> socket){return 1;} // bool for service execution status

	//Here we provide default service model with some frequently used methods	
	boost::property_tree::ptree get_config(void) {
		return configuration;
	}
	
	void set_config(boost::property_tree::ptree _configuration) {
		configuration = _configuration;
	}

	void update_config(boost::property_tree::ptree new_configuration)
	{
		configuration = new_configuration;
	}
	
	bool get_auto_close_socket(void)
	{
		return auto_close_socket;
	}

protected:
	void set_auto_close_socket(bool _auto_close_socket)
	{
		auto_close_socket = _auto_close_socket;
	}

protected:
	boost::property_tree::ptree configuration;
	bool auto_close_socket;

};

#endif