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
#include <empty_service.hpp>

//Extension includes
#include <extension_utils.h>

//pointer utilities
#include <pointer_utils.h>

//containers thread safe operations
#include <threading_utils.h>
//Thread safe logging
#include <log_util.h>

namespace server_utils
{
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

		std::list<int> services_ids;
	};

	server_utils::server_description parse_config(boost::property_tree::ptree config, log_util * info, log_util * warning, log_util * error); 
	std::map<int, boost::shared_ptr<server_utils::service_container> > parse_config_services(std::list<int> & services_ids, boost::property_tree::ptree config , log_util * info, log_util * warning, log_util * error );	
	// Creates class that is inherited from service class\interface, we plan to send to each service server_description with out service_map but with this wary service ptree description
	// Main point is for the service to get as much as possible information about its host server, its own configuration.
	boost::shared_ptr<base_service> create_service(std::string library_name, std::string class_name_inside_lib, boost::property_tree::ptree config); 

	std::multiset<std::string> get_services_names(server_utils::server_description description);
	std::multiset<std::string> get_services_class_names(server_utils::server_description description);
	std::multiset<std::string> get_services_libraries_names(server_utils::server_description description);

	boost::shared_ptr<base_service> get_service_by_name(std::string name, server_utils::server_description description);
	boost::shared_ptr<server_utils::service_container> get_service_description_by_name(std::string name, server_utils::server_description description);

	//grammar
	const std::string tag_service = "service";
	const std::string tag_library_name = "library_name";
	const std::string tag_service_name = "name";
	const std::string tag_class_name = "class_name";
	const std::string tag_url = "url";
	const std::string tag_settings = "settings";

	const std::string tag_description = "description";
	const std::string tag_description_type = "type" ;
	const std::string tag_description_text = "text";
	const std::string tag_description_icon = "icon";
	const std::string tag_description_default_url = "default_url";

	const std::string tag_default_description_type = "private";
	const std::string tag_default_description_text = "description text";
	const std::string tag_default_description_icon = "default_service_icon.png";
	const std::string tag_default_description_url = "../";

	const std::string tag_configuration = "config";
	const std::string tag_path_configuration_services = "config.services";
	const std::string tag_path_configuration_server_root_path = "config.server_root_path";
	const std::string tag_path_configuration_port = "config.port";
	const std::string tag_path_configuration_server_service_url = "config.server_service_url";
	const std::string tag_path_configuration_database = "config.database";

	template<class T>
	inline T &empty_class()
	{
		static T pt;
		return pt;
	}
};

#endif // SERVER_UTILITIES_H
