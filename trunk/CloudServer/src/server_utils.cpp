#include "server_utils.h"

server_utils::server_utils()
{
	util = new extension_utils();
	print = new printer();
	this->description.server_root_path = boost::filesystem::current_path();

	//grammar
	tag_service = "service";
	tag_library_name = "library_name";
	tag_service_name = "name";
	tag_class_name = "class_name";
	tag_properties = "properties";
	tag_root_service_web_path = "root_service_web_path";
	tag_url = "url";
	tag_arguments = "arguments";
	tag_headers = "headers";
	tag_url_extensions = "url_extensions";
	tag_settings = "settings";
	tag_configuration = "config";
	tag_url_equals = "equals";
	tag_path_configuration_services = tag_configuration + "." + "services";
	tag_path_configuration_server_root_path = tag_configuration + "." + "server_root_path";
	tag_path_configuration_port = tag_configuration + "." + "port";
}

boost::shared_ptr<service> server_utils::create_service(std::string library_name, std::string class_name_inside_lib, boost::property_tree::ptree config)
{
	return util->give_me_class<service, boost::property_tree::ptree>(library_name, class_name_inside_lib, config);
}

//Do not forget to change save_config if you change parse_config_services
std::map<boost::shared_ptr<service>, server_utils::service_description> server_utils::parse_config_services( boost::property_tree::ptree config )
{
	std::map<boost::shared_ptr<service>, server_utils::service_description> services_map;

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
		config.get_child(tag_path_configuration_services, server_utils::empty_class<boost::property_tree::ptree>()))
	{
		server_utils::service_description one_description;
		std::string service_library_name;
		std::string service_class_name;
		boost::property_tree::ptree individual_service_tree = (boost::property_tree::ptree) v.second ;

		std::string service_name = individual_service_tree.get<std::string>(tag_service_name, "unnamed service");
		one_description.name = service_name;
		std::cout << std::endl << "Service name: " << service_name << std::endl;

		try{
			service_library_name = individual_service_tree.get<std::string>(tag_library_name); // Will throw error if not defined
			one_description.library_name = service_library_name;
			std::cout << "Library name: " << service_library_name << std::endl;

			service_class_name = individual_service_tree.get<std::string>(tag_class_name); // Will throw error if not defined
			one_description.class_name = service_class_name;
			std::cout << "Class name: " << service_class_name << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << std::endl << "Parsing library or class name error in service: " << service_name << std::endl;
			continue;
		}

		one_description.service_custome_properties_tree = individual_service_tree.get_child(tag_settings, server_utils::empty_class<boost::property_tree::ptree>());

		boost::property_tree::ptree service_properties_tree = individual_service_tree.get_child(tag_properties, server_utils::empty_class<boost::property_tree::ptree>());

		std::string root_service_web_path = service_properties_tree.get<std::string>(tag_root_service_web_path, "");
		if(!root_service_web_path.empty()){
			one_description.root_service_web_path = root_service_web_path;
			std::cout << "Service web root directory path: " << root_service_web_path << std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &va,
			service_properties_tree.get_child(tag_url, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			if (va.first == tag_url_equals)
				one_description.set_of_url_rules.push_back(std::string(va.second.data()));
			std::cout << "Required url: " << va.second.data() << std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &va,
			service_properties_tree.get_child(tag_arguments, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.set_of_arguments_rules.insert(std::pair<std::string, std::string>( va.first.data(), va.second.data() ) );
			std::cout << "Required argument: " << va.first.data() << " : " << va.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vh,
			service_properties_tree.get_child(tag_headers, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.set_of_header_rules.insert(std::pair<std::string, std::string>(vh.first.data(), vh.second.data()));
			std::cout << "Required header: " << vh.first.data() << " : " << vh.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child(tag_url_extensions, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.url_extensions.insert(vp.second.data());
			std::cout << "Supported url extension: " << vp.second.data() <<  std::endl;
		}

		try{
			boost::shared_ptr<service> one_service = util->give_me_class<service>(service_library_name, service_class_name);
			try
			{
				one_service->apply_config(one_description.service_custome_properties_tree);
			}
			catch (service::not_configurable_exception)
			{
				std::cout << "Service '" << service_name << " is not configurable." << std::endl;
			}
			services_map.insert(std::pair<boost::shared_ptr<service>, server_utils::service_description>(one_service, one_description));
		}
		catch(std::exception &e)
		{
			std::cout << "Error while creating service: " << service_name << std::endl;
		}
	}
	return services_map;
}

//Do not forget to change save_config if you change parse_config
server_utils::server_description server_utils::parse_config( boost::property_tree::ptree config )
{
	server_utils::server_description server_descr;
	std::cout << std::endl << "Server description: " << std::endl;

	server_descr.server_root_path = config.get(tag_path_configuration_server_root_path, boost::filesystem::current_path());
	std::cout << "Server root path: " << server_descr.server_root_path << std::endl;

	server_descr.port = config.get(tag_path_configuration_port, 12345);
	std::cout << "Server port: " << server_descr.port << std::endl;

	std::cout << std::endl << "Server services: ";
	server_descr.service_map = server_utils::parse_config_services( config );
	std::cout << std::endl;

	return server_descr;
}

//Do not forget to change parse_config and/or parse_config_services if you change save_config
boost::property_tree::ptree server_utils::save_config( server_utils::server_description server_configuration_description )
{
	boost::property_tree::ptree root, arr;
	root.put<int>(tag_path_configuration_port, server_configuration_description.port);
	root.put<std::string>(tag_path_configuration_server_root_path, server_configuration_description.server_root_path.string());
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	BOOST_FOREACH( map_t::value_type &i, server_configuration_description.service_map)
	{
		server_utils::service_description sm = i.second;
		boost::property_tree::ptree serv;

		serv.put<std::string>(tag_service_name, sm.name);
		serv.put<std::string>(tag_class_name, sm.class_name);
		serv.put<std::string>(tag_library_name, sm.library_name);
		serv.put<std::string>(tag_root_service_web_path, sm.root_service_web_path);

		boost::property_tree::ptree serv_prop, serv_sett, head, arg, url;
		typedef boost::unordered_multimap<std::string, std::string> mulmap_t;
		bool headers_exist = false, args_exist = false, urls_exist=false;
		BOOST_FOREACH(  mulmap_t::value_type &iih, sm.set_of_arguments_rules)
		{
			args_exist = true;
			arg.push_back( std::make_pair(iih.first, iih.second));
		}
		BOOST_FOREACH(  mulmap_t::value_type &iia, sm.set_of_header_rules)
		{
			headers_exist = true;
			head.push_back( std::make_pair(iia.first, iia.second));
		}
		BOOST_FOREACH(  std::string &iiu, sm.set_of_url_rules)
		{
			urls_exist = true;
			url.push_back( std::make_pair(tag_url_equals, iiu));
		}
		if (args_exist)
		{
			serv_prop.push_back( std::make_pair(tag_arguments, arg));
		}
		if (headers_exist)
		{
			serv_prop.push_back( std::make_pair(tag_headers, head));
		}
		if (urls_exist)
		{
			serv_prop.push_back( std::make_pair(tag_url, url));
		}
		if((headers_exist) || (args_exist) || (urls_exist))
		{
			serv.push_back(std::make_pair(tag_properties, serv_prop));
		}
		if(!sm.service_custome_properties_tree.empty())
		{
			BOOST_FOREACH(boost::property_tree::ptree::value_type &va, sm.service_custome_properties_tree)
			{
				if(va.first.empty())
				{
					serv_sett.push_back(std::make_pair("", va.second));
				}
				else
				{
					serv_sett.push_back(std::make_pair(va.first, va.second));
				}
			}
			serv.push_back(std::make_pair(tag_settings, serv_sett));
		}
		arr.push_back(std::make_pair(tag_service, serv));
	}
	root.put_child(tag_path_configuration_services, arr);
	return root;
}

std::multiset<std::string> server_utils::get_services_names()
{
	std::multiset<std::string> service_names;
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	BOOST_FOREACH(map_t::value_type &it, description.service_map)
	{
		server_utils::service_description descr = it.second;
		service_names.insert(descr.name);
	}
	return service_names;
}

server_utils::service_description server_utils::get_service_description_by_name(std::string name)
{
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	BOOST_FOREACH(map_t::value_type &it, description.service_map)
	{
		server_utils::service_description descr = it.second;
		if(descr.name == name)
		{
			return it.second;
		}
	}
	throw std::runtime_error("Service with such name was not found map not found!");
	server_utils::service_description null;
	return null;
}

bool server_utils::find_service_by_name_iterator_function(std::pair<boost::shared_ptr<service>, server_utils::service_description> const & element, std::string name) const
{
	return element.second.name == name;
}

server_utils::service_description server_utils::stop_service_by_name(std::string name)
{
	/*typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	map_t::iterator map_it =   std::find_if(description.service_map.begin(), description.service_map.end(), std::bind1st(std::ptr_fun(&server_utils::find_service_by_name_iterator_function), name)); 

	if (map_it != description.service_map.end())
	{
	description.service_map.erase (map_it);
	} 
	else
	{
	throw std::runtime_error("Service with such name was not found map not found!");
	}*/
	server_utils::service_description null;
	return null;
}

boost::shared_ptr<service> server_utils::get_service_by_name(std::string name)
{
	typedef std::map<boost::shared_ptr<service>, server_utils::service_description> map_t;
	BOOST_FOREACH(map_t::value_type it, description.service_map)
	{
		server_utils::service_description descr = it.second;
		if(descr.name == name)
		{
			return it.first;
		}
	}
	throw std::runtime_error("Service with such name was not found map not found!");
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

		std::string service_name = individual_service_tree.get<std::string>(tag_service_name, "unnamed service");
		one_description.name = service_name;
		std::cout << std::endl << "Service name: " << service_name << std::endl;

		try{
			service_library_name = individual_service_tree.get<std::string>(tag_library_name); // Will throw error if not defined
			one_description.library_name = service_library_name;
			std::cout << "Library name: " << service_library_name << std::endl;

			service_class_name = individual_service_tree.get<std::string>(tag_class_name); // Will throw error if not defined
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

		one_description.service_custome_properties_tree = individual_service_tree.get_child(tag_settings, server_utils::empty_class<boost::property_tree::ptree>());
		boost::property_tree::ptree service_properties_tree = individual_service_tree.get_child(tag_properties, server_utils::empty_class<boost::property_tree::ptree>());

		std::string root_service_web_path = service_properties_tree.get<std::string>(tag_root_service_web_path, "");
		if(!root_service_web_path.empty()){
			one_description.root_service_web_path = root_service_web_path;
			std::cout << "Service web root directory path: " << root_service_web_path << std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &va,
			service_properties_tree.get_child(tag_arguments, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.set_of_arguments_rules.insert(std::pair<std::string, std::string>( va.first.data(), va.second.data() ) );
			std::cout << "Required argument: " << va.first.data() << " : " << va.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vh,
			service_properties_tree.get_child(tag_headers, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.set_of_header_rules.insert(std::pair<std::string, std::string>(vh.first.data(), vh.second.data()));
			std::cout << "Required header: " << vh.first.data() << " : " << vh.second.data() <<  std::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child(tag_url_extensions, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description.url_extensions.insert(vp.second.data());
			std::cout << "Supported url extension: " << vp.second.data() <<  std::endl;
		}

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
		rel += 100;
	}

	typedef std::vector<std::string> vector_s_t;
	BOOST_FOREACH(vector_s_t::value_type rule_it, r.set_of_url_rules)
	{
		if (rule_it == d.url)
			rel += 1000;
	}

	std::multiset<std::string> libraries_names;
	typedef std::map<std::string, std::string> map_s_t;
	typedef boost::unordered_multimap<std::string, std::string> multimap_s_t;

	BOOST_FOREACH(map_s_t::value_type data_it, d.arguments)
	{
		BOOST_FOREACH(multimap_s_t::value_type rule_it, r.set_of_arguments_rules)
		{
			if( rule_it.first == data_it.first)
			{
				if(data_it.second.find(rule_it.second) !=std::string::npos)
				{
					rel += 100;
				}
			}
		}
	}

	BOOST_FOREACH(map_s_t::value_type data_it, d.headers)
	{
		BOOST_FOREACH(multimap_s_t::value_type rule_it, r.set_of_header_rules)
		{
			if( rule_it.first == data_it.first)
			{
				if(data_it.second.find(rule_it.second) !=std::string::npos)
				{
					rel += 100;
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
	std::string name = "";
	BOOST_FOREACH(map_t::value_type data_it, this->description.service_map)
	{
		int current = server_utils::relevance(data_it.second, d);
		if (current >= max)
		{
			pre_max = max;
			max = current;
			result = data_it.first;
			name = data_it.second.name;
		}
	}
	if (pre_max == max)
	{
		throw std::runtime_error("Could not find suitable service.");
	}
	std::cout << "Found service: " << name << std::endl;
	return result;
}