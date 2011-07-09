#include "extension_utils.h"
extension_utils::extension_utils()
{
	// Shared library suffixes
	#ifdef WIN
		current_extention = ".dll";
	#elif defined LIN
		current_extention = ".so";
	#elif defined MAC
		current_extention = ".dylib"; // as wall .bundle can be used.
	#else
	#error "unknown platform";
	#endif

	// Shared library prefixes
	#ifdef WIN
		current_prefix = "";
	#elif defined LIN
		current_prefix = "lib";
	#elif defined MAC
		current_prefix = "lib"; // as wall .bundle can be used.
	#else
	#error "unknown platform";
	#endif
}


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
