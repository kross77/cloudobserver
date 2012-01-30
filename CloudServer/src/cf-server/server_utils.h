// OJ 2011

#ifndef SERVER_UTILITIES_H
#define SERVER_UTILITIES_H 

//STD
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <functional>

//Boost
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp> // aka std::shared_ptr
#include <boost/unordered_map.hpp> // aka std::unordered_map
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

//General Service header Class\Interface
#include <service.hpp>

//Extension includes
#include <extension_utils.h>

//containers thread safe operations
#include <threading_utils.h>
//Thread safe logging
#include <log_util.h>

class server_utils
{
public:

	server_utils();

	~server_utils();

	//Each service provides us with rules
	struct service_container
	{
		service_container() : service_ptr(new empty_service(), boost::bind(&pointer_utils::delete_ptr<base_service>, _1))
		{
		}
		//A service must have
		boost::shared_ptr<base_service> service_ptr;
		std::string library_name;
		std::string class_name;
		std::string service_name;
		std::string root_file_system_directory;

		std::string description_type;
		std::string description_text;
		std::string description_icon_file_path;
		std::string description_default_url_path;

		boost::shared_mutex edit_mutex_;

		boost::property_tree::ptree service_custome_properties_tree;

		int order;
		std::set<boost::thread::id> threads_ids;
	};

	struct server_description
	{
		int port;

		std::string server_service_url;

		//Database name, DB will be created if it does not exist.
		std::string database_name;

		// Server path (by default app path)
		boost::filesystem::path server_root_path;

		//We keep all services and their rules inside of a map
		std::map<int, boost::shared_ptr<server_utils::service_container> > service_map;
	};

	// Creates class that is inherited from service class\interface, we plan to send to each service server_description with out service_map but with this wary service ptree description
	// Main point is for the service to get as much as possible information about its host server, its own configuration.
	boost::shared_ptr<base_service> create_service(std::string library_name, std::string class_name_inside_lib, boost::property_tree::ptree config); 

	server_utils::server_description parse_config(boost::property_tree::ptree config); 

	boost::shared_ptr<base_service> get_service_by_name(std::string name);
	boost::shared_ptr<server_utils::service_container> get_service_description_by_name(std::string name);

	std::multiset<std::string> get_services_names();
	std::multiset<std::string> get_services_class_names();
	std::multiset<std::string> get_services_libraries_names();

	threading_utils *tread_util; 
	server_description description;
	log_util *warning, *info, *error;
	std::list<int> services_ids;
private:

	std::map<int, boost::shared_ptr<server_utils::service_container> > parse_config_services( boost::property_tree::ptree config );
	// For services creation from shared libraries
	threading_utils *tread_util_local; 
	std::stringstream log;

	std::string tag_service;
	std::string tag_library_name;
	std::string tag_service_name;
	std::string tag_class_name;
	std::string tag_url;
	std::string tag_settings;
	std::string tag_configuration;
	std::string tag_path_configuration_services;
	std::string tag_path_configuration_server_root_path;
	std::string tag_path_configuration_port;
	std::string tag_path_configuration_server_service_url;
	std::string tag_path_configuration_database;
	std::string tag_path_configuration_properties_manager;

	std::string tag_description;
	std::string tag_description_type;
	std::string tag_description_text;
	std::string tag_description_icon;
	std::string tag_description_default_url;
	std::string tag_default_description_type;
	std::string tag_default_description_text;
	std::string tag_default_description_icon;
	std::string tag_default_description_url;

	template<class T>
	inline T &empty_class()
	{
		static T pt;
		return pt;
	}

};

#endif // SERVER_UTILITIES_H
