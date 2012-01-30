#include "server_utils.h"

server_utils::server_utils()
{
	#ifdef DEBUG
	error = new log_util(512, true, true, "log.txt");
	warning = new log_util(512 * 8, true, true, "log.txt");
	info = new log_util(512 * 32, false, true, "log.txt");
	#else
	error = new log_util(1024, true, true, "log.txt");
	warning = new log_util(1024 * 8, false, true, "log.txt");
	info = new log_util(1024 * 32, false, false, "log.txt");
	#endif
	error->use_prefix("error: ");
	error->use_time();

	warning->use_prefix("warning: ");
	warning->use_time();

	tread_util = new threading_utils();
	tread_util_local = new threading_utils();
	this->description.server_root_path = boost::filesystem::current_path();

	//grammar
	tag_service = "service";
	tag_library_name = "library_name";
	tag_service_name = "name";
	tag_class_name = "class_name";
	tag_url = "url";
	tag_settings = "settings";

	tag_description = "description";
	tag_description_type = "type" ;
	tag_description_text = "text";
	tag_description_icon = "icon";
	tag_description_default_url = "default_url";

	tag_default_description_type = "private";
	tag_default_description_text = "description text";
	tag_default_description_icon = "default_service_icon.png";
	tag_default_description_url = "../";

	tag_configuration = "config";
	tag_path_configuration_services = tag_configuration + "." + "services";
	tag_path_configuration_server_root_path = tag_configuration + "." + "server_root_path";
	tag_path_configuration_port = tag_configuration + "." + "port";
	tag_path_configuration_server_service_url = tag_configuration + "." + "server_service_url";
	tag_path_configuration_database = tag_configuration + "." + "database";
}

server_utils::~server_utils()
{
	delete tread_util;
	delete tread_util_local;
}

boost::shared_ptr<base_service> server_utils::create_service(std::string library_name, std::string class_name_inside_lib, boost::property_tree::ptree config)
{
	return extension_utils::give_me_class<base_service, boost::property_tree::ptree>(library_name, class_name_inside_lib, config);
}

//Do not forget to change save_config if you change parse_config_services
std::map<int, boost::shared_ptr<server_utils::service_container> > server_utils::parse_config_services( boost::property_tree::ptree config )
{
	typedef std::map<int, boost::shared_ptr<server_utils::service_container> >  int_map;
	int_map services_map;

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
			one_description->service_name = service_name;
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

		boost::property_tree::ptree service_description_tree = individual_service_tree.get_child(tag_description, server_utils::empty_class<boost::property_tree::ptree>());
		one_description->description_default_url_path = service_description_tree.get<std::string>(tag_description_default_url,  tag_default_description_url);
		one_description->description_icon_file_path = service_description_tree.get<std::string>(tag_description_icon,  tag_default_description_icon);
		one_description->description_text = service_description_tree.get<std::string>(tag_description_text,  tag_default_description_text);
		one_description->description_type = service_description_tree.get<std::string>(tag_description_type,  tag_default_description_type);

		one_description->service_custome_properties_tree = individual_service_tree.get_child(tag_settings, server_utils::empty_class<boost::property_tree::ptree>());

		int order = individual_service_tree.get<unsigned int>("call", -1);
		if (order == -1)
		{
			std::string err = "configuration incorrect - some services order value is not set.";
			*error << std::endl << err<< " Found while parsing " << service_name << log_util::endl;
			throw std::runtime_error("");
		}

		int_map::iterator order_it;
		order_it = services_map.find(order);
		if (order_it != services_map.end())
		{
			std::string err = "configuration incorrect - services order duplication is presented.";
			*error << std::endl << err<< " Found while parsing " << service_name << log_util::endl;
			throw std::runtime_error("");
		}

		services_ids.push_back(order);
		services_ids.sort(std::less<int>());

		one_description->order = order;
		*info << "Service order: " << order << log_util::endl;
		

		try{
			boost::shared_ptr<base_service> one_service = extension_utils::give_me_class<base_service>(service_library_name, service_class_name);
			try
			{
				boost::shared_ptr<boost::property_tree::ptree> service_custom_properties_tree(new boost::property_tree::ptree(one_description->service_custome_properties_tree));
				one_service->apply_config(service_custom_properties_tree);
				one_description->service_ptr = one_service;
			}
			catch (base_service::not_configurable_exception)
			{
				*warning << "Service '" << service_name << " is not configurable." << log_util::endl;
			}
			services_map.insert(int_map::value_type(order, one_description));
			one_service->start();
		}
		catch(std::exception &e)
		{
			*error << "error while creating service: " << service_name << log_util::endl;
		}
	}
	return services_map;
}

server_utils::server_description server_utils::parse_config( boost::property_tree::ptree config )
{
	server_utils::server_description server_descr;
	*info << std::endl << "Server description: " << log_util::endl;

	server_descr.server_root_path = config.get(tag_path_configuration_server_root_path, boost::filesystem::current_path());
	*info << "Server root path: " << server_descr.server_root_path << log_util::endl;

	server_descr.port = config.get(tag_path_configuration_port, 12345);
	*info << "Server port: " << server_descr.port << log_util::endl;

	server_descr.server_service_url = config.get(tag_path_configuration_server_service_url, "/server.json");
	*info << "Server Service Url: " << server_descr.server_service_url << log_util::endl;

	server_descr.database_name = config.get(tag_path_configuration_database, "server.db");
	*info << "Server database: " << server_descr.database_name << log_util::endl;

	*info << std::endl << "Server services: " << log_util::endl;
	server_descr.service_map = server_utils::parse_config_services( config );

	return server_descr;
}

std::multiset<std::string> server_utils::get_services_names()
{
	std::multiset<std::string> service_names;
	typedef std::map<int, boost::shared_ptr<server_utils::service_container> >  int_map;
	BOOST_FOREACH( int_map::value_type p, description.service_map )
	{
		service_names.insert(p.second->service_name);
	}
	return service_names;
}

boost::shared_ptr<server_utils::service_container> server_utils::get_service_description_by_name(std::string name)
{
	typedef std::map<int, boost::shared_ptr<server_utils::service_container> >  int_map;
	BOOST_FOREACH( int_map::value_type p, description.service_map )
	{
		 if( p.second->service_name == name)
			 return p.second;
	}

	throw std::runtime_error("Service with such name was not found map not found!");
}

boost::shared_ptr<base_service> server_utils::get_service_by_name(std::string name)
{
	typedef std::map<int, boost::shared_ptr<server_utils::service_container> >  int_map;
	BOOST_FOREACH( int_map::value_type p, description.service_map )
	{
		if( p.second->service_name == name)
			return p.second->service_ptr;
	}

	throw std::runtime_error("Service with such name was not found map not found!");
}

std::multiset<std::string> server_utils::get_services_class_names()
{
	std::multiset<std::string> class_names;
	typedef std::map<int, boost::shared_ptr<server_utils::service_container> >  int_map;
	BOOST_FOREACH( int_map::value_type p, description.service_map )
	{
		class_names.insert(p.second->class_name);
	}
	return class_names;
}

std::multiset<std::string> server_utils::get_services_libraries_names()
{
	std::multiset<std::string> libraries_names;
	typedef std::map<int, boost::shared_ptr<server_utils::service_container> >  int_map;
	BOOST_FOREACH( int_map::value_type p, description.service_map )
	{
		libraries_names.insert(p.second->library_name);
	}
	return libraries_names;
}