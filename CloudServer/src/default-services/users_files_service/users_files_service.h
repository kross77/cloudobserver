#ifndef USERS_FILES_SERVICE_H
#define USERS_FILES_SERVICE_H

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
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
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

#include <http_service.hpp>

/*!
 * \brief Users Files Sharing service featuring files protection from any one on the web as well as public access provision
 *
 * responds to \c /ufs.service, \c /ufs.json urls and all urls with \c file extension
 * 
 * \note creates a directory ( default \c ./ufs)
 * \note creates sqlite database file ( default \c ./ufs.db)
 */
class users_files_service: public http_service
{ 
public:

	/*!
	 * \brief Creates database file and folder if they do not exist yet 
	 *
	 * \n FullName:  users_files_service::users_files_service
	 * \n Access:    public  
	 * \sa apply_config
	 *
	 */
	users_files_service();

	/*!
	 * \brief Checks if service applies to request
	 * 
	 * inspects request for \c /ufs.service; \c /ufs.json absolute urls and \c .file extension)
	 *
	 * \n FullName:  users_files_service::service_check
	 * \n Access:    virtual public  
	 *
	 * \param request boost::shared_ptr<http_request>
	 * \param shared_data boost::shared_ptr<shared>
	 * \return std::string 
	 * \sa service_call
	 * \note inspects for absolute urls except ending with `.file`
	 *
	 */
	virtual std::string service_check(boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data);
		
	/*!
	 * \brief Main UFS service function - resolves requests.
	 * 
	 *  \b GET \b requests to \b UFS:\n
	 *  - you can obtain your name with request argument:\n
	 *		- \c user_name : \c string;\n
	 *  - or redirect to any location with request argument:\n
	 *		- \c redirect_to : \c string;\n
	 *  - or get a personal file info with request arguments submited to url `/ufs.json`:\n
	 *		- \c action = \c file_info,\n
	 *		- \c url : \c string;\n
	 *  - even delete personal file with request arguments submited to url `/ufs.service`:\n
	 * 		- \c action = \c delete,\n
	 * 		- \c url : \c string;\n		
	 * 		
	 * \b AJAX \b requests to url `/ufs.service`:\n
	 *	- via method keyword : \c POST \n
	 *		- you can upload a file: \n
	 *			- with arguments:\n
	 *				- \c action = \c upload,\n
	 *				- \c is_public : \c bool (\c true/false ),\n
	 *				- \c type: \c string,\n
	 *				- \c name : \c string\n
	 *			- and with file contents (!only) inside request body;\n
	 *			only \c action argument and body contents are required.\n
	 *		- you can delete multiple files: \n
	 *			- with arguments:\n
	 *				- \c action = \c delete;\n
	 *			- and with array of file uri's in request body separated via  {", "};\n
	 *			
	 * All user pure \b POST requests to UFS shall be for file upload. \n
	 * To upload a file all required is to send its contents. \n
	 * Also we can save provided file \c name, \c policy and \c type. \n
	 * We provide response in JSON format:  \c {success:true} or  \c  {success:false}. \n
	 * If \c redirect_location is provided and request was processed with out any errors 
	 * instead of responding in JSON format we redirect user forward to requested location. \n
	 * 
	 *  \b POST arguments API:\n
	 *	- required: \n
	 *		- \c datafile : data (as \c string)\n
	 *	- can be processed:\n
	 *		- \c file_name : \c string,\n
	 *		- \c redirect_location : \c string,\n
	 *		- \c is_public : \c bool (as a \c string).\n
	 *
	 * \n FullName:  users_files_service::service_call
	 * \n Access:    virtual public  
	 *
	 * \param socket boost::shared_ptr<boost::asio::ip::tcp::socket>
	 * \param request boost::shared_ptr<http_request>
	 * \param shared_data boost::shared_ptr<shared>
	 * \return void 
	 * \note should not throw anything if all goes OK
	 * \sa service_check
	 */
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request,  boost::shared_ptr<shared> shared_data);

	/*!
	 * \brief configuration of a UFS service
	 * 
	 * looks for:\n
	 *	- \c users_files_directory : path (\c string);\n
	 *	- \c extension : default files extension (\c string);\n
	 *	- \c log_util_file : path (\c string);\n
	 *	- \c database : db name (\c string);\n
	 * in provided ptree.\n
	 *
	 * \n FullName:  users_files_service::apply_config
	 * \n Access:    virtual public  
	 *
	 * \param config boost::shared_ptr<boost::property_tree::ptree>
	 * \return void 
	 *
	 */
	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config);

	virtual void start(){}
	virtual void stop(){}

private:

	void list_user_files( std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request );
	void list_user_files_of_type( std::string user_name, std::string f_type, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request );
	void create_file_table_entry( std::string encoded_url, std::string file_name, std::string user_name, std::string f_type, int f_size, bool is_public );
	void create_log_util( std::string lu_path );

	void create_files_table( std::string db_name );

	bool send_file( std::string href, std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	bool send_file(std::string file_name, boost::filesystem::path path, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	bool send_file_info( std::string href, std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	
	bool is_request_to_file_info(std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	bool delete_file( std::string href, std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	bool delete_file( std::string href, std::string user_name);
	bool rename_file( std::string href, std::string new_file_name, std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	bool rename_file( std::string href, std::string new_file_name, std::string user_name);
	bool set_file_policy( std::string href, std::string user_name, bool is_public, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	bool set_file_policy( std::string href, std::string user_name, bool is_public);

	boost::filesystem::path root_path;
	boost::shared_ptr<sqlite3pp::database> db;
	bool is_db_set;

	boost::posix_time::time_duration expiration_period;
	boost::shared_ptr<log_util> lu;
	bool is_lu_set;

	std::string max_age;

	std::string tag_ufs_file_types;
	std::string tag_ufs_file_type;
	std::set<std::string> file_types;

	std::string command_create_files_table;
	std::string command_update_file;
	std::string command_rename_file;
	std::string command_set_file_policy;
	std::string command_delete_file;
	std::string command_create_file;
	std::string command_find_file;
	std::string default_db_name;
	std::string command_find_all_user_files;
	std::string command_find_all_user_files_of_type;
	std::string default_lu_path;
	std::string tag_ufs_extension;
	std::string default_ufs_extension;

	template<class T>
	inline T &empty()
	{
		static T pt;
		return pt;
	}
};

#endif // USERS_FILES_SERVICE_H
