#include <iostream>
#include <string>

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
			std::cout << "incoming data:" << **a << std::endl;
			**a += " La la la ";
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