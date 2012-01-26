#ifndef APP
#define APP

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
//Extension includes
#include <extension_utils.h>

#include "plug_in_interface.h"

void fuck2(int *&b)
{
	(*b)++;
}

void fuck(int **b)
{
	(**b)++;
}

int main()
{
	
	std::cout << "creating plugin instance:" << std::endl;
	boost::shared_ptr<plugin> my_plugin = extension_utils::give_me_class<plugin>("DemoPlugin", "my_plugin");
	std::cout << "plugin instance created from dynamically loaded shared library." << std::endl;
		
	std::cout << "Demo call to plugin instance:" << std::endl;
	{
		my_plugin->simple_call();
		std::cout << "instance called." << std::endl;
	}
		
	std::cout << std::endl << "Old School memory management:" << std::endl;
	std::cin.get();
	{
		std::string **a = new std::string*;
		*a = new std::string("A b c d e f g");
		my_plugin->pass_and_modify_data(a);
		std::cout << "modified data: " <<  **a << std::endl;
		my_plugin->delete_ptr(*a);
		delete a;
		std::cout << "removed data" << std::endl;
	}

	std::cout << std::endl << "Modern memory management:" << std::endl;
	std::cin.get();
	{
		boost::shared_ptr<std::string> a(new std::string("A b c d e f g"));
		boost::shared_ptr<std::string> b = my_plugin->pass_and_modify_data(a);
		std::cout << "modified data: " << *b << std::endl;
	}
	std::cout << "removed data" << std::endl;
	std::cin.get();

	std::cout << "And now we will crush because do not know how to close the library:" << std::endl;
	std::cin.get();

}


#endif //APP