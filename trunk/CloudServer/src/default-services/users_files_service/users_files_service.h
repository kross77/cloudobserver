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
#include <fs_utils.h>

#include <service.hpp>


class users_files_service: public service
{ 
public:
	users_files_service()
	{
		general_util = new general_utils();
		http_util = new http_utils();
		fs_util = new fs_utils();
		this->root_path = boost::filesystem::current_path().string();

		this->expiration_period = boost::posix_time::minutes(200);
		this->max_age = "max-age=" + boost::lexical_cast<std::string>(this->expiration_period.total_seconds());

		this->command_create_users_table = "CREATE TABLE IF NOT EXISTS files (encoded_url varchar(300) UNIQUE NOT NULL primary key, file_name varchar(65) NOT NULL, user_name varchar(65) NOT NULL, is_public BOOLEAN NOT NULL, modified DATETIME NOT NULL default CURRENT_TIMESTAMP )";
		this->command_create_user =  "INSERT INTO files (encoded_url, file_name, user_name, is_public, ) VALUES (?, ?, ?, ?, now)";
		this->command_find_user = "SELECT email, pass FROM users WHERE email=";

	}
	
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
	{
		send_fuck(socket, request, response);
	}

	void send_fuck( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
	{
		std::ostringstream body;
		body << "Go fuck your self! " << http_util->url_decode(request->url) << " does not exist\n <br/> <a href='/'>" << "Dear " << http_util->url_decode(fs_util->get_user_name(request)) <<", please now fuck your self again!</a>";

		response->body = "<head></head><body><h1>" + body.str() + "</h1></body>";
		response->send(*socket);
	}

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config)
	{
		this->root_path = config->get<std::string>("users_files_directory", this->root_path.string());
	}
	virtual void start(){}
	virtual void stop(){}
private:


	boost::filesystem::path root_path;
	boost::posix_time::time_duration expiration_period;
	general_utils *general_util;
	http_utils *http_util;
	fs_utils *fs_util;
	std::string max_age;
	std::string command_find_user;
	std::string command_create_user;
	std::string command_create_users_table;
	void insert_file_headers( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response ){}
	void send_uncachable_file(boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response){}
	

	CLOUD_SERVICE_AUXILIARIES;
};

#endif // FILE_SERVICE_H
