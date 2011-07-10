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

#ifndef SERVER_UTILITIES_H
#define SERVER_UTILITIES_H 

//STD
#include <iostream>
#include <string>
#include <map>

//Boost
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp> // aka std::shared_ptr
#include <boost/unordered_map.hpp> // aka std::unordered_map
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

//General Service header Class\Interface
#include "../service-interface/service.hpp"

//Extension includes
#include "extension_utils.h"

//Maps printer
#include "printer.h"




class server_utils
{
public:
	server_utils();
	virtual ~server_utils(){}

	//Each service provides us with rules
	struct rules
	{
		boost::unordered_multimap<std::string, std::string> set_of_header_rules;
		boost::unordered_multimap<std::string, std::string> set_of_arguments_rules;
	};
	
	//Each request provides us with data
	struct data
	{
		std::map<std::string, std::string> headers;
		std::map<std::string, std::string> arguments;
	};
	
	boost::shared_ptr<service> create_service(std::string library_name, std::string class_name_inside_lib); // Creates class that is inherited from service class\interface. 

	std::map<boost::shared_ptr<service>, rules> parse_config(boost::property_tree::ptree config); // TODO: write this
	void save_config( std::map<boost::shared_ptr<service>, rules> services_map); // TODO: write this

	data parse_request(http_request request); // TODO: write this

	int relevance(const rules & r, const data & d); // TODO: write this
	boost::shared_ptr<service> find_service(const data & d); //TODO:  write this

	// For maps contents printing
	printer *print;

private:

	//We keap all services and thare rules inside of a map
	std::map<boost::shared_ptr<service>, rules> service_map;
	
	// Server path (by default app path) //TODO: make it configurable via config ptree
	boost::filesystem::path server_root_path;

	// For services creation from shared libraries
	extension_utils *util; 

};


#endif // SERVER_UTILITIES_H