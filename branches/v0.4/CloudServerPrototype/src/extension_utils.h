// OJ 2011
//Usage:
//
//one way to create classes from dll - create all possible classes using factories, tested, works
//
//map<string, factory<Your_Base_Class, Constructor_Argument_T> > producer_factories = get_factories<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance);
//for (map<string, factory<Your_Base_Class, Constructor_Argument> >::iterator it
//	= producer_factories.begin();
//	it != producer_factories.end(); ++it) {
//		cout << "Creating Your_Base_Class using factory: " << it->first << endl;
//		boost::scoped_ptr<Your_Base_Class> current_instance_of_Your)Base_Class(it->second.create(Some_Constructor_Argument_Value));
//		cout << "Created instance of Your Base Class" << 
//			" Lets try it on: " << endl;
//		current_instance_of_Your_Base_Class->Some_Function_From_Your_Base_Class(Argument_Value);
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//another way to create one class from dll by name having factories, tested, works
//
//map<string, factory<Your_Base_Class, Constructor_Argument_T> > producer_factories = get_factories<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance);
//boost::scoped_ptr<Your_Base_Class> producer(producer_factories["BOOST_EXTENSION_TYPE_MAP_FUNCTION_STRING_NAME_DEFINED_IN_LIB"].create(Some_Constructor_Argument_Value));
//current_instance_of_Your_Base_Class->Some_Function_From_Your_Base_Class(Argument_Value);
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//last way is to create a class having only int name (declared in realization)
//
//its prototype interface class and that class constructor argument type and value we want to use
//boost::shared_ptr<Your_Base_Class> producer ( get_class<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance, "BOOST_EXTENSION_TYPE_MAP_FUNCTION_STRING_NAME_DEFINED_IN_LIB", Some_Constructor_Argument_Value));
//


#ifndef UTILITIES_H
#define UTILITIES_H 
//STD
#include <iostream>
#include <string>
#include <map>
//Boost
#include <boost/shared_ptr.hpp> // aka std::shared_ptr
//Boost.Extension
#include <boost/extension/factory.hpp>
#include <boost/extension/extension.hpp>
#include <boost/extension/shared_library.hpp>
#include <boost/extension/type_map.hpp>

#ifdef WIN
#include "Windows.h"
#define _USE_32_BIT_TIME_T
#elif defined LIN
#include <unistd.h>
#elif defined MAC
#include <unistd.h> // probably...
#else
#error "unknown platform";
#endif

class extension_utils
{
public:
	extension_utils();
	virtual ~extension_utils(){}
	void load_library(boost::extensions::type_map *types, std::string library_name);
	
	template <class BaseClass, class ConstructorType>
	std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > get_factories (boost::extensions::shared_library & lib) {
		boost::extensions::type_map lib_types;
		if (!lib.call(lib_types)) {
			cerr << "Types map not found!" << endl;
			cin.get();
		}

		std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > lib_factories(lib_types.get());
		if (lib_factories.empty()) {
			std::cerr << "Producers not found!" << std::endl;
			std::cin.get();
		}
		return lib_factories;
	}

	template <class BaseClass, class ConstructorType>
	boost::shared_ptr<BaseClass> get_class (boost::extensions::shared_library & lib, std::string class_name, ConstructorType value ) {
		std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > lib_factories = get_factories<BaseClass, ConstructorType>(lib);
		boost::shared_ptr<BaseClass> lib_class(lib_factories[class_name].create(value));
		return lib_class;
	}

	template <class BaseClass>
	std::map<std::string, boost::extensions::factory<BaseClass> > get_factories (boost::extensions::shared_library & lib) {
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
	boost::shared_ptr<BaseClass> get_class (boost::extensions::shared_library & lib, std::string class_name ) {
		std::map<std::string, boost::extensions::factory<BaseClass> > lib_factories = get_factories<BaseClass>(lib);
		boost::shared_ptr<BaseClass> lib_class(lib_factories[class_name].create());
		return lib_class;
	}

	void try_open_lib(boost::extensions::shared_library & lib, std::string & path)
	{
		if (!lib.open()) {
			std::cout << "Library failed to open: " << path << std::endl;
		}
		else
		{
			std::cout << "Library " << path << " opened." << std::endl;
		}
	}
	std::string add_prefix_and_suffix(std::string name);
private:
	std::string current_prefix;
	std::string current_extention;
};

#endif // UTILITIES_H