#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

// Boost
#include <boost/cstdint.hpp> //boost::uintmax_t
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>

// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

#include <general_utils.h>
#include <http_utils.h>

#include <service.hpp>

class file_service: public service
{
public:
	file_service();
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
	virtual void apply_config(boost::property_tree::ptree config);
	virtual void start(){}
	virtual void stop(){}
private:
	std::string get_user_name(boost::shared_ptr<http_request> request);
	boost::filesystem::path root_path;
	bool show_directory_contents;
	boost::posix_time::time_duration expiration_period;
	general_utils *general_util;
	http_utils *http_util;
	void save_string_into_file(std::string contents, std::string name);

	boost::filesystem::path users_directory_path;
};

#endif // FILE_SERVICE_H
