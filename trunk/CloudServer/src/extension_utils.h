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

#ifndef BOOST_EXTENSION_UTILITIES_H
#define BOOST_EXTENSION_UTILITIES_H 
//STD
#include <iostream>
#include <stdexcept>
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
	
	template <class BaseClass, class ConstructorType>
	std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > get_factories (boost::extensions::shared_library & lib);

	template <class BaseClass>
	std::map<std::string, boost::extensions::factory<BaseClass> > get_factories (boost::extensions::shared_library & lib);

	//Way to get pointer to class with constructor from created by you shared_library object.
	template <class BaseClass, class ConstructorType>
	boost::shared_ptr<BaseClass> get_class (boost::extensions::shared_library & lib, std::string class_name, ConstructorType value );

	//Way to get pointer to class with empty constructor from created by you shared_library object.
	template <class BaseClass>
	boost::shared_ptr<BaseClass> get_class (boost::extensions::shared_library & lib, std::string class_name );

	//Here we assume library is in path some library path known to app.
	//Fast way to get pointer to class out from library.
	//We open your lib file, check it for requested class, create class instance and return it to you.
	template <class BaseClass, class ConstructorType>
	boost::shared_ptr<BaseClass> give_me_class(std::string library_name, std::string class_name_inside_lib, ConstructorType constructor_argument);

	//Here we assume library is in path some library path known to app.
	//Fast way to get pointer to class with empty constructor out from library.
	//We open your lib file, check it for requested class, create class instance and return it to you.
	template <class BaseClass>
	boost::shared_ptr<BaseClass> give_me_class(std::string library_name, std::string class_name_inside_lib);

	void try_open_lib(boost::extensions::shared_library & lib, std::string & path);

	std::string add_prefix_and_suffix(std::string &name);

private:
	std::string current_prefix;
	std::string current_extention;
};

//Include inline functions
#include "extension_utils_inl.h"

#endif // BOOST_EXTENSION_UTILITIES_H