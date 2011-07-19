// OJ 2011
//Usage:
//
//one way to create classes from dll - create all possible classes using factories, tested, works
//
//map<string, factory<Your_Base_Class, Constructor_Argument_T> > producer_factories = get_factories<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance);
//for (map<string, factory<Your_Base_Class, Constructor_Argument> >::iterator it
//	= producer_factories.begin();
//	it != producer_factories.end(); ++it) {
//		cout << "Creating Your_Base_Class using factory: " << it->first << endl;
//		boost::scoped_ptr<Your_Base_Class> current_instance_of_Your)Base_Class(it->second.create(Some_Constructor_Argument_Value));
//		cout << "Created instance of Your Base Class" << 
//			" Lets try it on: " << endl;
//		current_instance_of_Your_Base_Class->Some_Function_From_Your_Base_Class(Argument_Value);
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//another way to create one class from dll by name having factories, tested, works
//
//map<string, factory<Your_Base_Class, Constructor_Argument_T> > producer_factories = get_factories<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance);
//boost::scoped_ptr<Your_Base_Class> producer(producer_factories["BOOST_EXTENSION_TYPE_MAP_FUNCTION_STRING_NAME_DEFINED_IN_LIB"].create(Some_Constructor_Argument_Value));
//current_instance_of_Your_Base_Class->Some_Function_From_Your_Base_Class(Argument_Value);
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//last way is to create a class having only int name (declared in realization)
//
//its prototype interface class and that class constructor argument type and value we want to use
//boost::shared_ptr<Your_Base_Class> producer ( get_class<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance, "BOOST_EXTENSION_TYPE_MAP_FUNCTION_STRING_NAME_DEFINED_IN_LIB", Some_Constructor_Argument_Value));
//

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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

//General Service header Class\Interface
#include "../service-interface/service.hpp"

//Extension includes
#include "extension_utils.h"

//Maps printer
#include "printer.h"

class server_utils
{
public:

	server_utils();

	virtual ~server_utils(){}

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
		std::string root_service_web_path;
		std::set<boost::thread::id> threads_ids;
	};

	struct server_description
	{
		int port;

		// Server path (by default app path) //TODO: make it configurable via config ptree
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

	// For maps contents printing
	printer *print;

	server_description description;

	template <class variable_T, class group_T>
	void safe_insert(variable_T variable, group_T &into)
	{
		boost::mutex::scoped_lock lock(mut);
		into.insert(variable);
	}

	template <class variable_T, class group_T>
	void safe_erase(variable_T variable, group_T &into)
	{
		boost::mutex::scoped_lock lock(mut);
		into.erase(into.find(variable));
	}

private:

	std::map<std::string, boost::shared_ptr<server_utils::service_container> > parse_config_services(boost::property_tree::ptree config);

	// For services creation from shared libraries
	extension_utils *util;

	std::stringstream log;

	std::string tag_service;
	std::string tag_library_name;
	std::string tag_service_name;
	std::string tag_class_name;
	std::string tag_properties;
	std::string tag_root_service_web_path;
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

	mutable boost::mutex mut;

	template<class T>
	inline T &empty_class()
	{
		static T pt;
		return pt;
	}

};

#endif // SERVER_UTILITIES_H
