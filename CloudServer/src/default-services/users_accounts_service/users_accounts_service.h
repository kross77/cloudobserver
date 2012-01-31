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
#include <boost/algorithm/string.hpp>    

// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

//SQLite
#include <sqlite3pp.h>

// Cloud Forever
#include <http.h>
#include <service.hpp>

#include <threading_utils.h>
#include <general_utils.h>
#include <http_utils.h>
#include <log_util.h>

class users_accounts_service : public service
{
public:
	users_accounts_service();
	~users_accounts_service();

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config);
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket>, boost::shared_ptr<http_request>, boost::shared_ptr<http_response>);
	virtual std::string service_check( boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data );

	virtual void start(){}
	virtual void stop(){}
	//This method shall be called for requests filtering
private:
	//Case response functions
	void register_user(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response);
	void update_user(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response);
	void log_in(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response);
	void log_out(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response);
	void guest_user(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response);


	//User_control functions
	bool is_registered_user(std::string & email, std::string & pass_sha256);
	bool is_registered_user(std::string & email);
	std::string is_signed_in_user(std::string session_id_sha256);

	void check_recaptcha( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> user_request , boost::shared_ptr<http_response>  user_response);

	void start_work_with_db(std::string db_name);
	void start_work_with_lu( std::string lu_path );
	//User_control variables
	std::map<std::string,std::string> sessions_map; // session_id to name
	boost::shared_ptr<sqlite3pp::database> db;

	threading_utils *threading_util;

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
	std::string tag_user_control;
};

#endif // USER_CONTROL_H
