#include "server_utils.h"

server_utils::server_utils()
{
	util = new extension_utils();
	print = new printer();
	server_root_path = boost::filesystem::current_path();
}

boost::shared_ptr<service> server_utils::create_service(std::string library_name, std::string class_name_inside_lib)
{
	return util->give_me_class<service, boost::filesystem::path>(library_name, class_name_inside_lib, server_root_path);
}

std::map<boost::shared_ptr<service>, server_utils::service_description> server_utils::parse_config( boost::property_tree::ptree config )
{
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
		config.get_child("config.services", server_utils::empty_class<boost::property_tree::ptree>()))
	{
		boost::property_tree::ptree individual_service_tree = (boost::property_tree::ptree) v.second ;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &vs,
			individual_service_tree)
		{
			std::string first_data = vs.first.data();

			if(first_data == "name")
			{
				std::string second_data = vs.second.data();
				std::cout << std::endl << "Service name: " << second_data << std::endl;
			}

			if(first_data == "library_name")
			{
				std::string second_data = vs.second.data();
				std::cout << "Library name: " << second_data << std::endl;
			}

			if(first_data == "class_name")
			{
				std::string second_data = vs.second.data();
				std::cout << "Class name: " << second_data << std::endl;
			}

			if(first_data == "root_directory")
			{
				std::string second_data = vs.second.data();
				std::cout << "Root directory path: " << second_data << std::endl;
			}

			if(first_data == "properties")
			{
				boost::property_tree::ptree service_properties_tree = (boost::property_tree::ptree) vs.second ;		
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
		}
	}
	std::cout << std::endl;
	std::map<boost::shared_ptr<service>, server_utils::service_description> m;
	return m;
}