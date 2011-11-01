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
	users_files_service()
	{
		general_util =boost::shared_ptr<general_utils>( new general_utils());
		http_util = boost::shared_ptr<http_utils>(new http_utils());
		fs_util =  boost::shared_ptr<fs_utils>(new fs_utils());

		this->root_path = boost::filesystem::current_path().string();

		this->expiration_period = boost::posix_time::minutes(200);
		this->max_age = "max-age=" + boost::lexical_cast<std::string>(this->expiration_period.total_seconds());

		this->default_lu_path = "ufs_log.txt";
		this->default_db_name = "ufs.db";

		is_db_set = false;
		is_lu_set = false;

		this->tag_ufs_extension = "extension";
		this->default_ufs_extension = "user.file";

		this->command_create_files_table = "CREATE TABLE IF NOT EXISTS files (encoded_url varchar(300) UNIQUE NOT NULL primary key, file_name varchar(150) NOT NULL, user_name varchar(65) NOT NULL, is_public BOOLEAN NOT NULL, modified DATETIME NOT NULL default CURRENT_TIMESTAMP )";
		this->command_create_file =  "INSERT INTO files (encoded_url, file_name, user_name, is_public ) VALUES (:encoded_url, :file_name, :user_name, :is_public)";
		this->command_update_file = " UPDATE files SET encoded_url=:new_encoded_url, file_name=:new_file_name, is_public=:is_public, modified=CURRENT_TIMESTAMP  WHERE encoded_url=:encoded_url";
		this->command_delete_file = "DELETE FROM files WHERE encoded_url=:encoded_url";
		this->command_find_file = "SELECT file_name, user_name, is_public, modified FROM files WHERE encoded_url=:encoded_url";
		this->command_find_all_user_files = "SELECT encoded_url, file_name, user_name, modified, is_public FROM files WHERE user_name=:user_name";

	}

	//UFS POST API:
	//	required:
	//		file_name : string,
	//		redirect_location : string,
	//		is_public : bool (as string),
	//		datafile : data (as string)
	//	use:
	//		users files upload.
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
	{
		std::string user_name = http_util->url_decode(fs_util->get_user_name(request));
		if(user_name != "guest")
		{
			if(request->body.length() > 0)
			{
				try
				{
					std::map<std::string, std::string> save_file; 
					save_file = http_util->parse_multipart_form_data(request->body);

					std::string file_name =save_file.find("file_name")->second;
					std::string redirect_location = save_file.find("redirect_location")->second;
					bool is_public = save_file.find("is_public")->second == "true" ? true : false ;

					std::string encoded_url = "";
					encoded_url = user_name + file_name + general_util->get_utc_now_time();
					encoded_url = general_util->get_sha256(encoded_url);
					encoded_url = encoded_url + "." + this->default_ufs_extension;
					encoded_url = http_util->url_encode( encoded_url );

					fs_util->save_string_into_file(save_file.find("datafile")->second, encoded_url,  this->root_path);
					this->create_file_table_entry(encoded_url, file_name, user_name, is_public);
					http_util->send_found_302(redirect_location, socket, response);
					return;
				}
				catch(std::exception &e)
				{
					*lu << e.what() << log_util::endl;
				}
			}

			if (request->url == "/ufs.json")
			{
				list_user_files(user_name, socket, response);
				return;
			}

			if(request->arguments["user_name"] == "true")
			{
				send_json( std::pair<std::string, std::string>("user_name", user_name), socket, response);
				return;
			}
		}
		fs_util->send_404(request->url, socket, request, response);
	}

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config)
	{
		this->root_path = config->get<std::string>("users_files_directory", this->root_path.string());
		this->default_ufs_extension = config->get<std::string>(this->tag_ufs_extension, this->default_ufs_extension);
		this->default_lu_path = config->get<std::string>("log_util_file", this->default_lu_path);
		this->default_db_name = config->get<std::string>("database", this->default_db_name);
		create_log_util(this->default_lu_path);
		create_files_table(this->default_db_name);
	}

	virtual void start(){}
	virtual void stop(){}

private:

	//TODO: move to http_utils, add std::map variant
	void send_json(std::pair<std::string, std::string> pair, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response)
	{
			std::ostringstream data_stream;
			data_stream << "\n{\n\t\"" << http_util->escape(pair.first) << "\": \""	<< http_util->escape(pair.second)  << "\"\n}";
			std::string data = data_stream.str();
			response->body = data;
			response->body_size = response->body.length();
			response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(response->body_size)));
			response->send(*socket);
			return;
	}

	void list_user_files(std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response)
	{

		std::ostringstream user_files_stream;
		user_files_stream << "[";

		sqlite3pp::transaction xct(*db, true);
		{
			sqlite3pp::query qry(*db, this->command_find_all_user_files.c_str());
			qry.bind(":user_name", user_name);

			for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
				bool is_public;
				std::string encoded_url, file_name, user_name, modified;
				(*i).getter() >> encoded_url >> file_name >> user_name >> modified >> is_public ;
				
				user_files_stream << "\n\t{\n\t\t\"encoded_url\": \""
					<< encoded_url << "\",\n\t\t\"file_name\": \""
					<< http_util->escape(file_name) << "\",\n\t\t\"user_name\": \""
					<< user_name << "\",\n\t\t\"modified\": \""
					<< modified << "\",\n\t\t\"is_public\": "
					<< is_public << "\n\t},";
			}

		}
		std::string files_ = user_files_stream.str();
		if (files_.length() > 5)
			files_ = files_.substr(0, files_.length() - 1);

		response->body = files_.append("\n]");
		response->body_size = response->body.length();
		response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(response->body_size)));
		response->send(*socket);
		return;
	}

	void create_file_table_entry(std::string encoded_url, std::string file_name, std::string user_name, bool is_public)
	{
		sqlite3pp::transaction xct(*db);
		sqlite3pp::command cmd(*db, command_create_file.c_str());
		cmd.bind(":encoded_url", encoded_url) ;
		cmd.bind(":file_name", file_name) ;
		cmd.bind(":user_name", user_name) ;
		cmd.bind(":is_public", is_public);
		cmd.execute() ;
		xct.commit();
	}

	void create_log_util( std::string lu_path )
	{
		if (!is_lu_set)
		{
			lu = boost::shared_ptr<log_util>(new log_util(50, false, true, true, lu_path));
			is_lu_set = true;
		}
	}

	void create_files_table( std::string db_name )
	{
		if(!is_db_set) // TODO: find out how to detach from one db and connect to another.
		{
			boost::shared_ptr<sqlite3pp::database> db_( new sqlite3pp::database(db_name.c_str())); //I could not get `db = new sqlite3pp::database(DB_name.c_str());` to compile
			db = db_;
			*lu << "Connected to "<< db_name << " database and created a table with SQLite return code: " << db->execute(command_create_files_table.c_str()) << log_util::endl;
			is_db_set = true;
		}
	}

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
	void insert_file_headers( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response ){}
	void send_uncachable_file(boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response){}

	CLOUD_SERVICE_AUXILIARIES;
};

#endif // FILE_SERVICE_H
