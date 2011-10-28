//if service needs access to server main database it shall be presented with shared_ptr to User Controll class and service shall call request method to search thru DB.

#ifndef USER_CONTROL_H
#define USER_CONTROL_H

//STD
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <locale>

// Boost
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

//SQLite
#include <sqlite3pp.h>

// Cloud Forever
#include <http.h>

#include <threading_utils.h>
#include <general_utils.h>
#include <http_utils.h>
#include <log_util.h>

class user_control
{
public:
	user_control();
	~user_control();

	void apply_config(boost::property_tree::ptree config);

	//This metod shall be called by services to read data from server DB.
	boost::shared_ptr<sqlite3pp::query> request(std::string query);
	//This method shall be called for requests filtering
	std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > service_call( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response> service_response);
private:

	//Case response functions
	std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > register_user(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user);
	std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > update_user(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user);
	std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > log_in(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user);
	std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > log_out(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user);
	std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > guest_user(std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user);


	//User_control functions
	bool is_registered_user(std::string email, std::string pass_sha256);
	bool is_registered_user(std::string email);
	std::string is_signed_in_user(std::string session_id_sha256);

	std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > check_recaptcha( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > user);

	void start_work_with_db(std::string db_name);
	void start_work_with_lu( std::string lu_path );
	//User_control variables
	std::map<std::string,std::string> sessions_map; // session_id to name
	boost::shared_ptr<sqlite3pp::database> db;

	threading_utils *threading_util;
	general_utils *general_util;
	http_utils *http_util;
	log_util *lu;
	

	//Grammar
	std::string default_db_name;
	std::string default_lu_path;

	bool is_lu_set;
	bool is_db_set;

	std::string tag_login;
	std::string tag_register;
	std::string tag_pass_sha256;
	//std::string tag_session_sha256;
	std::string tag_header_email;
	std::string tag_cookie; // TODO get rid of.
	std::string tag_cookie_name;
	std::string tag_guest_name;
	std::string tag_logout;
	std::string tag_update;
	std::string command_create_users_table;
	std::string command_create_user;
	std::string command_find_user;
	std::string recapcha_server_url;
	std::string recapcha_server_key;
	std::string tag_recaptcha_challenge_field;
	std::string tag_recaptcha_response_field;

	std::string tag_recaptcha_challenge_for_post;
	std::string tag_recaptcha_remoteip_for_post;
	std::string tag_recaptcha_privatekey_for_post;
	std::string tag_recaptcha_response_for_post;
	
	bool use_recapcha;

};

#endif // USER_CONTROL_H
