#include "extension_utils.h"
extension_utils::extension_utils()
{
	// Shared library suffixes
	#ifdef WIN
		std::string current_extention = ".dll";
	#elif defined LIN
		std::string current_extention = ".so";
	#elif defined MAC
		std::string current_extention = ".dylib"; // as wall .bundle can be used.
	#else
	#error "unknown platform";
	#endif

		// Shared library prefixes
	#ifdef WIN
		std::string current_prefix = "";
	#elif defined LIN
		std::string current_prefix = "lib";
	#elif defined MAC
		std::string current_prefix = "lib"; // as wall .bundle can be used.
	#else
	#error "unknown platform";
	#endif
}


std::string extension_utils::add_prefix_and_suffix(std::string name)
{
	std::string library_name = current_prefix;
	library_name +=	name;
	library_name +=	current_extention;
	return library_name;
}


