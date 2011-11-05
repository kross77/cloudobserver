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
#include <log_util.h>
#include <fs_file.h>
#include <fs_utils.h>

#include <service.hpp>


class users_files_service: public service
{ 
public:
	users_files_service();

	//UFS POST API:
	//	required:
	//		file_name : string,
	//		redirect_location : string,
	//		is_public : bool (as string),
	//		datafile : data (as string)
	//	use:
	//		users files upload.
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config);

	virtual void start(){}
	virtual void stop(){}

private:

	//TODO: move to http_utils, add std::map variant
	void send_json(std::pair<std::string, std::string> pair, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response);

	void list_user_files(std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response);

	void create_file_table_entry(std::string encoded_url, std::string file_name, std::string user_name, bool is_public);

	void create_log_util( std::string lu_path );

	void create_files_table( std::string db_name );

	boost::filesystem::path root_path;
	boost::shared_ptr<sqlite3pp::database> db;
	bool is_db_set;

	boost::posix_time::time_duration expiration_period;
	boost::shared_ptr<general_utils> general_util;
	boost::shared_ptr<http_utils> http_util;
	boost::shared_ptr<fs_utils> fs_util;
	boost::shared_ptr<log_util> lu;
	bool is_lu_set;

	std::string max_age;

	std::string command_create_files_table;
	std::string command_update_file;
	std::string command_delete_file;
	std::string command_create_file;
	std::string command_find_file;
	std::string default_db_name;
	std::string command_find_all_user_files;
	std::string default_lu_path;
	std::string tag_ufs_extension;
	std::string default_ufs_extension;

	CLOUD_SERVICE_AUXILIARIES;
};

#endif // FILE_SERVICE_H