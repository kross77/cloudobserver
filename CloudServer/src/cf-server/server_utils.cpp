#include "server_utils.h"

server_utils::server_utils()
{
	error = new log_util(1024, true, true, "log.txt");
	error->use_prefix("error: ");
	error->use_time();
	warning = new log_util(1024 * 8, false, true, "log.txt");
	warning->use_prefix("warning: ");
	warning->use_time();
	info = new log_util(1024 * 32, false, true, "log.txt");

	util = new extension_utils();
	tread_util = new threading_utils();
	tread_util_local = new threading_utils();
	this->description.server_root_path = boost::filesystem::current_path();

	//grammar
	tag_service = "service";
	tag_library_name = "library_name";
	tag_service_name = "name";
	tag_class_name = "class_name";
	tag_properties = "properties";
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
	tag_path_configuration_database = tag_configuration + "." + "database";
	tag_path_configuration_properties_manager = tag_configuration + "." +"properties_manager";
	tag_arguments_price = "arguments_price";
	tag_headers_price = "headers_price";
	tag_url_price = "url_price";
	tag_url_extensions_price = "url_extensions_price";
	tag_default_price = "default_price";

	//request properties pricing manager set up.
	default_price = 0;
	arguments_price = default_price;
	headers_price = default_price;
	url_price = default_price;
	url_extensions_price = default_price;
}

server_utils::~server_utils()
{
	delete error;
	delete warning;
	delete info;

	delete util;
	delete tread_util;
	delete tread_util_local;
}

boost::shared_ptr<service> server_utils::create_service(std::string library_name, std::string class_name_inside_lib, boost::property_tree::ptree config)
{
	return util->give_me_class<service, boost::property_tree::ptree>(library_name, class_name_inside_lib, config);
}

//Do not forget to change save_config if you change parse_config_services
std::map<std::string, boost::shared_ptr<server_utils::service_container> > server_utils::parse_config_services( boost::property_tree::ptree config )
{
	std::map<std::string, boost::shared_ptr<server_utils::service_container> > services_map;

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
		config.get_child(tag_path_configuration_services, server_utils::empty_class<boost::property_tree::ptree>()))
	{
		boost::shared_ptr<server_utils::service_container> one_description(new server_utils::service_container);
		std::string service_name;
		std::string service_library_name;
		std::string service_class_name;
		boost::property_tree::ptree individual_service_tree = (boost::property_tree::ptree) v.second ;

		try
		{
			service_name = individual_service_tree.get<std::string>(tag_service_name); // Will throw error if not defined
			*info << std::endl << "Service name: " << service_name << log_util::endl;

			service_library_name = individual_service_tree.get<std::string>(tag_library_name); // Will throw error if not defined
			one_description->library_name = service_library_name;
			*info << "Library name: " << service_library_name << log_util::endl;

			service_class_name = individual_service_tree.get<std::string>(tag_class_name); // Will throw error if not defined
			one_description->class_name = service_class_name;
			*info << "Class name: " << service_class_name << log_util::endl;
		}
		catch(std::exception &e)
		{
			*error << std::endl << "Parsing service library, class or name error in service: " << service_name << log_util::endl;
			continue;
		}

		one_description->service_custome_properties_tree = individual_service_tree.get_child(tag_settings, server_utils::empty_class<boost::property_tree::ptree>());

		boost::property_tree::ptree service_properties_tree = individual_service_tree.get_child(tag_properties, server_utils::empty_class<boost::property_tree::ptree>());

		int service_price = service_properties_tree.get<int>(tag_default_price, default_price);
		one_description->default_price = service_price;
		if(service_price != default_price){
			*info << "Service price: " << service_price << log_util::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &va,
			service_properties_tree.get_child(tag_url, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			if (va.first == tag_url_equals)
				one_description->set_of_url_rules.push_back(std::string(va.second.data()));
			*info << "Required url: " << va.second.data() << log_util::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &va,
			service_properties_tree.get_child(tag_arguments, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description->set_of_arguments_rules.insert(std::pair<std::string, std::string>( va.first.data(), va.second.data() ) );
			*info << "Required argument: " << va.first.data() << " : " << va.second.data() <<  log_util::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vh,
			service_properties_tree.get_child(tag_headers, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description->set_of_header_rules.insert(std::pair<std::string, std::string>(vh.first.data(), vh.second.data()));
			*info << "Required header: " << vh.first.data() << " : " << vh.second.data() <<  log_util::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child(tag_url_extensions, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description->url_extensions.insert(vp.second.data());
			*info << "Supported url extension: " << vp.second.data() <<  log_util::endl;
		}

		try{
			boost::shared_ptr<service> one_service = util->give_me_class<service>(service_library_name, service_class_name);
			try
			{
				boost::shared_ptr<boost::property_tree::ptree> service_custom_properties_tree(new boost::property_tree::ptree(one_description->service_custome_properties_tree));
				one_service->apply_config(service_custom_properties_tree);
				one_description->service_ptr = one_service;
			}
			catch (service::not_configurable_exception)
			{
				*warning << "Service '" << service_name << " is not configurable." << log_util::endl;
			}
			services_map.insert(std::pair<std::string, boost::shared_ptr<server_utils::service_container> >(service_name, one_description));
			one_service->start();
		}
		catch(std::exception &e)
		{
			*error << "error while creating service: " << service_name << log_util::endl;
		}
	}
	return services_map;
}

//Do not forget to change save_config if you change parse_config
server_utils::server_description server_utils::parse_config( boost::property_tree::ptree config )
{
	server_utils::server_description server_descr;
	*info << std::endl << "Server description: " << log_util::endl;

	server_descr.server_root_path = config.get(tag_path_configuration_server_root_path, boost::filesystem::current_path());
	*info << "Server root path: " << server_descr.server_root_path << log_util::endl;

	server_descr.port = config.get(tag_path_configuration_port, 12345);
	*info << "Server port: " << server_descr.port << log_util::endl;

	server_descr.database_name = config.get(tag_path_configuration_database, "server.db");
	*info << "Server database: " << server_descr.database_name << log_util::endl;

	*info << std::endl << "Request properties prices: " << log_util::endl;
	BOOST_FOREACH(boost::property_tree::ptree::value_type &vh,
		config.get_child(tag_path_configuration_properties_manager, server_utils::empty_class<boost::property_tree::ptree>()))
	{
		try
		{
			server_descr.properties_manager_map.insert(std::pair<std::string, int>(vh.first.data(), boost::lexical_cast<int>(vh.second.data())));
			*info << vh.first.data() << " : " << vh.second.data() <<  log_util::endl;
		}
		catch(boost::bad_lexical_cast &e)
		{
			throw std::runtime_error("Incorrect price value");
		}
	}
	
	*info << std::endl << "Server services: " << log_util::endl;
	server_descr.service_map = server_utils::parse_config_services( config );

	return server_descr;
}

//This does not work correctly, do not use this.
//TODO: rewrite this.
//Do not forget to change parse_config and/or parse_config_services if you change save_config
boost::property_tree::ptree server_utils::save_config( server_utils::server_description server_configuration_description )
{
	boost::property_tree::ptree root, arr;
	root.put<int>(tag_path_configuration_port, server_configuration_description.port);
	root.put<std::string>(tag_path_configuration_server_root_path, server_configuration_description.server_root_path.string());
	typedef std::map<std::string, boost::shared_ptr<server_utils::service_container> > map_t;
	BOOST_FOREACH( map_t::value_type &i, server_configuration_description.service_map)
	{
		boost::shared_ptr<server_utils::service_container> sm = i.second;
		boost::property_tree::ptree serv;

		serv.put<std::string>(tag_service_name, i.first);
		serv.put<std::string>(tag_class_name, sm->class_name);
		serv.put<std::string>(tag_library_name, sm->library_name);

		boost::property_tree::ptree serv_prop, serv_sett, head, arg, url;
		typedef boost::unordered_multimap<std::string, std::string> mulmap_t;
		bool headers_exist = false, args_exist = false, urls_exist=false;
		BOOST_FOREACH(  mulmap_t::value_type &iih, sm->set_of_arguments_rules)
		{
			args_exist = true;
			arg.push_back( std::make_pair(iih.first, iih.second));
		}
		BOOST_FOREACH(  mulmap_t::value_type &iia, sm->set_of_header_rules)
		{
			headers_exist = true;
			head.push_back( std::make_pair(iia.first, iia.second));
		}
		BOOST_FOREACH(  std::string &iiu, sm->set_of_url_rules)
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
		if(!sm->service_custome_properties_tree.empty())
		{
			BOOST_FOREACH(boost::property_tree::ptree::value_type &va, sm->service_custome_properties_tree)
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
	typedef std::map<std::string, boost::shared_ptr<server_utils::service_container> > map_t;
	BOOST_FOREACH(map_t::value_type &it, description.service_map)
	{
		service_names.insert(it.first);
	}
	return service_names;
}

boost::shared_ptr<server_utils::service_container> server_utils::get_service_description_by_name(std::string name)
{
	typedef std::map<std::string, boost::shared_ptr<server_utils::service_container> > map_t;
	map_t::iterator it = description.service_map.find(name);
	if (it != description.service_map.end())
	{
		return it->second;
	} 
	else
	{
		throw std::runtime_error("Service with such name was not found map not found!");
	}
	boost::shared_ptr<server_utils::service_container> null;
	return null;
}

boost::shared_ptr<service> server_utils::get_service_by_name(std::string name)
{
	typedef std::map<std::string, boost::shared_ptr<server_utils::service_container> > map_t;
	map_t::iterator it = description.service_map.find(name);
	if (it != description.service_map.end())
	{
		return it->second->service_ptr;
	} 
	else
	{
		throw std::runtime_error("Service with such name was not found map not found!");
	}
	boost::shared_ptr<service> null;
	return null;
}

std::multiset<std::string> server_utils::get_services_class_names()
{
	std::multiset<std::string> class_names;
	typedef std::map<std::string, boost::shared_ptr<server_utils::service_container> > map_t;
	BOOST_FOREACH(map_t::value_type &it, description.service_map)
	{
		boost::shared_ptr<server_utils::service_container> descr = it.second;
		class_names.insert(descr->class_name);
	}
	return class_names;
}

std::multiset<std::string> server_utils::get_services_libraries_names()
{
	std::multiset<std::string> libraries_names;
	typedef std::map<std::string, boost::shared_ptr<server_utils::service_container> > map_t;
	BOOST_FOREACH(map_t::value_type &it, description.service_map)
	{
		boost::shared_ptr<server_utils::service_container> descr = it.second;
		libraries_names.insert(descr->library_name);
	}
	return libraries_names;
}

void server_utils::add_to_services_list( boost::property_tree::ptree config )
{
	std::multiset<std::string> classes = server_utils::get_services_class_names();
	std::multiset<std::string> libs = server_utils::get_services_libraries_names();
	typedef std::map<std::string, boost::shared_ptr<server_utils::service_container> > map_t;
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
		config.get_child("config.services", server_utils::empty_class<boost::property_tree::ptree>()))
	{
		boost::shared_ptr<server_utils::service_container> one_description(new server_utils::service_container);
		std::string service_library_name;
		std::string service_class_name;
		boost::property_tree::ptree individual_service_tree = (boost::property_tree::ptree) v.second ;
		std::string service_name = individual_service_tree.get<std::string>(tag_service_name);

		map_t::iterator mitr = description.service_map.find(service_name);
		if(mitr != description.service_map.end())
		{
			*warning << std::endl << "Service: " << service_name << " already exists." << log_util::endl;
			continue;
		}
		*info << std::endl << "Service name: " << service_name << log_util::endl;

		try{
			service_library_name = individual_service_tree.get<std::string>(tag_library_name); // Will throw error if not defined
			one_description->library_name = service_library_name;
			*info << "Library name: " << service_library_name << log_util::endl;

			service_class_name = individual_service_tree.get<std::string>(tag_class_name); // Will throw error if not defined
			one_description->class_name = service_class_name;
			*info << "Class name: " << service_class_name << log_util::endl;
		}
		catch(std::exception &e)
		{
			*error << std::endl << "Parsing library or class name error in service: " << service_name << log_util::endl;
			continue;
		}

		one_description->service_custome_properties_tree = individual_service_tree.get_child(tag_settings, server_utils::empty_class<boost::property_tree::ptree>());
		boost::property_tree::ptree service_properties_tree = individual_service_tree.get_child(tag_properties, server_utils::empty_class<boost::property_tree::ptree>());

		BOOST_FOREACH(boost::property_tree::ptree::value_type &va,
			service_properties_tree.get_child(tag_arguments, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description->set_of_arguments_rules.insert(std::pair<std::string, std::string>( va.first.data(), va.second.data() ) );
			*info << "Required argument: " << va.first.data() << " : " << va.second.data() <<  log_util::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vh,
			service_properties_tree.get_child(tag_headers, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description->set_of_header_rules.insert(std::pair<std::string, std::string>(vh.first.data(), vh.second.data()));
			*info << "Required header: " << vh.first.data() << " : " << vh.second.data() <<  log_util::endl;
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &vp,
			service_properties_tree.get_child(tag_url_extensions, server_utils::empty_class<boost::property_tree::ptree>()))
		{
			one_description->url_extensions.insert(vp.second.data());
			*info << "Supported url extension: " << vp.second.data() <<  log_util::endl;
		}

		try
		{
			one_description->service_ptr = util->give_me_class<service, boost::property_tree::ptree>(service_library_name, service_class_name, one_description->service_custome_properties_tree);
			description.service_map.insert(std::pair<std::string, boost::shared_ptr<server_utils::service_container> >(service_name, one_description));
		}
		catch(std::exception &e)
		{
			*error << "error while creating service: " << service_name << log_util::endl;
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

int server_utils::relevance(boost::shared_ptr<server_utils::service_container> rules_container, const server_utils::request_data &data_container)
{

	int rel = default_price;

	rel += rules_container->default_price;

	if (rules_container->url_extensions.find(data_container.url_extension) != rules_container->url_extensions.end())
	{
		rel += url_extensions_price;
	}

	typedef std::vector<std::string> vector_s_t;
	BOOST_FOREACH(vector_s_t::value_type rule_it, rules_container->set_of_url_rules)
	{
		if (rule_it == data_container.url)
			rel += url_price;
	}

	std::multiset<std::string> libraries_names;
	typedef std::map<std::string, std::string> map_s_t;
	typedef boost::unordered_multimap<std::string, std::string> multimap_s_t;

	BOOST_FOREACH(map_s_t::value_type data_it, data_container.arguments)
	{
		BOOST_FOREACH(multimap_s_t::value_type rule_it, rules_container->set_of_arguments_rules)
		{
			if( rule_it.first == data_it.first)
			{
				if(data_it.second.find(rule_it.second) !=std::string::npos)
				{
					rel += arguments_price;
				}
			}
		}
	}

	BOOST_FOREACH(map_s_t::value_type data_it, data_container.headers)
	{
		BOOST_FOREACH(multimap_s_t::value_type rule_it, rules_container->set_of_header_rules)
		{
			if( rule_it.first == data_it.first)
			{
				if(data_it.second.find(rule_it.second) !=std::string::npos)
				{
					rel += headers_price;
				}
			}
		}
	}

	return rel;
}

boost::shared_ptr<server_utils::service_container> server_utils::find_service(http_request request)
{
	request_data d = parse_request(request);
	typedef std::map<std::string, boost::shared_ptr<server_utils::service_container> > map_t;
	boost::shared_ptr<server_utils::service_container> result;
	int pre_max = -2;
	int max = -1;
	std::string name = "";
	BOOST_FOREACH(map_t::value_type &data_it, this->description.service_map)
	{
		int current = server_utils::relevance(data_it.second, d);
		if (current >= max)
		{
			pre_max = max;
			max = current;
			result = data_it.second;
			name = data_it.first;
		}
	}
	if (pre_max == max)
	{
		throw std::runtime_error("Could not find suitable service.");
	}
	*info << "Found service: " << name << log_util::endl;
	return result;
}

void server_utils::update_properties_manager()
{
	arguments_price = server_utils::find_or_null(description.properties_manager_map, tag_arguments_price);
	headers_price = server_utils::find_or_null(description.properties_manager_map, tag_headers_price);
	url_price = server_utils::find_or_null(description.properties_manager_map, tag_url_price);
	url_extensions_price = server_utils::find_or_null(description.properties_manager_map, tag_url_extensions_price);
}

int server_utils::find_or_null( std::map<std::string, int> map, std::string to_find)
{
	typedef std::map<std::string, int> map_si;
	return tread_util_local->safe_search_in_map<std::string, int, map_si::iterator>(to_find, map);
	
}