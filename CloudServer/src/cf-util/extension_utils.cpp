#include "extension_utils.h"

std::string extension_utils::add_prefix_and_suffix(std::string &name)
{
	std::string library_name = current_prefix;
	library_name +=	name;
	library_name +=	current_extention;
	return library_name;
}

void extension_utils::try_open_lib( boost::extensions::shared_library &lib, std::string &path )
{
	if (!lib.open()) {
		std::cout << "Library failed to open: " << path << std::endl;
	}
	else
	{	
		std::cout << "Library " << path << " opened." << std::endl;
	}
}
