#include "user_control.h"

user_control::user_control(std::string DB_name)
{
	general_util = new general_utils();
	threading_util = new threading_utils();

	//Grammar
	tag_login = "login";
	tag_register = "register";
	tag_pass_sha256 = "pass";
	//tag_session_sha256 = "session-id";
	tag_set_cookie = "Set-Cookie";
	tag_cookie = "Cookie";
	tag_cookie_name = "session-id";
	tag_header_email = "email";
	tag_guest_name = "guest";
	tag_logout = "logout";
	tag_update = "update";

	command_create_users_table = "CREATE TABLE IF NOT EXISTS users (email varchar(65) UNIQUE NOT NULL primary key, pass varchar(65))";
	command_create_user =  "INSERT INTO users (email, pass) VALUES (?, ?)";
	command_find_user = "SELECT email, pass FROM users WHERE email=";

	//SQLite
	boost::shared_ptr<sqlite3pp::database> db_( new sqlite3pp::database(DB_name.c_str())); //I could not get `db = new sqlite3pp::database(DB_name.c_str());` to compile
	db = db_;
	std::cout << db->execute(command_create_users_table.c_str()) << std::endl;

}

std::map<std::string, std::string> user_control::parse_cookie( std::string cookie_data )
{
	std::map<std::string, std::string> parsed_cookie;
	std::string token, token2;
	std::istringstream iss(cookie_data);
	while ( getline(iss, token, ' ') )
	{
		std::string name, val;
		std::istringstream iss2(token);
		int num = 0 ;
		while ( getline(iss2, token2, '=') )
		{
			if ( num == 0)
			{
				name = token2;
				num++;
			}
			else
			{
				val = token2;
				std::string::iterator it = val.end() - 1;
				if (*it == ';')
					val.erase(it);

			}
		}
		parsed_cookie.insert(std::pair<std::string, std::string>(name, val));
	}
	return parsed_cookie;
}

std::string user_control::is_signed_in_user( std::string session_id_sha256 )
{
	return threading_util->safe_search_in_map< std::string, std::string, std::map<std::string, std::string>::iterator >(session_id_sha256, sessions_map);
}

std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user_control::service_call( boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response> service_response )
{
	typedef std::map<std::string, std::string> map_ss;

	map_ss::iterator arguments_end = user_request->arguments.end();
	map_ss::iterator headers_end = user_request->headers.end();


	map_ss::iterator has_email = user_request->headers.find(tag_header_email);

	if (has_email != headers_end)
	{
		 user_request->headers.erase(has_email);
	}

	map_ss::iterator has_logout = user_request->arguments.find(tag_logout);

	if (has_logout != arguments_end)
	{
		return log_out(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> >(user_request, service_response));
	}

	map_ss::iterator has_update = user_request->arguments.find(tag_update);

	map_ss::iterator has_cookie = user_request->headers.find(tag_cookie);

	if (has_cookie != headers_end){
		std::map<std::string, std::string> parsed_cookie = parse_cookie(has_cookie->second);

		try
		{
			std::map<std::string, std::string>::iterator it =  parsed_cookie.find(tag_cookie_name);
			if (it != parsed_cookie.end())
			{
				std::string session_id = it->second; 
				std::string user_name  = is_signed_in_user(session_id);
				user_request->headers.insert(std::pair<std::string, std::string>(tag_header_email, user_name));
				if ( has_update != arguments_end)
				{
					return update_user(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> >(user_request, service_response));
				}
				return std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> >(user_request, service_response);
			}
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl; 
		}
	}

	map_ss::iterator has_login = user_request->arguments.find(tag_login);
	map_ss::iterator has_register = user_request->arguments.find(tag_register);

	if((has_register != arguments_end) && (has_login != arguments_end))
	{
		throw std::runtime_error("User is trying to register and log in at the same time. violation!");
	}
	else if (has_login != arguments_end)
	{
		return log_in(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> >(user_request, service_response));		
	}
	else if(has_register != arguments_end)
	{
		return register_user(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> >(user_request, service_response));
	}
	else
	{
		return guest_user(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> >(user_request, service_response));
	}

}

boost::shared_ptr<sqlite3pp::query>  user_control::request( std::string query)
{
	general_util->to_lower(query);
	if((query.find("insert") == std::string::npos) && (query.find("delete") == std::string::npos))
	{
		boost::shared_ptr<sqlite3pp::query> sql_query(new sqlite3pp::query(*db, query.c_str()));

		return sql_query;
	}
	else
	{
		throw std::runtime_error("Not allowed query arguments use!");
	}
}

bool user_control::is_registered_user( std::string email, std::string pass_sha256 )
{
	boost::shared_ptr<sqlite3pp::query>  qry = request(command_find_user + "'" + email + "'" + "AND pass=" + "'" + pass_sha256 + "'" );
	if(qry->begin() == qry->end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool user_control::is_registered_user( std::string email )
{
	boost::shared_ptr<sqlite3pp::query>  qry = request(command_find_user + "'" + email + "'");
	if(qry->begin() == qry->end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user_control::guest_user( std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user )
{
	user.first->headers.insert(std::pair<std::string, std::string>(tag_header_email, tag_guest_name));
	return user;
}

std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user_control::log_in( std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user )
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	map_ss::iterator arguments_end = user.first->arguments.end();
	map_ss::iterator has_login =  user.first->arguments.find(tag_login);
	map_ss::iterator has_pass =  user.first->arguments.find(tag_pass_sha256);

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
			session_id = general_util->get_sha256(session_id);

			threading_util->safe_insert<pair_ss ,map_ss>(pair_ss(session_id, has_login->second), sessions_map);

			std::string cookie = tag_cookie_name;
			cookie += "=";
			cookie += session_id;
			this->save_cookie(cookie, user.second);

			user.first->arguments.erase(has_login);
			user.first->arguments.erase(has_pass);
			return user;
		}
		else
		{
			this->guest_user(user);
			throw std::runtime_error("Unregistred user!");
		}
	}
	else
	{
		this->guest_user(user);
		throw std::runtime_error("No password found!");
	}
}

boost::shared_ptr<http_response> user_control::save_cookie( std::string cookie_data , boost::shared_ptr<http_response> response )
{
	typedef std::pair<std::string, std::string> pair_ss;
	response->headers.insert(pair_ss(tag_set_cookie, cookie_data));
	return response;
}

std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user_control::log_out( std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user )
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	map_ss::iterator headers_end = user.first->headers.end();
	map_ss::iterator has_cookie = user.first->headers.find(tag_cookie);

	if (has_cookie != headers_end){
		std::map<std::string, std::string> parsed_cookie = parse_cookie(has_cookie->second);

		try
		{
			std::map<std::string, std::string>::iterator it =  parsed_cookie.find(tag_cookie_name);
			if (it != parsed_cookie.end())
			{
				std::string session_id = it->second; 
				threading_util->safe_erase< std::string, std::map<std::string, std::string> >(session_id, sessions_map);
			}
		}
		catch(std::exception &e)
		{}
	}

	std::string tag_expired_date = "Expires=Wed, 09 Jun 2001 10:18:14 GMT";
	std::string cookie = tag_cookie_name + "=" + "0" + "; " + tag_expired_date;

	this->save_cookie(cookie, user.second);

	user.first->arguments.erase(user.first->arguments.find(tag_logout));
	return guest_user(user);
}

std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user_control::register_user( std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user )
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	map_ss::iterator arguments_end = user.first->arguments.end();
	map_ss::iterator has_register =  user.first->arguments.find(tag_register);
	map_ss::iterator has_pass =  user.first->arguments.find(tag_pass_sha256);

	if (has_pass != arguments_end)
	{
		if (!is_registered_user(has_register->second))
		{
			sqlite3pp::transaction xct(*db);
			std::string command_string = "INSERT INTO users (email, pass) VALUES ('" + has_register->second + "', '" +  has_pass->second + "')";
			sqlite3pp::command cmd(*db, command_string.c_str());
			std::cout << cmd.execute() << std::endl;
			xct.commit();

			user.first->arguments.insert(std::pair<std::string, std::string>(tag_login, has_register->second));
			user.first->arguments.erase(has_register);
			return this->log_in(user);
		}
		else
		{
			this->guest_user(user);
			throw std::runtime_error("User already exists!");
		}
	}
	else
	{
		this->guest_user(user);
		throw std::runtime_error("No password provided!");
	}
}

std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user_control::update_user( std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user )
{
	typedef std::map<std::string, std::string> map_ss;
	typedef std::pair<std::string, std::string> pair_ss;

	map_ss::iterator arguments_end = user.first->arguments.end();
	map_ss::iterator has_pass =  user.first->arguments.find(tag_pass_sha256);

	std::string user_name = user.first->headers.find(tag_header_email)->second;

	if(has_pass != arguments_end)
	{
		if(this->is_registered_user(user_name, has_pass->second))
		{
			sqlite3pp::transaction xct(*db);
			std::string command_string = "UPDATE users SET pass='"+ user.first->arguments.find(tag_update)->second + "' WHERE email='" + user_name + "')";
			sqlite3pp::command cmd(*db, command_string.c_str());
			std::cout << cmd.execute() << std::endl;
			xct.commit();

			user.first->arguments.erase(user.first->arguments.find(tag_update));
			user.first->arguments.erase(has_pass);
			return user;
		}
		else
		{
			this->guest_user(user);
			throw std::runtime_error("Not registered user!");
		}
	}
	else
	{
		this->guest_user(user);
		throw std::runtime_error("No original password provided!");
	}

}