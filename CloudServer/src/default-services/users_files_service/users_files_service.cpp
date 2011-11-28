#include "users_files_service.h"

users_files_service::users_files_service()
{
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

	this->command_create_files_table = "CREATE TABLE IF NOT EXISTS files (encoded_url varchar(300) UNIQUE NOT NULL primary key, file_name varchar(150) NOT NULL, user_name varchar(65) NOT NULL, is_public BOOLEAN NOT NULL, modified DATETIME NOT NULL default CURRENT_TIMESTAMP, type varchar(20), size INTEGER(8) )";
	this->command_create_file =  "INSERT INTO files (encoded_url, file_name, user_name, is_public, type, size ) VALUES (:encoded_url, :file_name, :user_name, :is_public, :type, :size)";
	this->command_update_file = " UPDATE files SET encoded_url=:new_encoded_url, file_name=:new_file_name, is_public=:is_public, modified=CURRENT_TIMESTAMP, type=:type, size=:size  WHERE encoded_url=:encoded_url";
	this->command_delete_file = "DELETE FROM files WHERE encoded_url=:encoded_url";
	this->command_find_file = "SELECT file_name, user_name, is_public, modified FROM files WHERE encoded_url=:encoded_url";
	this->command_find_all_user_files = "SELECT encoded_url, file_name, user_name, modified, type, size, is_public FROM files WHERE user_name=:user_name";
	this->command_find_all_user_files_of_type = "SELECT encoded_url, file_name, user_name, modified, size, is_public FROM files WHERE user_name=:user_name AND type=:type";
}

void users_files_service::apply_config( boost::shared_ptr<boost::property_tree::ptree> config )
{
	config = boost::shared_ptr<boost::property_tree::ptree>(new boost::property_tree::ptree(*config));
	this->root_path = config->get<std::string>("users_files_directory", this->root_path.string());
	this->default_ufs_extension = config->get<std::string>("extension", this->default_ufs_extension);
	this->default_lu_path = config->get<std::string>("log_util_file", this->default_lu_path);
	this->default_db_name = config->get<std::string>("database", this->default_db_name);

	create_log_util(this->default_lu_path);
	create_files_table(this->default_db_name);
}

void users_files_service::service_call( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	std::string user_name = http_utils::url_decode(fs_util->get_user_name(request));
	if(user_name != "guest")
	{
		if(request->body.length() > 0)
		{
			try
			{
				std::map<std::string, std::string> save_file; 
				save_file = http_utils::parse_multipart_form_data(request->body);

				std::string file_name =save_file.find("file_name")->second;
				std::string redirect_location = save_file.find("redirect_location")->second;
				std::string f_type = save_file.find("type")->second;
				bool is_public = save_file.find("is_public")->second == "true" ? true : false ;

				std::string encoded_url = "";
				encoded_url = user_name + file_name + general_utils::get_utc_now_time();
				encoded_url = general_utils::get_sha256(encoded_url);
				encoded_url = encoded_url + "." + this->default_ufs_extension;
				encoded_url = http_utils::url_encode( encoded_url );
				int f_size = save_file.find("datafile")->second.length();
				fs_util->save_string_into_file(save_file.find("datafile")->second, encoded_url,  this->root_path);
				this->create_file_table_entry(encoded_url, file_name, user_name, f_type, f_size, is_public);

				http_utils::send_found_302(redirect_location, socket, response);

				return;
			}
			catch(std::exception &e)
			{
				*lu << e.what() << log_util::endl;
			}
		}

		if (request->url == "/ufs.json")
		{
			if (boost::iequals(request->arguments["action"], "type"))
			{
				list_user_files_of_type(user_name, request->arguments["type"],  socket, response);
				return;
			}

			list_user_files(user_name, socket, response);
			return;
		}

		if(request->arguments["user_name"] == "true")
		{
			send_json( std::pair<std::string, std::string>("user_name", user_name), socket, response);
			return;
		}
	}

	std::map<std::string, std::string>::iterator redirect_iterator= request->arguments.find("redirect_to");
	if (redirect_iterator != request->arguments.end() )
	{
		http_utils::send_found_302(redirect_iterator->second, socket, response);
		return;
	}
	bool sent;
	try{
		sent = send_file(request->url, user_name, socket, request, response);
		if (!sent)
		{
			fs_util->send_404(request->url, socket, request, response);
		}
	}
	catch(...)
	{
		fs_util->send_404(request->url, socket, request, response);
	}
}



bool users_files_service::send_file( std::string href, std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
		href.erase(0,1);
	sqlite3pp::transaction xct(*db, true);
	{
		sqlite3pp::query qry(*db, this->command_find_file.c_str());
		qry.bind(":encoded_url", href);
		//file_name, user_name, is_public, modifie
		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			bool is_public=false;
			std::string  file_name, f_user_name, modified;
			(*i).getter() >> file_name >> f_user_name >>  is_public >> modified;

			if (is_public)
			{
				boost::shared_ptr<fs_file> f = fs_util->create_file(boost::filesystem::path(root_path / href));
				fs_util->send_uncachable_file(f, socket,request, response);
				return true;
			}
			else if (f_user_name == user_name)
			{
				boost::shared_ptr<fs_file> f = fs_util->create_file(boost::filesystem::path(root_path / href));
				fs_util->send_uncachable_file(f, socket,request, response);
				return true;
			}
			return false;
		}

	}
	return false;
}

void users_files_service::send_json( std::pair<std::string, std::string> pair, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	std::ostringstream data_stream;
	data_stream << "\n{\n\t\"" << http_utils::escape(pair.first) << "\": \""	<< http_utils::escape(pair.second)  << "\"\n}";
	std::string data = data_stream.str();
	response->body = data;
	response->body_size = response->body.length();
	response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(response->body_size)));
	response->send(*socket);
	return;
}



void users_files_service::list_user_files( std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	std::ostringstream user_files_stream;
	user_files_stream << "[";

	sqlite3pp::transaction xct(*db, true);
	{
		sqlite3pp::query qry(*db, this->command_find_all_user_files.c_str());
		qry.bind(":user_name", user_name);

		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			bool is_public;
			int f_size;
			std::string encoded_url, file_name, user_name, modified, f_type;
			(*i).getter() >> encoded_url >> file_name >> user_name >> modified >> f_type >> f_size >> is_public ;

			user_files_stream << "\n\t{\n\t\t\"href\": \""
				<< encoded_url << "\",\n\t\t\"title\": \""
				<< http_utils::escape(file_name) << "\",\n\t\t\"user_name\": \""
				<< user_name << "\",\n\t\t\"modified\": \""
				<< modified << "\",\n\t\t\"type\": \""
				<< f_type << "\",\n\t\t\"is_public\": "
				<< is_public << ",\n\t\t\"size\": " 
				<< f_size << "\n\t},";
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

void users_files_service::list_user_files_of_type( std::string user_name,  std::string f_type, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	std::ostringstream user_files_stream;
	user_files_stream << "[";

	sqlite3pp::transaction xct(*db, true);
	{
		sqlite3pp::query qry(*db, this->command_find_all_user_files_of_type.c_str());
		qry.bind(":user_name", user_name);
		qry.bind(":type", f_type);

		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			bool is_public;
			int f_size;
			std::string encoded_url, file_name, user_name, modified;
			(*i).getter() >> encoded_url >> file_name >> user_name >> modified  >> f_size >> is_public ;

			user_files_stream << "\n\t{\n\t\t\"href\": \""
				<< encoded_url << "\",\n\t\t\"title\": \""
				<< http_utils::escape(file_name) << "\",\n\t\t\"user_name\": \""
				<< user_name << "\",\n\t\t\"modified\": \""
				<< modified << "\",\n\t\t\"is_public\": "
				<< is_public << ",\n\t\t\"size\": " 
				<< f_size << "\n\t},";
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


void users_files_service::create_file_table_entry( std::string encoded_url, std::string file_name, std::string user_name, std::string f_type, int f_size, bool is_public )
{
	sqlite3pp::transaction xct(*db);
	sqlite3pp::command cmd(*db, command_create_file.c_str());
	cmd.bind(":encoded_url", encoded_url) ;
	cmd.bind(":file_name", file_name) ;
	cmd.bind(":user_name", user_name) ;
	cmd.bind(":is_public", is_public);
	cmd.bind(":size", f_size);
	cmd.bind(":type", f_type);
	cmd.execute() ;
	xct.commit();
}

void users_files_service::create_log_util( std::string lu_path )
{
	if (!is_lu_set)
	{
		lu = boost::shared_ptr<log_util>(new log_util(50, false, true, true, lu_path));
		is_lu_set = true;
	}
}

void users_files_service::create_files_table( std::string db_name )
{
	if(!is_db_set) // TODO: find out how to detach from one db and connect to another.
	{
		boost::shared_ptr<sqlite3pp::database> db_( new sqlite3pp::database(db_name.c_str())); //I could not get `db = new sqlite3pp::database(DB_name.c_str());` to compile
		db = db_;
		*lu << "Connected to "<< db_name << " database and created a table with SQLite return code: " << db->execute(command_create_files_table.c_str()) << log_util::endl;
		is_db_set = true;
	}
}

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<service> > &factories(types.get());
	factories["users_files_service"].set<users_files_service>();
}