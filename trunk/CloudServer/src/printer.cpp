#include "printer.h"

void printer::print_map_contents(std::map <std::string, std::string> data)
{
	std::map<std::string, std::string>::const_iterator end = data.end();
	if(data.end() != data.begin())
	{
		std::cout << "Received request contained:\n";
		for (std::map<std::string, std::string>::const_iterator it = data.begin(); it != end; ++it)
		{
			std::cout << it->first << " : " << it->second << '\n';
		}
	}
}

void printer::print_map_contents(std::map <std::string, std::string> data, std::string dataName)
{
	std::map<std::string, std::string>::const_iterator end = data.end();
	if(data.end() != data.begin())
	{
		std::cout << "Received request contained next "<< dataName << ":\n";
		for (std::map<std::string, std::string>::const_iterator it = data.begin(); it != end; ++it)
		{
			std::cout << it->first << " : " << it->second << '\n';
		}
	}
}