#include "users_files_service.h"

users_files_service::users_files_service()
{
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
	this->command_find_file = "SELECT file_name, user_name, is_public, modified, type FROM files WHERE encoded_url=:encoded_url";
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

void users_files_service::service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request,  boost::shared_ptr<shared> shared_data)
{
	boost::shared_ptr<http_response> response(new http_response(), boost::bind(&pointer_utils::delete_ptr<http_response>, _1));

	std::string user_name = fs_utils::get_user_name(shared_data);
	if( (user_name != "guest") && (user_name != ""))
	{
		if(request->url == "/ufs.service"){
			if (boost::iequals(request->method, "POST"))
			{
				if(request->body.length() > 0)
				{

					std::map<std::string, std::string> save_file; 
					save_file = http_utils::parse_multipart_form_data(request->body);
					bool save = false;
					//search for file
					std::string file_data;
					//with size
					int f_size;
					//set file policy
					bool is_public = false;
					//set virtual file name
					std::string file_name = "Untitled";
					//set fiscal file name
					std::string encoded_url = "";
					//set file type
					std::string f_type = "";

					if (save_file.empty())
					{
						if (boost::iequals(request->arguments["action"], "delete"))
						{
							boost::char_separator<char> sep(", ");
							boost::tokenizer<boost::char_separator<char> > tokens(request->body, sep);
							BOOST_FOREACH(std::string t, tokens)
							{
								delete_file( t, user_name);
							}
							http_utils::send_json(std::pair<std::string, std::string>("success","true"),  socket, response, request); 
							return;
						}
						else if(boost::iequals(request->arguments["action"], "upload"))
						{
							save = true;
							file_data= request->body;
							if(!boost::iequals(request->arguments["is_public"], ""))
							{
								is_public = request->arguments["is_public"] == "true" ? true : false ;
							}
							if(!boost::iequals(request->arguments["type"], ""))
							{
								f_type = http_utils::url_decode(request->arguments["type"]);
							}
							if(!boost::iequals(request->arguments["name"], ""))
							{
								file_name = http_utils::url_decode(request->arguments["name"]);
							}
						}

					}else{
						//parse POST request data
						std::map<std::string, std::string>::iterator it;
						it = save_file.find("datafile");
						if (it != save_file.end())
						{
							save = true;
							//set file contents
							file_data = it->second;

							//set file size
							//f_size = save_file.find("datafile")->second.length();

							it = save_file.find("file_name");
							if (it != save_file.end())
							{
								file_name = it->second;
							}

							it = save_file.find("is_public");
							if (it != save_file.end())
							{
								is_public = it->second == "true" ? true : false ;
							}

							it = save_file.find("type");
							if (it != save_file.end())
							{
								f_type = it->second;
							}
						}
					}
			

					if(save){
						f_size = file_data.length();

						encoded_url = user_name + file_name + general_utils::get_utc_now_time();
						encoded_url = general_utils::get_sha256(encoded_url);
						encoded_url = encoded_url + "." + this->default_ufs_extension;
						encoded_url = http_utils::url_encode( encoded_url );

						//save file
						fs_utils::save_string_into_file(file_data, encoded_url,  this->root_path);
						this->create_file_table_entry(encoded_url, file_name, user_name, f_type, f_size, is_public);
					}else{
						http_utils::send_json(std::pair<std::string, std::string>("success","false"),  socket, response, request); 
					}

					//redirect user
					std::map<std::string, std::string>::iterator it;
					it =save_file.find("redirect_location");
					if (it != save_file.end())
					{
						http_utils::send_found_302(it->second, socket, response, request);
					}else{
						http_utils::send_json(std::pair<std::string, std::string>("success","true"),  socket, response, request); 
					}
					return;
				}else{
					http_utils::send_json(std::pair<std::string, std::string>("success","false"),  socket, response, request);
				}
			}

			if(request->arguments["action"] == "delete")
			{
				delete_file(request->arguments["url"], user_name, socket, request, response);
				return;
			}
		}

		if (request->url == "/ufs.json")
		{
			if (boost::iequals(request->arguments["action"], "type"))
			{
				list_user_files_of_type(user_name, request->arguments["type"],  socket, response, request);
				return;
			}

			if(is_request_to_file_info(user_name, socket, request, response))
				return;

			list_user_files(user_name, socket, response, request);
			return;
		}

		if(request->arguments["user_name"] == "true")
		{
			http_utils::send_json( std::pair<std::string, std::string>("user_name", user_name), socket, response, request);
			return;
		}
	}

	std::map<std::string, std::string>::iterator redirect_iterator= request->arguments.find("redirect_to");
	if (redirect_iterator != request->arguments.end() )
	{
		http_utils::send_found_302(	http_utils::url_decode(redirect_iterator->second), socket, response, request);
		return;
	}

	if(is_request_to_file_info(user_name, socket, request, response))
		return;

	bool sent;
	try{
		sent = send_file(request->url, user_name, socket, request, response);
		if (!sent)
		{
			fs_utils::send_404(request->url, socket, request, response, shared_data);
		}
	}
	catch(...)
	{
		fs_utils::send_404(request->url, socket, request, response, shared_data);
	}
}

bool users_files_service::is_request_to_file_info(std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	if (request->url == "/ufs.json")
	{
		if (boost::iequals(request->arguments["action"], "file_info"))
		{
			std::string url_requested =  request->arguments["url"];
			if (url_requested != "")
			{
				if(send_file_info(url_requested, user_name, socket, request, response))
					return true;

				http_utils::send_json_error("this file is not available for you", socket, response, request);
				return true;
			}
		}
	}
	return false;
}

bool users_files_service::send_file(std::string file_name, boost::filesystem::path path, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	boost::shared_ptr<fs_file> f = fs_utils::create_file(path);
	response->headers.insert(std::pair<std::string, std::string>("Content-Disposition", std::string("attachment; filename=" + file_name)));

	fs_utils::send_uncachable_file(f, socket,request, response);
	return true;
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
			std::string  file_name, f_user_name, modified, f_type;
			(*i).getter() >> file_name >> f_user_name >>  is_public >> modified >> f_type;

			if (is_public || (f_user_name == user_name))
			{
				std::string type = "." + f_type;
				if (boost::filesystem::extension(file_name) != type)
				{
					file_name = file_name + type;
				}
				return users_files_service::send_file(file_name, boost::filesystem::path(root_path / href), socket, request, response);
			}
			return false;
		}

	}
	return false;
}


bool users_files_service::send_file_info( std::string href, std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	sqlite3pp::transaction xct(*db, true);
	{
		sqlite3pp::query qry(*db, this->command_find_file.c_str());
		qry.bind(":encoded_url", href);
		//file_name, user_name, is_public, modifie
		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			bool is_public=false;
			std::string  file_name, f_user_name, modified, f_type;
			(*i).getter() >> file_name >> f_user_name >>  is_public >> modified >> f_type;

			if (is_public || (f_user_name == user_name))
			{
				std::ostringstream user_files_stream;

				user_files_stream << "{\n\t\"href\": \""
					<< href << "\",\n\t\"title\": \""
					<< http_utils::escape(file_name) <<  "\",\n\t\"modified\": \""
					<< modified << "\",\n\t\"type\": \""
					<< f_type << "\",\n\t\"is_public\": "
					<< is_public << "\n},";

				std::string files_ = user_files_stream.str();
				if (files_.length() > 5)
					files_ = files_.substr(0, files_.length() - 1);
				http_utils::set_json_content_type(response);
				http_utils::send(files_, socket, response, request);
				return true;
			}
			return false;
		}
	}
	return false;
}

bool users_files_service::delete_file( std::string href, std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
				bool deleted = delete_file(href,user_name);
				if(deleted == true)
					http_utils::send_json(std::pair<std::string, std::string>("success","true"),  socket, response, request); 
				else
					http_utils::send_json(std::pair<std::string, std::string>("success","false"),  socket, response, request); 

				return deleted;
}

bool users_files_service::delete_file( std::string href, std::string user_name)
{
	sqlite3pp::transaction xct(*db, true);
	{
		sqlite3pp::query qry(*db, this->command_find_file.c_str());
		qry.bind(":encoded_url", href);
		//file_name, user_name, is_public, modifie
		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			bool is_public=false;
			std::string  file_name, f_user_name, modified, f_type;
			(*i).getter() >> file_name >> f_user_name >>  is_public >> modified >> f_type;

			if (f_user_name == user_name)
			{
				sqlite3pp::command cmd(*db, this->command_delete_file.c_str());
				cmd.bind(":encoded_url", href);
				if(cmd.execute() == 0)
				{
					boost::filesystem::remove(boost::filesystem::path(this->root_path / href));
					return true;
				}
			}
		}
	}
	return false;
}



void users_files_service::list_user_files( std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
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
	http_utils::set_json_content_type(response);
	http_utils::send(files_.append("\n]"), socket, response, request);
	return;
}

void users_files_service::list_user_files_of_type( std::string user_name,  std::string f_type, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
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
				<< f_size <<  ",\n\t\t\"type\": \"" 
				<< f_type <<"\"\n\t},";
		}

	}
	std::string files_ = user_files_stream.str();
	if (files_.length() > 5)
		files_ = files_.substr(0, files_.length() - 1);
	http_utils::set_json_content_type(response);
	http_utils::send(files_.append("\n]"), socket, response, request);
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

std::string users_files_service::service_check( boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data )
{
	std::string url_extension = request->url.substr(request->url.find_last_of(".") + 1);
	std::string url= request->url;
	if (url == "/ufs.service" || url == "/ufs.json" || url_extension == "file")
	{
		return "executor";
	}
	return "not for me";
}
BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<base_service> > &factories(types.get());
	factories["users_files_service"].set<users_files_service>();
}