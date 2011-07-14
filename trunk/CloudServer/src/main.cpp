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
#include <boost/program_options.hpp>

boost::program_options::options_description desc("Allowed options");
server *s;
server_utils su;
boost::property_tree::ptree server_config;
bool server_started = false, server_config_was_set = false;
std::string default_configuration_file_name = "config.xml";

void print_info()
{
	std::cout << "Expendable Server 1.0" << std::endl;
	std::cout << "Copyright (c) 2011 Cloud Forever. All rights reserved." << std::endl;
	std::cout << std::endl;
	std::cout << "Type 'help' to see help messages." << std::endl;
}

void print_help()
{
	std::cout	<< "Type 'help'                  to see interactive shell help messages again." << std::endl
		<< "Type 'program_options_help'  to see program start up arguments." << std::endl
		<< "Type 'config'                to enter path for configuration file." << std::endl
		<< "Type 'save'                  to save current configuration into file." << std::endl
		<< "Type 'start'                 to start this server." << std::endl
		<< "Type 'exit'                  to stop this server and leave this the application." << std::endl;
}

bool config(std::string config_file_path)
{
	std::cout << "Config file path: " << config_file_path << std::endl;
	std::ifstream script;
	try
	{
		script.open(config_file_path.c_str());
		if(!script.is_open())
		{
			if(config_file_path == default_configuration_file_name)
			{
				std::cout << "Error: could not open default configuration file: '" << config_file_path << "'." << std::endl;
				return false;
			}
			std::cout << "Error: could not open configuration file: '" << config_file_path << "'." << std::endl;
			return false;
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Error: could not open configuration file: '" << config_file_path << "'." << std::endl;
		return false;
	}

	try
	{
		std::string ext = config_file_path.substr(config_file_path.find_last_of(".") + 1);
		if((ext == "x") || (ext == "xml") || (ext  == "ccml"))
		{
			boost::property_tree::read_xml(script, server_config);
		}
		else if((ext == "j") || (ext == "js") || (ext == "json"))
		{
			boost::property_tree::read_json(script, server_config);
		}
		else
		{
			std::cout << "Error: configuration file must have extension `.x`, `.xml`, `.ccml` for xml formated input files or `.j`, `.js`, `.json` for JSON formated files  " << std::endl;
			return false;
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Error: configuration file should be valid JSON or XML file." << std::endl;
		return false;
	}

	//TODO: link to server class
	try
	{
		if(!server_started)
		{
		s = new server(server_config);
		server_started = true;
		}
		else
		{
			s->util->add_to_services_list(server_config);
			std::cout << "Configuration updated." << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Error: Could not start up the server." << std::endl;
		return false;
	}

	std::cout << "Configuration from '" << config_file_path << "' is currently active." << std::endl;
	return true;
}

bool save(std::string save_file_path)
{
	try
	{
		std::string ext = save_file_path.substr(save_file_path.find_last_of(".") + 1);
		if((ext == "x") || (ext == "xml") || (ext  == "ccml"))
		{
			boost::property_tree::xml_writer_settings<char> w(' ', 4);
			write_xml(save_file_path, s->get_configuration(), std::locale(), w);
		}
		else if((ext == "j") || (ext == "js") || (ext == "json"))
		{
			write_json(save_file_path, s->get_configuration());
		}
		else
		{
			std::cout << "Error: configuration file must have extension `.x`, `.xml`, `.ccml` for xml formated input files or `.j`, `.js`, `.json` for JSON formated files  " << std::endl;
			return false;
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Error: configuration file should be valid JSON or XML file." << std::endl;
		return false;
	}
	std::cout << "Current configuration saved to '" << save_file_path << "' file." << std::endl;
	return true;
}

void start(boost::property_tree::ptree server_config)
{
	if(!server_started)
	{
		try
		{
			if(!config(default_configuration_file_name))
			{
				std::cout << "Starting server with empty configuration." <<  std::endl;
				boost::property_tree::ptree server_config;
				s = new server(server_config);
			}
		}
		catch(std::exception &e)
		{
			std::cout << "Server initialization failed miserably." << std::endl;
			return;
		}
		server_started = true;
		std::cout << "Server started." << std::endl;
	}
	else
	{
		std::cout << "Server is already running. You can configure it while it runs." << std::endl;
		return ;
	}
	return ;
}

void parse_program_options(int argc, char* argv[])
{
	desc.add_options()
		("help", "to produce help message")
		("config", boost::program_options::value<std::string>()->composing()->notifier(&config)->default_value(default_configuration_file_name), "to enter path for configuration file for us to read");
	("start", "to start this server")
		;
	boost::program_options::variables_map vm;

	try
	{
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
		boost::program_options::notify(vm);    
	}
	catch(std::exception &e)
	{
		std::cout << "You have used unknown argument while starting program, please see our help: " << std::endl;
		std::cout << desc << std::endl;
	}
	if (vm.count("help")) {
		std::cout << desc << std::endl;
	}

	if (vm.count("start")) {
		start(server_config);
	} 
}

int main(int argc, char* argv[])
{ 
	print_info();

	parse_program_options(argc, argv);

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
		if (input == "program_options_help")
		{
			std::cout << std::endl;
			std::cout << desc << std::endl;
			continue;
		}

		if (input == "start") 
		{
			start(server_config);
			continue;
		}

		if (input == "config")
		{
			std::string file_path;
			std::cout << "Please enter config file path (to XML or JSON file): " << std::endl;
			do{
				std::cout << "Path: ";
				std::cin >> file_path;

				if (file_path == "exit")
					continue;

				if(config(file_path))
					break; 

			} while (file_path != "exit");
			continue;
		}

		if (input == "save")
		{
			std::string file_path;
			std::cout << "Please enter file path and name (to save XML or JSON file): " << std::endl;
			do{
				std::cout << "Path: ";
				std::cin >> file_path;

				if (file_path == "exit")
					continue;

				if(save(file_path))
					break; 

			} while (file_path != "exit");
			continue;
		}

		if (input == "exit")
			continue;

		std::string ext = input.substr(input.find_last_of(".") + 1);
		if((ext == "x") || (ext == "xml") || (ext  == "ccml") || (ext == "j") || (ext == "js") || (ext == "json"))
		{
			config(input);
			continue;
		}

		std::cout << "Unknown command '" << input << "'." << std::endl;
	} while (input != "exit");

	return EXIT_SUCCESS;
}
