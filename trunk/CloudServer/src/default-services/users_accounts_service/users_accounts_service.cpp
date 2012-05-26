#include "users_accounts_service.h"

users_accounts_service::users_accounts_service()
{
	threading_util = new threading_utils();
	sid_map_threading_util = boost::shared_ptr<threading_utils>(new threading_utils());
	is_db_set = false;
	is_lu_set = false;
	//Grammar
	default_lu_path = "log.txt";
	default_db_name = "server.db";
	use_recapcha = true;

	tag_login = "login";
	tag_register = "register";
	tag_pass_sha256 = "pass";
	//tag_session_sha256 = "session-id";
	tag_cookie = "Cookie";
	tag_cookie_name = "session-id";
	tag_header_email = "email";
	tag_guest_name = "guest";
	tag_logout = "logout";
	tag_update = "update";
	tag_user_control = "user_control";

	recapcha_server_url = "http://www.google.com/recaptcha/api/verify";
	recapcha_server_key = "6LdRhsYSAAAAACWFAY14BsbhEe0HzOMayMMfAYdj";
	tag_recaptcha_challenge_field = "recaptcha_challenge_field";
	tag_recaptcha_response_field = "recaptcha_response_field";

	tag_recaptcha_challenge_for_post = "challenge";
	tag_recaptcha_remoteip_for_post = "remoteip";
	tag_recaptcha_privatekey_for_post = "privatekey";
	tag_recaptcha_response_for_post = "response";

	command_create_users_table = "CREATE TABLE IF NOT EXISTS users (email varchar(100) UNIQUE NOT NULL primary key, pass varchar(100))";
	command_create_user =  "INSERT INTO users (email, pass) VALUES (:user_name, :pass)";
	command_find_user = "SELECT email, pass FROM users WHERE email=:email";
	
	service_session_id ="service_session_id";

}

users_accounts_service::~users_accounts_service()
{
	delete threading_util;
	delete lu;
}

std::string users_accounts_service::is_signed_in_user( std::string session_id_sha256 )
{
	return threading_util->safe_search_in_map< std::string, std::string, std::map<std::string, std::string>::iterator >(session_id_sha256, sessions_map);
}

void users_accounts_service::service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request,  boost::shared_ptr<shared> shared_data)
{
	typedef std::map<std::string, std::string> map_ss;

	map_ss::iterator arguments_end = user_request->arguments.end();
	map_ss::iterator headers_end = user_request->headers.end();

	boost::shared_ptr<http_response> service_response(new http_response(), boost::bind(&pointer_utils::delete_ptr<http_response>, _1));

	map_ss::iterator has_email = user_request->headers.find(tag_header_email);
	
	if (has_email != headers_end)
	{
		user_request->headers.erase(has_email);
	}

	map_ss::iterator has_logout = user_request->arguments.find(tag_logout);

	if (has_logout != arguments_end)
	{
		return log_out(socket, user_request, service_response);
	}

	try
	{
		if ((shared_data->get("UAC service call")).empty())
		{
			std::string user_name  = shared_data->get("user_name");
			if (user_name.empty())
			{
				user_request->arguments.insert(std::pair<std::string, std::string>(tag_logout, "true"));
				return log_out(socket, user_request, service_response);
			}
			std::map<std::string, std::string>::iterator it =  user_request->cookies.find(tag_cookie_name);	
			if (it != user_request->cookies.end())
				user_request->cookies.erase(it);

			map_ss::iterator has_update = user_request->arguments.find(tag_update);
			if ( has_update != arguments_end)
			{
				return update_user(socket, user_request, service_response, shared_data);
			}
			return;
		}
	}
	catch(std::exception &e)
	{
		user_request->arguments.insert(std::pair<std::string, std::string>(tag_logout, "true"));
		return log_out(socket, user_request, service_response);
	}
	

	std::string service_action = user_request->arguments[tag_user_control];

	if ( service_action == tag_login)
	{
		return log_in(socket, user_request, service_response);		
	}

	if( service_action == tag_register)
	{
		return register_user(socket, user_request, service_response);
	}

	return guest_user(socket, user_request, service_response);

}

bool users_accounts_service::is_registered_user( std::string & given_email, std::string & pass_sha256 )
{
	/* TODO: use Boost::Locale!!!
	boost::locale::generator gen;
	std::locale loc=gen(""); 
	std::locale::global(loc); 
	std::stringstream u_name;
	u_name.imbue(loc);
	u_name << boost::locale::to_lower(has_register->second);
	has_register->second = u_name.str();
	*/
	boost::algorithm::to_lower(given_email);
	given_email = http_utils::url_decode(given_email);
	given_email = http_utils::url_encode(given_email);

	std::string email="", pass="";
	sqlite3pp::transaction xct(*db, true);
	{
		sqlite3pp::query qry(*db, this->command_find_user.c_str());
		qry.bind(":email", given_email);

		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			bool is_public;
			(*i).getter() >> email >> pass ;
		}

	}

	std::string given_pass = general_utils::get_sha256(pass_sha256);
	if (given_pass == pass)
	{
		return true;
	}

	return false;

}

bool users_accounts_service::is_registered_user( std::string & given_email )
{
	if (given_email == "")
	{
		return false;
	}
	
	/* TODO: use Boost::Locale!!!
	boost::locale::generator gen;
	std::locale loc=gen(""); 
	std::locale::global(loc); 
	std::stringstream u_name;
	u_name.imbue(loc);
	u_name << boost::locale::to_lower(has_register->second);
	has_register->second = u_name.str();
	*/
	boost::algorithm::to_lower(given_email);
	given_email = http_utils::url_decode(given_email);
	given_email = http_utils::url_encode(given_email);

	std::string email="", pass="";

	sqlite3pp::transaction xct(*db, true);
	{
		sqlite3pp::query qry(*db, this->command_find_user.c_str());
		qry.bind(":email", given_email);

		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			bool is_public;
			(*i).getter() >> email >> pass ;
		}

	}

	if (given_email == email)
	{
		return true;
	}

	return false;
}

void users_accounts_service::guest_user( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response)
{
	if(! http_utils::try_to_redirect(socket, user_request, user_response))
		http_utils::send_found_302(	user_request->url, socket, user_response, user_request);
}

void users_accounts_service::log_in(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response )
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	map_ss::iterator arguments_end = user_request->arguments.end();
	map_ss::iterator has_login =  user_request->arguments.find(tag_login);
	map_ss::iterator has_pass =  user_request->arguments.find(tag_pass_sha256);

	if (has_pass != arguments_end)
	{
		if(this->is_registered_user(has_login->second, has_pass->second))
		{
			boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
			std::ostringstream formatter;
			formatter.imbue(std::locale(std::cout.getloc(), new boost::posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT")));
			formatter << now;
			std::string session_id = formatter.str();
			session_id += has_login->second;
			session_id = general_utils::get_sha256(session_id);

			threading_util->safe_insert<pair_ss ,map_ss>(pair_ss(session_id, has_login->second), sessions_map);

			std::string cookie = tag_cookie_name;
			cookie += "=";
			cookie += session_id;
			http_utils::save_cookie(cookie, user_response);

			user_request->arguments.erase(has_login);
			user_request->arguments.erase(has_pass);
		}
		else
		{
			this->guest_user(socket, user_request, user_response);
			throw std::runtime_error("Unregistred user!");
		}
	}
	else
	{
		this->guest_user(socket, user_request, user_response);
		throw std::runtime_error("No password found!");
	}
	http_utils::try_to_redirect(socket, user_request, user_response);
}

void users_accounts_service::log_out(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response )
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	try
	{
		std::map<std::string, std::string>::iterator it =  user_request->cookies.find(tag_cookie_name);
		if (it !=  user_request->cookies.end())
		{
			std::string session_id = it->second;
			threading_util->safe_erase_in_map< std::string, std::map<std::string, std::string> >(session_id, sessions_map);
		}
	}
	catch(std::exception &e)
	{}
	
	std::string tag_expired_date = "Expires=Wed, 09 Jun 2001 10:18:14 GMT";
	std::string cookie = tag_cookie_name + "=" + "0" + "; " + tag_expired_date;

	http_utils::save_cookie(cookie, user_response);

	try
	{
		user_request->arguments.erase(user_request->arguments.find(tag_logout));
	}
	catch(std::exception &e)
	{}

	guest_user(socket, user_request, user_response);
}

void users_accounts_service::register_user( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response )
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	map_ss::iterator arguments_end = user_request->arguments.end();
	map_ss::iterator has_register =  user_request->arguments.find(tag_register);
	map_ss::iterator has_pass =  user_request->arguments.find(tag_pass_sha256);

	if (has_pass != arguments_end)
	{
		if (has_pass->second == "")
		{
			throw std::runtime_error("Bad User Pass!");
		}

		if (has_register->second == "")
		{
			throw std::runtime_error("Bad User Name!");
		}
		has_register->second = http_utils::url_decode(has_register->second);
		has_register->second = http_utils::url_encode(has_register->second);
		if (!is_registered_user(has_register->second))
		{
			if (use_recapcha)
			{
				try{
					this->check_recaptcha( socket, user_request, user_response );
				}
				catch(std::exception &e)
				{
					user_request->arguments.erase(has_register);
					user_request->arguments.erase(has_pass);
					return this->guest_user(socket, user_request, user_response);
				}
			}

			sqlite3pp::transaction xct(*db);

			sqlite3pp::command cmd(*db, command_create_user.c_str());

			cmd.bind(":user_name", has_register->second);
			cmd.bind(":pass", general_utils::get_sha256(has_pass->second) );
			std::cout << cmd.execute() << std::endl;
			xct.commit();

			user_request->arguments.insert(std::pair<std::string, std::string>(tag_login, has_register->second));
			user_request->arguments.erase(has_register);
			return this->log_in(socket, user_request, user_response);
		}
		else
		{
			this->guest_user(socket, user_request, user_response);
			throw std::runtime_error("User already exists!");
		}
	}
	else
	{
		this->guest_user(socket, user_request, user_response);
		throw std::runtime_error("No password provided!");
	}
}

void users_accounts_service::update_user(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response, boost::shared_ptr<shared> shared_data )
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	map_ss::iterator arguments_end = user_request->arguments.end();
	map_ss::iterator has_pass =  user_request->arguments.find(tag_pass_sha256);

	std::string user_name = shared_data->get("user_name");

	if(has_pass != arguments_end)
	{
		if(this->is_registered_user(user_name, has_pass->second))
		{
			sqlite3pp::transaction xct(*db);
			std::string command_string = "UPDATE users SET pass='"+ user_request->arguments.find(tag_update)->second + "' WHERE email='" + user_name + "')";
			sqlite3pp::command cmd(*db, command_string.c_str());
			std::cout << cmd.execute() << std::endl;
			xct.commit();

			user_request->arguments.erase(user_request->arguments.find(tag_update));
			user_request->arguments.erase(has_pass);
		}
		else
		{
			this->guest_user(socket, user_request, user_response);
			throw std::runtime_error("Not registered user!");
		}
	}
	else
	{
		this->guest_user(socket, user_request, user_response);
		throw std::runtime_error("No original password provided!");
	}
	http_utils::try_to_redirect(socket, user_request, user_response);

}

void users_accounts_service::apply_config( boost::shared_ptr<boost::property_tree::ptree> config )
{
	this->default_lu_path = config->get<std::string>("log_util_file", this->default_lu_path);
	this->default_db_name = config->get<std::string>("database", this->default_db_name);
	this->use_recapcha = config->get<bool>("use_recapcha", this->use_recapcha);
	this->recapcha_server_key = config->get<std::string>("recapcha_server_key", this->recapcha_server_key);
	this->recapcha_server_url = config->get<std::string>("recapcha_server_url", this->recapcha_server_url);
	start_work_with_lu( this->default_lu_path);
	start_work_with_db(this->default_db_name);
}

void users_accounts_service::start_work_with_lu( std::string lu_path )
{
	if (!is_lu_set)
	{
		lu = new log_util(50, false, true, true, lu_path);
		is_lu_set = true;
	}

}

void users_accounts_service::start_work_with_db( std::string db_name )
{
	if (!is_db_set) // TODO: find out how to detach from one db and connect to another.
	{
		boost::shared_ptr<sqlite3pp::database> db_( new sqlite3pp::database(db_name.c_str())); //I could not get `db = new sqlite3pp::database(DB_name.c_str());` to compile
		db = db_;
		*lu << "Connected to "<< db_name << " database and created a table with SQLite return code: " << db->execute(command_create_users_table.c_str()) << log_util::endl;
	}
}

void users_accounts_service::check_recaptcha(  boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response)
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	map_ss::iterator arguments_end = user_request->arguments.end();

	map_ss::iterator has_recaptcha_challenge_field = user_request->arguments.find(tag_recaptcha_challenge_field);
	if (has_recaptcha_challenge_field == arguments_end)
	{
		throw std::runtime_error("no recaptcha challenge id field!");
	}

	map_ss::iterator has_recaptcha_response_field = user_request->arguments.find(tag_recaptcha_response_field);
	if (has_recaptcha_response_field == arguments_end)
	{
		throw std::runtime_error("no recaptcha response field!");
	}

	map_ss to_recaptcha;

	to_recaptcha.insert(pair_ss(tag_recaptcha_response_for_post,has_recaptcha_response_field->second));
	to_recaptcha.insert(pair_ss(tag_recaptcha_challenge_for_post, has_recaptcha_challenge_field->second));

	to_recaptcha.insert(pair_ss(tag_recaptcha_privatekey_for_post, this->recapcha_server_key));

	boost::asio::ip::tcp::endpoint remote_endpoint = socket->remote_endpoint();
	boost::asio::ip::address addr = remote_endpoint.address();
	std::string addr_string = addr.to_string();
	to_recaptcha.insert(pair_ss(tag_recaptcha_remoteip_for_post, addr_string));

	http_request request_to_recap;

	request_to_recap.body = http_utils::map_to_post_without_escape(to_recaptcha);
	request_to_recap.headers.insert(pair_ss("Content-Type", "application/x-www-form-urlencoded;"));
	request_to_recap.headers.insert(pair_ss("User-Agent", "reCAPTCHA/CloudForever"));
	request_to_recap.headers.insert(pair_ss("Connection","close"));
	//	request_to_recap.headers.insert(pair_ss("Content-Length", boost::lexical_cast<std::string>(request_to_recap.body.size())));
	request_to_recap.method = "POST";

	std::string cap_err_recaptcha_not_reachable = "recaptcha-not-reachable";
	std::string cap_err_invalid_site_private_key = "invalid-site-private-key";
	std::string cap_err_invalid_request_cookie = "invalid-request-cookie";
	std::string cap_err_incorrect_captcha_sol = "incorrect-captcha-sol";

	http_response response;
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket socket(io_service);
		response.receive(request_to_recap.send(this->recapcha_server_url, socket));
	}
	catch(std::exception &e)
	{
		throw std::runtime_error( "unable to contact the reCAPTCHA verify server.");
	}
	std:: cout << "captcha responded: " << std::endl << response.body << std::endl;

	if (response.body.find("success") != std::string::npos)
	{
		user_request->arguments.erase(has_recaptcha_response_field);
		user_request->arguments.erase(has_recaptcha_challenge_field);
	}

	if( response.body.find(cap_err_invalid_site_private_key) != std::string::npos)
	{
		throw std::runtime_error("We weren't able to verify the private key. \n Possible Solutions: \n \t Did you swap the public and private key? It is important to use the correct one \n \t Did you make sure to copy the entire key, with all hyphens and underscores, but without any spaces? The key should be exactly 40 characters long.");
	}
	if( response.body.find(cap_err_invalid_request_cookie) != std::string::npos)
	{
		throw std::runtime_error("The challenge parameter of the verify script was incorrect.");
	}
	if( response.body.find(cap_err_incorrect_captcha_sol) != std::string::npos)
	{
		throw std::runtime_error("The CAPTCHA solution was incorrect.");
	}
}

std::string users_accounts_service::service_check( boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data )
{
	typedef std::map<std::string, std::string> map_ss;
	map_ss::iterator it;

	it = request->headers.find(service_session_id);

	if (it != request->headers.end())
	{
		std::string user_name = sid_map_threading_util->safe_search_in_map<std::string, std::string, boost::unordered_map<std::string, std::string>::iterator >(request->headers[service_session_id], service_calls_map);
		if(user_name.empty())
		{
			sid_map_threading_util->safe_erase_in_map<std::string, boost::unordered_map<std::string,std::string> >(request->headers[service_session_id], service_calls_map);
			return "executor";
		}

		shared_data->post("user_name", http_utils::url_decode(user_name));
		sid_map_threading_util->safe_erase_in_map<std::string, boost::unordered_map<std::string,std::string> >(request->headers[service_session_id], service_calls_map);
		return "assistant";
	}

	it = request->cookies.find(tag_cookie_name);
	if (it != request->cookies.end())
	{
		std::string user_name =  is_signed_in_user(it->second);
		if (user_name.empty())
		{
			return "executor";
		}
		shared_data->post("user_name", http_utils::url_decode(user_name));
		return "assistant";
	}

	std::string url= request->url;
	if (url == "/uac.service" )
	{
		shared_data->post("UAC service call", "true");
		return "executor";
	}

	return "not for me";
}

void users_accounts_service::serialize(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> old_http_request, boost::shared_ptr<shared> shared_data, boost::shared_ptr<http_request> new_http_request)
{
	std::string user_name = (*shared_data).get("user_name");
	if( !user_name.empty()){
		std::string request_id = general_utils::get_sha256(http_utils::url_encode(user_name + boost::posix_time::to_iso_extended_string(boost::posix_time::second_clock::local_time())));
		sid_map_threading_util->safe_insert<std::pair<std::string,std::string>, boost::unordered_map<std::string,std::string> >(std::make_pair(request_id, user_name), service_calls_map);
		new_http_request->headers[service_session_id] = request_id;
	}

}

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<base_service> > &factories(types.get());
	factories["users_accounts_service"].set<users_accounts_service>();
}
