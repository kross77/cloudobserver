// OJ 2011

#ifndef SERVER_UTILITIES_H
#define SERVER_UTILITIES_H 

//STD
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <functional>

//Boost
#include <boost/asio.hpp>
#include <boost/thread.hpp>
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
		//A service must have
		boost::shared_ptr<service> service_ptr;
		std::string library_name;
		std::string class_name;
		std::string root_file_system_directory;
		boost::property_tree::ptree service_custome_properties_tree;

		//A service might have
		std::vector<std::string> set_of_url_rules;
		boost::unordered_multimap<std::string, std::string> set_of_header_rules;
		boost::unordered_multimap<std::string, std::string> set_of_arguments_rules;
		std::set<std::string> url_extensions;
		int default_price;
		std::set<boost::thread::id> threads_ids;
	};

	struct server_description
	{
		int port;

		//Database name, DB will be created if it does not exist.
		std::string database_name;
		
		//Containse pairs of services properties values, used in find_service algorithm
		std::map<std::string, int> properties_manager_map;

		// Server path (by default app path)
		boost::filesystem::path server_root_path;

		//We keep all services and their rules inside of a map
		std::map<std::string, boost::shared_ptr<server_utils::service_container> > service_map;
	};

	//Each request provides us with data
	struct request_data
	{
		std::map<std::string, std::string> headers;
		std::map<std::string, std::string> arguments;
		std::string url_extension;
		std::string url;
	};

	// Creates class that is inherited from service class\interface, we plan to send to each service server_description with out service_map but with this wary service ptree description
	// Main point is for the service to get as much as possible information about its host server, its own configuration.
	boost::shared_ptr<service> create_service(std::string library_name, std::string class_name_inside_lib, boost::property_tree::ptree config); 

	server_utils::server_description parse_config(boost::property_tree::ptree config); 
	boost::property_tree::ptree save_config( server_utils::server_description server_configuration_description); 

	server_utils::request_data parse_request(http_request request); 

	int relevance(boost::shared_ptr<server_utils::service_container> rules_container, const server_utils::request_data &data_container);

	void add_to_services_list(boost::property_tree::ptree config);

	boost::shared_ptr<service> get_service_by_name(std::string name);
	boost::shared_ptr<server_utils::service_container> get_service_description_by_name(std::string name);

	std::multiset<std::string> get_services_names();
	std::multiset<std::string> get_services_class_names();
	std::multiset<std::string> get_services_libraries_names();

	boost::shared_ptr<server_utils::service_container> find_service(http_request request);

	void update_properties_manager();

	threading_utils *tread_util; 
	server_description description;
	log_util *warning, *info, *error;

private:

	std::map<std::string, boost::shared_ptr<server_utils::service_container> > parse_config_services(boost::property_tree::ptree config);
	int find_or_null( std::map<std::string, int> map, std::string to_find);
	// For services creation from shared libraries
	extension_utils *util;
	threading_utils *tread_util_local; 
	std::stringstream log;

	std::string tag_service;
	std::string tag_library_name;
	std::string tag_service_name;
	std::string tag_class_name;
	std::string tag_properties;
	std::string tag_url;
	std::string tag_url_equals;
	std::string tag_url_extensions;
	std::string tag_arguments;
	std::string tag_headers;
	std::string tag_settings;
	std::string tag_configuration;
	std::string tag_path_configuration_services;
	std::string tag_path_configuration_server_root_path;
	std::string tag_path_configuration_port;
	std::string tag_path_configuration_database;
	std::string tag_path_configuration_properties_manager;

	std::string tag_default_price;

	std::string tag_url_extensions_price;
	std::string tag_arguments_price;
	std::string tag_headers_price;
	std::string tag_url_price;

	int default_price;

	int arguments_price;
	int headers_price;
	int url_price;
	int url_extensions_price;


	template<class T>
	inline T &empty_class()
	{
		static T pt;
		return pt;
	}

};

#endif // SERVER_UTILITIES_H
