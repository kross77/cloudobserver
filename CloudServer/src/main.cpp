#include <stdio.h>
#include <iostream>
#include <fstream>

//Boost
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/program_options.hpp>

//cf service interface
#include <service.hpp>

//cf-server
#include <server.h>

boost::program_options::options_description desc("Allowed options");
server *s;
boost::property_tree::ptree server_config;
bool server_started = false, server_config_was_set = false;
std::string default_configuration_file_name = "config.xml";

void cleanup()
{
	delete s;
}

void print_info()
{
	std::cout << "Cloud Server v0.5" << std::endl;
	std::cout << "Copyright (c) 2011 Cloud Forever. All rights reserved." << std::endl;
	std::cout << std::endl;
	std::cout << "Type 'help' to see help messages." << std::endl;
}

void print_help()
{
	std::cout	<< "Type 'help'                  to see interactive shell help messages again." << std::endl
		<< "Type 'program_options_help'  to see program start up arguments." << std::endl
		<< "Type 'config'                to enter path for configuration file." << std::endl
		<< "Type 'service'               to enter service configuration menu." << std::endl
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
			atexit(cleanup);
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

void print_services()
{
	BOOST_FOREACH(std::string const si, s->util->get_services_names())
	{
		std::cout << si << std::endl;
	}
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
				atexit(cleanup);
			}
		}
		catch(std::exception &e)
		{
			std::cout << "Server initialization failed miserably." << std::endl;
			return;
		}
		server_started = true;
		std::cout << "Server started." << std::endl;
		std::cout << "Please enter service name or `ls` to print all currently available services: " << std::endl;
		print_services();
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

void service_commandor(std::string name)
{
	try
	{
		boost::shared_ptr<base_service> one_service = s->util->get_service_by_name(name);
		//std::cout << "service options are: `get state`, `restart`, `stop`, `start`" << std::endl;
		std::cout << "You can change service configuration. to get into service configuration menu enter `config`" << std::endl;
		std::string var;
		do{
			std::cout << "@" << name <<": ";
			std::getline(std::cin, var);

			if (var == "stop")
			{
				//s->util->stop_service_by_name() //TODO: implement set of turned off services.descriptions
				continue;
			}

			if (var == "start")
			{
				//s->util->start_service_by_name() //TODO: search thru turned off services.descriptions than thru turned on
				continue;
			}


			if (var == "restart")
			{
				//s->util->stop_service_by_name() //TODO: implement set of turned off services.descriptions
				//s->util->start_service_by_name() //TODO: search thru turned off services.descriptions than thru turned on
				continue;
			}

			if (var == "get state")
			{
				//s->util->get_service_state_by_name() //TODO: search thru turned off services.descriptions than thru turned on
				continue;
			}

			if (var == "config")
			{

				std::cout << "Please enter your configuration, enter `launch` to apply it or `exit` to return to main service menu shall" << std::endl;
				std::string com;
				std::stringstream conf;
				do{
					std::getline(std::cin, com);
					if (com == "exit")
						continue;

					if (com == "launch")
					{
						bool invalid_config = true;
						boost::property_tree::ptree pt;
						try
						{
							boost::property_tree::read_json(conf, pt); // Works,
							invalid_config = false;
						}
						catch (std::exception& e)
						{
							invalid_config = true;
						}
						if (invalid_config)
						{
							try
							{
								boost::property_tree::read_xml(conf, pt); // Does not work.
								invalid_config = false;
							}
							catch (std::exception& e)
							{
								invalid_config = true;
							}
						}

						if (invalid_config)
						{
							std::cout << "invalid configuration input, please input correct JSON config." << std::endl;
							continue;
						} 
						else
						{
							try
							{
								boost::shared_ptr<boost::property_tree::ptree> properties_tree(new boost::property_tree::ptree(pt));
								one_service->apply_config(properties_tree);
								std::cout << "Configuration applied." << std::endl;
							}
							catch(std::exception &e)
							{
								std::cout << "Configuration failed" << std::endl;
								continue;
							}
						}

						continue;
					}

					conf << com;
				} while (com != "exit");
				continue;
			}

			if (var == "exit")
				continue;

		} while (var != "exit");
		return;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << name << " service not found." << std::endl << "Please review list of currently existing services:" << std::endl;
		print_services();
		std::cout << "And try again." << std::endl;
		return;
	}



}

int main(int argc, char* argv[])
{ 
	print_info();

	parse_program_options(argc, argv);

	std::string input;
	do
	{
		if (std::cin.eof())
			while (true)
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		
		std::cout << "$ ";
		std::getline(std::cin, input);

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
				std::cout << "< Path: ";
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
				std::cout << "> Path: ";
				std::cin >> file_path;

				if (file_path == "exit")
					continue;

			} while (file_path != "exit");
			continue;
		}


			if (server_started)
			{
				if ((input == "ls") || (input == "list services"))
				{
					print_services();
					continue;
				}
				else
				{
					service_commandor(input);
					continue;
				}
			} 
			else
				continue;
		

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
