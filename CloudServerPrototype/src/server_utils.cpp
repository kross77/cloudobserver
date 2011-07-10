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

std::map<boost::shared_ptr<service>, server_utils::rules> server_utils::parse_config( boost::property_tree::ptree config )
{
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
		config.get_child("config.servecies"))
	{
		std::cout << "First data: " << v.first.data() << std::endl << "Second data: " << v.second.data() << std::endl;
	}
 std::map<boost::shared_ptr<service>, server_utils::rules> m;
 return m;
}