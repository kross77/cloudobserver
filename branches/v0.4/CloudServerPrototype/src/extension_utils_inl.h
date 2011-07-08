#include "extension_utils.h"
	
template <class BaseClass, class ConstructorType>
std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > extension_utils::get_factories (boost::extensions::shared_library &lib) {
	boost::extensions::type_map lib_types;
	if (!lib.call(lib_types)) {
		std::cerr << "Types map not found!" << std::endl;
		std::cin.get();
	}

	std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > lib_factories(lib_types.get());
	if (lib_factories.empty()) {
		std::cerr << "Producers not found!" << std::endl;
		std::cin.get();
	}
	return lib_factories;
}

template <class BaseClass, class ConstructorType>
boost::shared_ptr<BaseClass> extension_utils::get_class (boost::extensions::shared_library &lib, std::string class_name, ConstructorType value ) {
	std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > lib_factories = get_factories<BaseClass, ConstructorType>(lib);
	boost::shared_ptr<BaseClass> lib_class(lib_factories[class_name].create(value));
	return lib_class;
}

template <class BaseClass>
std::map<std::string, boost::extensions::factory<BaseClass> > extension_utils::get_factories (boost::extensions::shared_library &lib) {
	boost::extensions::type_map lib_types;
	if (!lib.call(lib_types)) {
		std::cerr << "Types map not found!" << std::endl;
		std::cin.get();
	}

	std::map<std::string, boost::extensions::factory<BaseClass> > lib_factories(lib_types.get());
	if (lib_factories.empty()) {
		std::cerr << "Producers not found!" << std::endl;
		std::cin.get();
	}
	return lib_factories;
}

template <class BaseClass>
boost::shared_ptr<BaseClass> extension_utils::get_class (boost::extensions::shared_library &lib, std::string class_name ) {
	std::map<std::string, boost::extensions::factory<BaseClass> > lib_factories = get_factories<BaseClass>(lib);
	boost::shared_ptr<BaseClass> lib_class(lib_factories[class_name].create());
	return lib_class;
}
