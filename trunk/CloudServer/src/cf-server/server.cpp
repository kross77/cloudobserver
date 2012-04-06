#include "server.h"

server::server(boost::property_tree::ptree config) 
{
	#ifdef DEBUG
		warning = new log_util(1, true, true, "log.txt");
		info = new log_util(1, true, true, "log.txt");
	#else
		warning = new log_util(1024, false, true, "log.txt");
		info = new log_util(1024, false, false, "log.txt");
	#endif
	error = new log_util(1, true, true, "log.txt");
	start_up_info = new log_util(1, true, true, "log.txt");

	error->use_prefix("error: ");
	error->use_time();

	warning->use_prefix("warning: ");
	warning->use_time();

	tread_util = new threading_utils();
	this->description.server_root_path = boost::filesystem::current_path();


	description = server_utils::parse_config(config, start_up_info, start_up_info, start_up_info);

	this->acceptor_thread = new boost::thread(&server::acceptor_loop, this);

	*(info) << "server created on port: " << description.port << log_util::endl;
}

server::~server()
{
	delete tread_util;
	delete error;
	delete warning;
	delete info;
	delete start_up_info;
}

void server::acceptor_loop(){

	// threads_pool has a destructor bug
	threads_pool = boost::shared_ptr<thread_pool>(new thread_pool(40));
	request_max_time = 5;
	
	//Move UAC into default services

	boost::asio::io_service io_service;
	int m_nPort = description.port;
	boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), m_nPort));
	*(info) << "Waiting for connection..." << std::endl << log_util::endl;
	while(true)
	{
		try
		{
			boost::shared_ptr<boost::asio::ip::tcp::socket> socket =
				boost::make_shared<boost::asio::ip::tcp::socket>(boost::ref(io_service));			
			acceptor.accept(*socket);
			*(info) << "connection accepted." << log_util::endl;
			user_info(*socket);
			boost::shared_ptr< boost::packaged_task<void> > task( new boost::packaged_task<void>( boost::bind(&server::request_response_loop, this, socket)));
			threads_pool->post(task);
		}
		catch(std::exception &e)
		{
			*(error) << e.what() << log_util::endl; //"The parameter is incorrect" exception
		}
	}
}

// We should forward request to shared library
void server::request_response_loop(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	try
	{
		bool connection_close = false;
		bool alive = false;

		do
		{
			boost::shared_ptr<http_request> request = boost::make_shared<http_request>();
			try
			{ 
				alive =	request->timed_receive(*socket, request_max_time);
			}
			catch (http_request::policy_file_request_exception)
			{
				*(info) << "Sending the 'crossdomain.xml' file." << log_util::endl;
				std::string policy_file =
					"<?xml version=\"1.0\"?>\n"
					"<!DOCTYPE cross-domain-policy SYSTEM \"http://www.macromedia.com/xml/dtds/cross-domain-policy.dtd\">\n"
					"<cross-domain-policy>\n"
					"  <allow-access-from domain=\"*\" to-ports=\"*\" />\n"
					"</cross-domain-policy>\n";
				socket->send(boost::asio::buffer(policy_file));
				socket->close();
				return;
			}
			if (!alive)
			{
				break;
			}

			*(info) << "request url: " << request->url << log_util::endl;

			boost::shared_ptr<shared> shared_data(new shared, boost::bind(&pointer_utils::delete_ptr<shared>, _1));
			shared_data->post("http_request", request->serialize_base(), true);

			boost::shared_ptr<http_response> response = boost::make_shared<http_response>();
			if (request->url == description.server_service_url)
			{
				server_service_call(socket, request, response);
				continue;
			}

			std::list<int>::iterator order_it;
			boost::shared_ptr<server_utils::service_container> service_cont;

			for (order_it=description.services_ids.begin(); order_it!=description.services_ids.end(); ++order_it)
			{
				service_cont = description.service_map[*order_it];
				boost::shared_ptr<base_service> requested_service = service_cont->service_ptr;

				service_check_input check_data;
				check_data.shared_data = shared_data->serialize();

				service_check_output check_data_out = requested_service->make_service_check(check_data);
				if((*(check_data_out.call_me_as) == "executor") || *(check_data_out.call_me_as) == "assistant")
				{
					try
					{
						shared_data->deserialize(check_data_out.shared_data);
						service_call_input data;
						data.socket = socket;			
						data.shared_data = shared_data->serialize();
						tread_util->safe_insert<boost::thread::id, std::set<boost::thread::id> >(boost::this_thread::get_id(),service_cont->threads_ids);
						service_call_output service_output;
						service_output = requested_service->make_service_call(data);
						if ((*(service_output.error_data)) != "")
						{
							std::ostringstream body;
							body << "@"<< service_cont->class_name <<" error: " << (*(service_output.error_data)) << "\n <br/> <a href='/'>please come again!</a>";
							response->body = "<head></head><body><h1>" + body.str() + "</h1></body>";
							response->headers["Content-Length"] = boost::lexical_cast<std::string>(response->body.length());
							response->send(*socket);

							*(error) << (*(service_output.error_data)) << log_util::endl;
						}
						shared_data->deserialize(service_output.shared_data);
						tread_util->safe_erase<boost::thread::id, std::set<boost::thread::id> >(boost::this_thread::get_id(), service_cont->threads_ids);
					}
					catch(std::exception &e)
					{
						*(error) << e.what() << log_util::endl; //"The parameter is incorrect" exception
					}
					if (*(check_data_out.call_me_as) == "assistant")
					{
						order_it=description.services_ids.begin();
					}
					if (*(check_data_out.call_me_as) == "executor")
					{
						break;
					}

				}
			}
			*(info) << "request resolved." << log_util::endl;
		}
		while(!connection_close);
	}
	catch(std::exception &e)
	{
		*(error) << e.what() << log_util::endl; //"The parameter is incorrect" exception
	}
	socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	socket->close();
	*(info) << "connection closed, socket disconnected" <<  log_util::endl;
}

void server::server_service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
{
	server_services_list(socket, response, request);
}

void server::server_services_list(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
{

	std::ostringstream user_files_stream;
	user_files_stream << "[";
	typedef std::map<int, boost::shared_ptr<server_utils::service_container> >  int_map;
	BOOST_FOREACH( int_map::value_type p, description.service_map )
	{
		boost::shared_lock<boost::shared_mutex> lock_r(p.second->edit_mutex_);

		if (boost::iequals(p.second->description_type , "public"))
		{
			user_files_stream << "\n\t{\n\t\t\"name\": \""
				<< p.second->service_name << "\",\n\t\t\"description\": \""
				<< p.second->description_text << "\",\n\t\t\"url\": \""
				<< p.second->description_default_url_path << "\",\n\t\t\"icon\": \""
				<< p.second->description_icon_file_path << "\"\n\t},";
		}
	}

	std::string files_ = user_files_stream.str();
	if (files_.length() > 5)
		files_ = files_.substr(0, files_.length() - 1);
	http_utils::set_json_content_type(response);
	http_utils::send(files_.append("\n]"), socket, response, request);

	return;
}

void server::user_info(boost::asio::ip::tcp::socket &socket)
{
	boost::asio::ip::tcp::endpoint remote_endpoint = socket.remote_endpoint();
	boost::asio::ip::address addr = remote_endpoint.address();
	std::string addr_string = addr.to_string();
	unsigned short port = remote_endpoint.port();

	*(info) << "User address: " << addr_string << log_util::endl;
	*(info) << "User port: " << port << log_util::endl;
}