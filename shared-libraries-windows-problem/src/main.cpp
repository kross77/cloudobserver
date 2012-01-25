#ifndef APP
#define APP

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
//Extension includes
#include <extension_utils.h>

#include "plug_in_interface.h"

int main()
{
	{
		std::cout << "creating plugin instance:" << std::endl;
		std::pair< boost::shared_ptr<boost::extensions::shared_library>, boost::shared_ptr<plugin> > map = extension_utils::give_me_class<plugin>("DemoPlugin", "my_plugin"); 
		boost::shared_ptr<plugin> my_plugin = map.second;
		std::cout << "plugin instance created from dynamically loaded shared library." << std::endl;
		std::cout << "calling plugin instance:" << std::endl;
		my_plugin->simple_call();
		std::cin.get();
		std::cout << "instance called." << std::endl;
		
		{
			std::string **a = new std::string*;
			*a = new std::string("A b c d e f g");
			my_plugin->pass_and_modify_data(a);
			std::cout << "modified data: " <<  **a << std::endl;
			std::cin.get();
			my_plugin->delete_ptr(*a);
			delete a;
			std::cout << "removed data" << std::endl;
		}
		std::cin.get();

		//currently we can not close lib successfully
		//map.first->close();
	}
	std::cin.get();
}


#endif //APP