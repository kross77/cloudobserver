#include <stdio.h>
#include <iostream>
#include <fstream>
#include "server.h"
//Boost
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>



void print_help()
{
	std::cout << "Expendable Server 1.0" << std::endl;
	std::cout << "Copyright (c) 2011 Cloud Forever. All rights reserved." << std::endl;
	std::cout << std::endl;

	std::cout << "Type 'config' to enter path for configuration file for us to read." << std::endl;
	std::cout << "Type 'start' to start this server." << std::endl; 
	std::cout << "Type 'help' to see these help messages again." << std::endl;
	std::cout << "Type 'exit' to stop this server and leave this the application." << std::endl;
	std::cout << std::endl;
	//TODO: implement start stop pause.
	//	std::cout << "Type 'start' to start this server." << std::endl; // After server stop, or pause.
	//	std::cout << "Type 'stop' to stop this server." << std::endl;  // What means pause server? Socket closed, services map saved, all services freed from duty.
	//	std::cout << "Type 'pause' to pause this server." << std::endl; // What means pause server? Socket shall be open, no requests processed
}
int main(int argc, char* argv[])
{ 
	print_help();

	server *s;
	bool server_started = false;
	int port_number = 12345;

	boost::property_tree::ptree server_config;

	std::string input;
	do
	{
		std::cout << "$ ";
		std::cin >> input;

		if (input == "help")
		{
			std::cout << std::endl;
			print_help();
			continue;
		}

		if (input == "start")
		{
			if(!server_started)
			{
				try
				{
					s = new server(port_number);
				}
				catch(std::exception &e)
				{
					std::cout << "Server initialization failed miserably" << std::endl;
					continue;
				}
				server_started = true;
				std::cout << "Server started with default options" << std::endl;
			}
			else
			{
				std::cout << "Server is already running. You can configure it while it runs." << std::endl;
			}
			continue;
		}

		if (input == "config")
		{
			std::string file_type;
			std::cout << "Please enter config file type - 'xml' or 'json': " << std::endl;
			do{
				std::cout << "type: ";
				std::cin >> file_type;
				if (input == "exit")
					continue;

				if (file_type == "xml")
				{
					std::cout << "Please input config file path." << std::endl;
					std::string file_path;
					do 
					{
						std::cout << "Path: ";
						std::cin >> file_path;
						if (input == "exit")
							continue;

						try
						{
							std::ifstream script;
							script.open(file_path.c_str());
							boost::property_tree::read_xml(script, server_config);
							std::cout << "Configuration from '" << file_path << "' is currently active." << std::endl;
							break;
						}
						catch(std::exception &e)
						{
							std::cout << "Bad path or file: '" << file_path << "'." << std::endl;
						}
					} while (file_path != "exit");
					break;
				}
				if (file_type == "json")
				{
					std::cout << "Please input config file path." << std::endl;
					std::string file_path;
					do 
					{
						std::cout << "path: ";
						std::cin >> file_path;
						if (input == "exit")
							continue;

						try
						{
							std::ifstream script;
							script.open(file_path.c_str());
							boost::property_tree::read_json(script, server_config);
							std::cout << "Configuration from '" << file_path << "' is currently active." << std::endl;
							break;
						}
						catch(std::exception &e)
						{
							std::cout << "Bad path or file: '" << file_path << "'." << std::endl;
							continue;
						}
					} while (file_path != "exit");
					break;
				}
				std::cout << "Unknown type '" << file_type << "'." << std::endl;
			} while (file_type != "exit");
			continue;
		}
		if (input == "exit")
			continue;

		std::cout << "Unknown command '" << input << "'." << std::endl;
	} while (input != "exit");
	return EXIT_SUCCESS;
}