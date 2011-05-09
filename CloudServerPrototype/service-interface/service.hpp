#ifndef SERVICE_HPP
#define SERVICE_HPP

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

using namespace boost::asio::ip;
using namespace boost::filesystem;

class BOOST_EXTENSION_EXPORT_DECL service
{
public:
	service(path default_path) : file_service_default_path(file_service_default_path) {std::cout << "\nCreated a Service";}

	virtual ~service(void){std::cout << "\nDestroyed a Service";}
	
	virtual bool service_call(http_request request, boost::shared_ptr<tcp::socket> socket){return 1;} // bool for service execution status
	
	path get_default_path(void) {
		return file_service_default_path;
	}
	
	void set_default_path(path default_path) {
		file_service_default_path = default_path;
	}

protected:
	path file_service_default_path;

};

#endif