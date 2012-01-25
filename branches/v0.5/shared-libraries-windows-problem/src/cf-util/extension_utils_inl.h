#include "extension_utils.h"
	
template <class BaseClass, class ConstructorType>
std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > extension_utils::get_factories (boost::extensions::shared_library &lib, std::string class_name) {
	boost::extensions::type_map lib_types;

	// The following initialization is required when using static CRT.
	std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > &lib_factories(lib_types.get());
	lib_factories[class_name];

	if (!lib.call(lib_types)) {
		std::cerr << "Types map not found!" << std::endl;
		throw std::runtime_error("Types map not found!");
	}

	if (lib_factories.empty()) {
		std::cerr << "Producers not found!" << std::endl;
		throw std::runtime_error("Producers not found!");
	}
	return lib_factories;
}

template <class BaseClass, class ConstructorType>
boost::shared_ptr<BaseClass> extension_utils::get_class (boost::extensions::shared_library &lib, std::string class_name, ConstructorType value ) {
	std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > lib_factories = get_factories<BaseClass, ConstructorType>(lib, class_name);
	boost::shared_ptr<BaseClass> lib_class(lib_factories[class_name].create(value));
	return lib_class;
}

template <class BaseClass>
std::map<std::string, boost::extensions::factory<BaseClass> > extension_utils::get_factories (boost::extensions::shared_library &lib, std::string class_name) {
	boost::extensions::type_map lib_types;

	// The following initialization is required when using static CRT.
	std::map<std::string, boost::extensions::factory<BaseClass> > &lib_factories(lib_types.get());
	lib_factories[class_name];

	if (!lib.call(lib_types)) {
		std::cerr << "Types map not found!" << std::endl;
		throw std::runtime_error("Types map not found!");
	}

	if (lib_factories.empty()) {
		std::cerr << "Producers not found!" << std::endl;
		throw std::runtime_error("Producers not found!");
	}
	return lib_factories;
}

template <class BaseClass, class ConstructorType>
boost::shared_ptr<BaseClass> extension_utils::give_me_class(std::string library_name, std::string class_name_inside_lib, ConstructorType constructor_argument)
{
	library_name = add_prefix_and_suffix(library_name);
	boost::extensions::shared_library library(library_name);
	try_open_lib(library, library_name);
	boost::shared_ptr<BaseClass> class_ptr = get_class<BaseClass>(library, class_name_inside_lib, constructor_argument);
	return class_ptr;
}

/*
template <class BaseClass>
boost::shared_ptr<BaseClass> extension_utils::give_me_class(std::string library_name, std::string class_name_inside_lib)
{
	library_name = add_prefix_and_suffix(library_name);
	boost::extensions::shared_library library(library_name);
	try_open_lib(library, library_name);
	boost::shared_ptr<BaseClass> class_ptr = get_class<BaseClass>(library, class_name_inside_lib);
	return class_ptr;
}*/

template <class BaseClass>
std::pair< boost::shared_ptr<boost::extensions::shared_library>, boost::shared_ptr<BaseClass> > extension_utils::give_me_class(std::string library_name, std::string class_name_inside_lib)
{
	library_name = add_prefix_and_suffix(library_name);
	boost::shared_ptr<boost::extensions::shared_library> library( new boost::extensions::shared_library(library_name));
	try_open_lib(*library, library_name);
	boost::shared_ptr<BaseClass> class_ptr = get_class<BaseClass>(*library, class_name_inside_lib);
	return std::pair< boost::shared_ptr<boost::extensions::shared_library>, boost::shared_ptr<BaseClass> >(library, class_ptr);
}

template <class BaseClass>
boost::shared_ptr<BaseClass> extension_utils::get_class (boost::extensions::shared_library &lib, std::string class_name ) {
	std::map<std::string, boost::extensions::factory<BaseClass> > lib_factories = get_factories<BaseClass>(lib, class_name);
	boost::shared_ptr<BaseClass> lib_class(lib_factories[class_name].create());
	return lib_class;
}
