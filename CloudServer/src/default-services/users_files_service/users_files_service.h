#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

// Boost
#include <boost/cstdint.hpp> //boost::uintmax_t
#include <boost/asio.hpp>
#include <boost/timer.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/shared_array.hpp>
#include <boost/foreach.hpp>
// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>
//SQLite
#include <sqlite3pp.h>

#include <general_utils.h>
#include <http_utils.h>
#include <fs_file.h>

#include <service.hpp>


class users_files_service: public service
{
public:
	users_files_service();
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config);
	virtual void start(){}
	virtual void stop(){}
private:
	std::string get_user_name(boost::shared_ptr<http_request> request);

	boost::filesystem::path root_path;
	boost::posix_time::time_duration expiration_period;
	general_utils *general_util;
	http_utils *http_util;
	std::string max_age;

	void insert_file_headers( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response ){}
	void send_not_modified_304( boost::shared_ptr<boost::asio::ip::tcp::socket> socket,  boost::shared_ptr<http_response> response ){}
	void save_string_into_file(std::string contents, std::string name){}
	void send_uncachable_file(boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response){}
	void send_404(std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response){}

};

#endif // FILE_SERVICE_H
