#include <iostream>
#include <string>
#include <boost/bind.hpp>
// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>



#include "plug_in_interface.h"

class my_plugin: public plugin
{
	public:

		virtual void pass_and_modify_data(std::string** a)
		{
			std::cout << "incoming data: " << **a << std::endl;
			**a += " La la la ";
		}

		virtual boost::shared_ptr<std::string> pass_and_modify_data( boost::shared_ptr<std::string>  a)
		{
			std::cout << "incoming data: " << *a << std::endl;
			return boost::shared_ptr<std::string>(new std::string( *a + " La la la "), boost::bind(&deleter_namespace::delete_ptr<std::string>, _1));
		}

		virtual void simple_call()
		{
			std::cout << "Hello world" << std::endl;
		}

};


BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<plugin> > &factories(types.get());
	factories["my_plugin"].set<my_plugin>();
}

