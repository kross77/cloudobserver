#include "server_utils.h"

server_utils::server_utils()
{
	util = new extension_utils();
	print = new printer();
	this->description.server_root_path = boost::filesystem::current_path();
}

boost::shared_ptr<service> server_utils::create_service(std::string library_name, std::string class_name_inside_lib, boost::property_tree::ptree config)
{
	return util->give_me_class<service, boost::property_tree::ptree>(library_name, class_name_inside_lib, config);
}

std::map<boost::shared_ptr<service>, server_utils::service_description> server_utils::parse_config_services( boost::property_tree::ptree config )
{
	std::map<boost::shared_ptr<service>, server_utils::service_description> services_map;

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
		config.get_child("config.services", server_utils::empty_class<boost::property_tree::ptree>()))
	{
		server_utils::service_description one_description;
		std::string service_library_name;
		std::string service_class_name;
		boost::property_tree::ptree individual_service_tree = (boost::property_tree::ptree) v.second ;

		std::string service_name = individual_service_tree.get<std::string>("name", "unnamed service");
		one_description.name = service_name;
		std::cout << std::endl << "Service name: " << service_name << std::endl;

		try{
			service_library_name = individual_service_tree.get<std::string>("library_name"); // Will throw error if not defined
			one_description.library_name = service_library_name;
			std::cout << "Library name: " << service_library_name << std::endl;

			service_class_name = individual_service_tree.get<std::string>("class_name"); // Will throw error if not defined
			one_description.class_name = service_class_name;
			std::cout << "Class name: " << service_class_name << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << std::endl << "Parsing library or class name error in service: " << service_name << std::endl;
			continue;
		}

		boost::property_tree::ptree service_properties_tree = individual_service_tree.get_child("properties", server_utils::empty_class<boost::property_tree::ptree>());

		std::string root_service_web_path = service_properties_tree.get<std::string>("root_service_web_path", "");
		if(!root_service_web_path.empty()){
			one_description.root_service_web_path = root_service_web_path;
			std::cout << "Service web root directory path: " << root_service_web_path << std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &va,
			service_properties_tree.get_child("arguments", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.set_of_arguments_rules.insert(std::pair<std::string, std::string>( va.first.data(), va.second.data() ) );
			std::cout << "Required argument: " << va.first.data() << " : " << va.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vh,
			service_properties_tree.get_child("headers", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.set_of_header_rules.insert(std::pair<std::string, std::string>(vh.first.data(), vh.second.data()));
			std::cout << "Required header: " << vh.first.data() << " : " << vh.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child("url_extensions", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.url_extensions.insert(vp.second.data());
			std::cout << "Supported url extension: " << vp.second.data() <<  std::endl;
		}

		one_description.service_custome_properties_tree = service_properties_tree.get_child("settings", server_utils::empty_class<boost::property_tree::ptree>());


		try{
			boost::shared_ptr<service> one_service = util->give_me_class<service, boost::property_tree::ptree>(service_library_name, service_class_name, one_description.service_custome_properties_tree);
			services_map.insert(std::pair<boost::shared_ptr<service>, server_utils::service_description>(one_service, one_description));
		}
		catch(std::exception &e)
		{
			std::cout << "Error while creating service: " << service_name << std::endl;
		}
	}
	return services_map;
}

server_utils::server_description server_utils::parse_config( boost::property_tree::ptree config )
{
	server_utils::server_description server_descr;
	std::cout << std::endl << "Server description: " << std::endl;

	server_descr.server_root_path = config.get("config.server_root_path", boost::filesystem::current_path());
	std::cout << "Server root path: " << server_descr.server_root_path << std::endl;

	server_descr.port = config.get("config.port", 12345);
	std::cout << "Server port: " << server_descr.port << std::endl;

	std::cout << std::endl << "Server services: ";
	server_descr.service_map = server_utils::parse_config_services( config );
	std::cout << std::endl;

	return server_descr;
}

boost::property_tree::ptree server_utils::save_config( server_utils::server_description server_configuration_description )
{
	boost::property_tree::ptree root, arr;
	root.put<int>("config.port", server_configuration_description.port);
	root.put<std::string>("config.server_root_path", server_configuration_description.server_root_path.string());
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	BOOST_FOREACH( map_t::value_type &i, server_configuration_description.service_map)
	{
		server_utils::service_description sm = i.second;
		boost::property_tree::ptree serv;

		serv.put<std::string>("name", sm.name);
		serv.put<std::string>("class_name", sm.class_name);
		serv.put<std::string>("library_name", sm.library_name);
		serv.put<std::string>("root_file_system_directory", sm.root_file_system_directory);
		serv.put<std::string>("root_service_web_path", sm.root_service_web_path);

		boost::property_tree::ptree serv_prop, head, arg;
		typedef boost::unordered_multimap<std::string, std::string> mulmap_t;
		bool headers_exist = false, args_exist = false;
		BOOST_FOREACH(  mulmap_t::value_type &iih, sm.set_of_arguments_rules)
		{
			args_exist = true;
			arg.put<std::string>(iih.first.data(), iih.second.data());
		}
		BOOST_FOREACH(  mulmap_t::value_type &iia, sm.set_of_header_rules)
		{
			headers_exist = true;
			head.put<std::string>(iia.first.data(), iia.second.data());
		}
		if (args_exist)
		{
			serv_prop.push_back( std::make_pair("arguments", arg));
		}
		if (headers_exist)
		{
			serv_prop.push_back( std::make_pair("headers", head));
		}
		if((headers_exist) || (args_exist))
		{
			serv.push_back(std::make_pair("properties", serv_prop));
		}
		serv.push_back(std::make_pair("properties", sm.service_custome_properties_tree));
		arr.push_back(std::make_pair("service", serv));
	}
	root.put_child("config.services", arr);
	return root;
}

boost::shared_ptr<service> server_utils::get_service_by_name(std::string name)
{
	std::multiset<std::string> service_names;
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	BOOST_FOREACH(map_t::value_type &it, description.service_map)
	{
		server_utils::service_description descr = it.second;
		if(descr.name == name)
		{
			return it.first;
		}
	}
	throw std::exception("Service with such name was not found map not found!");
	boost::shared_ptr<service> null;
	return null;
}

std::multiset<std::string> server_utils::get_services_class_names()
{
	std::multiset<std::string> class_names;
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	BOOST_FOREACH(map_t::value_type &it, description.service_map)
	{
		server_utils::service_description descr = it.second;
		class_names.insert(descr.class_name);
	}
	return class_names;
}

std::multiset<std::string> server_utils::get_services_libraries_names()
{
	std::multiset<std::string> libraries_names;
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	BOOST_FOREACH(map_t::value_type &it, description.service_map)
	{
		server_utils::service_description descr = it.second;
		libraries_names.insert(descr.library_name);
	}
	return libraries_names;
}

void server_utils::add_to_services_list( boost::property_tree::ptree config )
{
	std::multiset<std::string> classes = server_utils::get_services_class_names();
	std::multiset<std::string> libs = server_utils::get_services_libraries_names();

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
		config.get_child("config.services", server_utils::empty_class<boost::property_tree::ptree>()))
	{
		server_utils::service_description one_description;
		std::string service_library_name;
		std::string service_class_name;
		boost::property_tree::ptree individual_service_tree = (boost::property_tree::ptree) v.second ;

		std::string service_name = individual_service_tree.get<std::string>("name", "unnamed service");
		one_description.name = service_name;
		std::cout << std::endl << "Service name: " << service_name << std::endl;

		try{
			service_library_name = individual_service_tree.get<std::string>("library_name"); // Will throw error if not defined
			one_description.library_name = service_library_name;
			std::cout << "Library name: " << service_library_name << std::endl;

			service_class_name = individual_service_tree.get<std::string>("class_name"); // Will throw error if not defined
			one_description.class_name = service_class_name;
			std::cout << "Class name: " << service_class_name << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << std::endl << "Parsing library or class name error in service: " << service_name << std::endl;
			continue;
		}
		std::multiset<std::string>::iterator cn, ln;
		cn = classes.find(service_class_name);
		ln = libs.find(service_library_name);

		if((cn != classes.end()) || (ln != libs.end()))
		{
			std::cout << "Service: " << service_name << "already exists" << std::endl; 
			continue;
		}

		boost::property_tree::ptree service_properties_tree = individual_service_tree.get_child("properties", server_utils::empty_class<boost::property_tree::ptree>());

		std::string root_service_web_path = service_properties_tree.get<std::string>("root_service_web_path", "");
		if(!root_service_web_path.empty()){
			one_description.root_service_web_path = root_service_web_path;
			std::cout << "Service web root directory path: " << root_service_web_path << std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &va,
			service_properties_tree.get_child("arguments", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.set_of_arguments_rules.insert(std::pair<std::string, std::string>( va.first.data(), va.second.data() ) );
			std::cout << "Required argument: " << va.first.data() << " : " << va.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vh,
			service_properties_tree.get_child("headers", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.set_of_header_rules.insert(std::pair<std::string, std::string>(vh.first.data(), vh.second.data()));
			std::cout << "Required header: " << vh.first.data() << " : " << vh.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child("url_extensions", server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.url_extensions.insert(vp.second.data());
			std::cout << "Supported url extension: " << vp.second.data() <<  std::endl;
		}

		one_description.service_custome_properties_tree = service_properties_tree.get_child("settings", server_utils::empty_class<boost::property_tree::ptree>());

		try{
			boost::shared_ptr<service> one_service = util->give_me_class<service, boost::property_tree::ptree>(service_library_name, service_class_name, one_description.service_custome_properties_tree);
			description.service_map.insert(std::pair<boost::shared_ptr<service>, server_utils::service_description>(one_service, one_description));
		}
		catch(std::exception &e)
		{
			std::cout << "Error while creating service: " << service_name << std::endl;
		}
	}
}

server_utils::request_data server_utils::parse_request( http_request request )
{
	server_utils::request_data rd;
	rd.arguments = request.arguments;
	rd.headers = request.headers;
	rd.url = request.url;
	rd.url_extension = request.url.substr(request.url.find_last_of(".") + 1);
	return rd;
}

int server_utils::relevance(const server_utils::service_description &r, const server_utils::request_data &d )
{
	int rel = 0;
	if(!d.url.substr(d.url.find(r.root_service_web_path) + 1).empty())
	{
		rel += 100;
	}
	if (r.url_extensions.find(d.url_extension) != r.url_extensions.end())
	{
		rel += 50;
	}
	std::multiset<std::string> libraries_names;
	typedef std::map<std::string, std::string> map_s_t;
	typedef boost::unordered_multimap<std::string, std::string> multimap_s_t;

	BOOST_FOREACH(map_s_t::value_type data_it, d.arguments)
	{
		BOOST_FOREACH(multimap_s_t::value_type rule_it, r.set_of_arguments_rules)
		{
			if( rule_it.first.data() == data_it.first.data())
			{
				if(data_it.second.find(rule_it.second) !=std::string::npos)
				{
					rel += 1;
				}
			}
		}
	}

	BOOST_FOREACH(map_s_t::value_type data_it, d.headers)
	{
		BOOST_FOREACH(multimap_s_t::value_type rule_it, r.set_of_header_rules)
		{
			if( rule_it.first.data() == data_it.first.data())
			{
				if(data_it.second.find(rule_it.second) !=std::string::npos)
				{
					rel += 1;
				}
			}
		}
	}

	return rel;
}

boost::shared_ptr<service> server_utils::find_service(server_utils::request_data & d)
{
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	boost::shared_ptr<service> result;
	int pre_max = -2;
	int max = -1;
	BOOST_FOREACH(map_t::value_type data_it, this->description.service_map)
	{
		int current = server_utils::relevance(data_it.second, d);
		if (current > max)
		{
			pre_max = max;
			max = current;
			result = data_it.first;
		}
	}
	if (pre_max == max)
	{
		throw std::exception("Could not find suitable service.");
	}
	
	return result;
}