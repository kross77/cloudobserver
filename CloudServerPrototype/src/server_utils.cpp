#include "server_utils.h"

server_utils::server_utils()
{
	util = new extension_utils();
	print = new printer();
	this->description.server_root_path = boost::filesystem::current_path();
}

boost::shared_ptr<service> server_utils::create_service(std::string library_name, std::string class_name_inside_lib, boost::property_tree::ptree config)
{
	return util->give_me_class<service, boost::property_tree::ptree>(library_name, class_name_inside_lib, config);
}

std::map<boost::shared_ptr<service>, server_utils::service_description> server_utils::parse_config_services( boost::property_tree::ptree config )
{
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
		config.get_child("config.services", server_utils::empty_class<boost::property_tree::ptree>()))
	{
		boost::property_tree::ptree individual_service_tree = (boost::property_tree::ptree) v.second ;

		std::string service_name = individual_service_tree.get<std::string>("name", "unnamed service");
		std::cout << std::endl << "Service name: " << service_name << std::endl;

		try{
			std::string service_library_name = individual_service_tree.get<std::string>("library_name"); // Will throw error if not defined
			std::cout << "Library name: " << service_library_name << std::endl;


			std::string service_class_name = individual_service_tree.get<std::string>("class_name"); // Will throw error if not defined
			std::cout << "Class name: " << service_class_name << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << std::endl << "Parsing library or class name error in service: " << service_name << std::endl;
			continue;
		}

		std::string service_root_file_system_directory = individual_service_tree.get<std::string>("root_file_system_directory", description.server_root_path.string());
		std::cout << "Root directory path: " << service_root_file_system_directory << std::endl;

		boost::property_tree::ptree service_properties_tree = individual_service_tree.get_child("properties", server_utils::empty_class<boost::property_tree::ptree>());

		std::string root_service_web_path = service_properties_tree.get<std::string>("root_service_web_path", "");
		if(!root_service_web_path.empty())
		std::cout << "Service web root directory path: " << root_service_web_path << std::endl;
	

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child("arguments", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			std::cout << "Required argument: " << vp.first.data() << " : " << vp.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child("headers", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			std::cout << "Required header: " << vp.first.data() << " : " << vp.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child("url_extensions", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			std::cout << "Supported url extension: " << vp.second.data() <<  std::endl;
		}
	}

	std::map<boost::shared_ptr<service>, server_utils::service_description> m;
	return m;
}

server_utils::server_description server_utils::parse_config( boost::property_tree::ptree config )
{
	server_utils::server_description server_descr;
	std::cout << std::endl << "Server description: " << std::endl;

	server_descr.server_root_path = config.get("config.server_root_path", boost::filesystem::current_path());
	std::cout << "Server root path: " << server_descr.server_root_path << std::endl;

	server_descr.port = config.get("config.port", 12345);
	std::cout << "Server port: " << server_descr.port << std::endl;

	std::cout << std::endl << "Server services: ";
	server_descr.service_map = server_utils::parse_config_services( config );
	std::cout << std::endl;

	return server_descr;
}