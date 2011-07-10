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