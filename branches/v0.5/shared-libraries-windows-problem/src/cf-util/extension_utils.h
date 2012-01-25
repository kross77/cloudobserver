// OJ 2011

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

/*!
 *  \addtogroup Utilities
 *  @{
 */

/*!
 * \brief dinamically create classes from shared libraries
 *
 * one way to use it is to create all possible classes using factories, tested, works
 * \code
 * map<string, factory<Your_Base_Class, Constructor_Argument_T> > producer_factories = get_factories<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance);
 * for (map<string, factory<Your_Base_Class, Constructor_Argument> >::iterator it
 *	it != producer_factories.end(); ++it) {
 *		cout << "Creating Your_Base_Class using factory: " << it->first << endl;
 *		boost::scoped_ptr<Your_Base_Class> current_instance_of_Your)Base_Class(it->second.create(Some_Constructor_Argument_Value));
 *		cout << "Created instance of Your Base Class" << 
 *			" Lets try it on: " << endl;
 *		current_instance_of_Your_Base_Class->Some_Function_From_Your_Base_Class(Argument_Value);
 *}
 * \endcode
 * \n
 * There is a way to create one class from shared library by name using factories, tested, works
 * \code
 * map<string, factory<Your_Base_Class, Constructor_Argument_T> > producer_factories = get_factories<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance);
 * boost::scoped_ptr<Your_Base_Class> producer(producer_factories["BOOST_EXTENSION_TYPE_MAP_FUNCTION_STRING_NAME_DEFINED_IN_LIB"].create(Some_Constructor_Argument_Value));
 * current_instance_of_Your_Base_Class->Some_Function_From_Your_Base_Class(Argument_Value);
 * \endcode
 * \n
 * last way is to create a class having only its name (declared in realization) 
 * we need its prototype interface class and that class constructor argument type and value we want to use
 * \code
 * boost::shared_ptr<Your_Base_Class> producer ( get_class<Your_Base_Class, Constructor_Argument_T>(Your_Shared_Library_Instance, "BOOST_EXTENSION_TYPE_MAP_FUNCTION_STRING_NAME_DEFINED_IN_LIB", Some_Constructor_Argument_Value));
 * \endcode
 * \n
 *
 */
namespace extension_utils
{
	
	template <class BaseClass, class ConstructorType>
	std::map<std::string, boost::extensions::factory<BaseClass, ConstructorType> > get_factories (boost::extensions::shared_library & lib, std::string class_name);

	template <class BaseClass>
	std::map<std::string, boost::extensions::factory<BaseClass> > get_factories (boost::extensions::shared_library & lib, std::string class_name);
	
	/*!
	 * \brief Way to get pointer to class with constructor from created by you shared_library object.
	 *
	 * \n FullName:  extension_utils<BaseClass, ConstructorType>::get_class
	 * \n Access:    public  
	 *
	 * \param lib boost::extensions::shared_library &
	 * \param class_name std::string
	 * \param value ConstructorType
	 *
	 */
	template <class BaseClass, class ConstructorType>
	boost::shared_ptr<BaseClass> get_class (boost::extensions::shared_library & lib, std::string class_name, ConstructorType value );

	/*!
	 * \brief Way to get pointer to class with empty constructor from created by you shared_library object.
	 *
	 * \n FullName:  extension_utils<BaseClass>::get_class
	 * \n Access:    public  
	 *
	 * \param lib boost::extensions::shared_library &
	 * \param class_name std::string
	 * 
	 */
	template <class BaseClass>
	boost::shared_ptr<BaseClass> get_class (boost::extensions::shared_library & lib, std::string class_name );

	/*!
	 * \brief Fast way to get pointer to class out from library.
	 *
	 * We open your lib file, check it for requested class, create class instance and return it to you.
	 *
	 * \n FullName:  extension_utils<BaseClass, ConstructorType>::give_me_class
	 * \n Access:    public  
	 *
	 * \param library_name std::string
	 * \param class_name_inside_lib std::string
	 * \param constructor_argument ConstructorType
	 * \note Here we assume library is in path some library path known to app.
	 *
	 */
	template <class BaseClass, class ConstructorType>
	boost::shared_ptr<BaseClass> give_me_class(std::string library_name, std::string class_name_inside_lib, ConstructorType constructor_argument);

	/*!
	 * \brief Fast way to get pointer to class with empty constructor out from library.
	 * 
	 * We open your lib file, check it for requested class, create class instance and return it to you.
	 *
	 * \n FullName:  extension_utils<BaseClass>::give_me_class
	 * \n Access:    public  
	 *
	 * \param library_name std::string
	 * \param class_name_inside_lib std::string
	 * \note Here we assume library is in path some library path known to app.
	 *
	 */
	template <class BaseClass> std::pair< boost::shared_ptr<boost::extensions::shared_library>, boost::shared_ptr<BaseClass> > give_me_class(std::string library_name, std::string class_name_inside_lib);
	void try_open_lib(boost::extensions::shared_library & lib, std::string & path);
	void try_close_lib( std::string library_name );
	std::string add_prefix_and_suffix(std::string &name);

	// Shared library suffixes
	#ifdef WIN
		const std::string current_extention = ".dll";
	#elif defined LIN
		const std::string current_extention = ".so";
	#elif defined MAC
		const std::string current_extention = ".dylib"; // as wall .bundle can be used.
	#else
	#error "unknown platform";
	#endif

	// Shared library prefixes
	#ifdef WIN
		const std::string current_prefix = "";
	#elif defined LIN
		const std::string current_prefix = "lib";
	#elif defined MAC
		const std::string current_prefix = "lib"; // as wall .bundle can be used.
	#else
	#error "unknown platform";
	#endif
};
/*! @} */
//Include inline functions
#include "extension_utils_inl.h"

#endif // BOOST_EXTENSION_UTILITIES_H