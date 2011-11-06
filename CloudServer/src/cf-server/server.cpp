#include "server.h"

server::server(boost::property_tree::ptree config) 
{
	threads_pool = boost::shared_ptr<thread_pool>(new thread_pool(40));
	request_max_time = 5;
	general_util = new general_utils();

	uac = new user_control();
	boost::property_tree::ptree pt;
	uac->apply_config(pt);

	util = new server_utils();
	util->description = util->parse_config(config);
	util->update_properties_manager();

	this->acceptor_thread = new boost::thread(&server::acceptor_loop, this);

	*(util->info) << "server created on port: " << util->description.port << log_util::endl;
}

server::~server()
{
	delete util;
	delete uac;
}

void server::acceptor_loop(){
	boost::asio::io_service io_service;
	int m_nPort = util->description.port;
	boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), m_nPort));
	*(util->info) << "Waiting for connection..." << std::endl << log_util::endl;
	while(true)
	{
		try
		{
			boost::shared_ptr<boost::asio::ip::tcp::socket> socket =
				boost::make_shared<boost::asio::ip::tcp::socket>(boost::ref(io_service));			
			acceptor.accept(*socket);
			*(util->info) << "connection accepted." << log_util::endl;
			user_info(*socket);
			boost::shared_ptr< boost::packaged_task<void> > task( new boost::packaged_task<void>( boost::bind(&server::request_response_loop, this, socket)));
			threads_pool->post(task);
		}
		catch(std::exception &e)
		{
			*(util->error) << e.what() << log_util::endl; //"The parameter is incorrect" exception
		}
	}
}

// We should forward request to shared library
void server::request_response_loop(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	try
	{
		bool connection_close = true;
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
				*(util->info) << "Sending the 'crossdomain.xml' file." << log_util::endl;
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
				return;
			}

			//*(util->info) << "request url: " << request->url << log_util::endl;

			boost::shared_ptr<http_response> response = boost::make_shared<http_response>();
			std::ostringstream formatter;
			//formatter.imbue(std::locale(std::cout.getloc(), new boost::posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT")));
			//formatter << boost::posix_time::second_clock::local_time();
			response->headers.insert(std::pair<std::string, std::string>("Date",  boost::posix_time::to_iso_extended_string(  boost::posix_time::second_clock::universal_time() )));//formatter.str()));
			response->headers.insert(std::pair<std::string, std::string>("Server", "Cloud Server v0.5"));

			if (boost::iequals(request->headers["Connection"], "Keep-Alive"))
			{
				connection_close = false;
				response->headers.insert(std::pair<std::string, std::string>("Connection", "Keep-Alive"));
			}
			else
			{
				response->headers.insert(std::pair<std::string, std::string>("Connection", "Close"));
			}

			try
			{
				std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > login = uac->service_call(socket, request, response);
				request = login.first;
				response = login.second;
			}
			catch (std::exception &e)
			{
				*(util->error) << e.what() << log_util::endl;
			}

			if (request->url == util->description.server_service_url)
			{
				server_service_call(socket, request, response);
				return;
			}


			boost::shared_ptr<server_utils::service_container> service_cont;
			try
			{
				service_cont = util->find_service(*request);
			}
			catch(std::exception &e)
			{
				*(util->error) << "Could not find service for request." << log_util::endl;
				return;
			}

			boost::shared_ptr<service> requested_service = service_cont->service_ptr;

			util->tread_util->safe_insert<boost::thread::id, std::set<boost::thread::id> >(boost::this_thread::get_id(),service_cont->threads_ids);

			//*(util->info) << "ids size: " << service_cont->threads_ids.size() << log_util::endl;

			try
			{
				requested_service->make_service_call(socket, request, response);
			}
			catch(std::exception &e)
			{
				*(util->error) << e.what() << log_util::endl; //"The parameter is incorrect" exception
			}

			util->tread_util->safe_erase<boost::thread::id, std::set<boost::thread::id> >(boost::this_thread::get_id(), service_cont->threads_ids);

			//*(util->info) << "connection resolved." << log_util::endl;
		}
		while(!connection_close);
	}

	catch(std::exception &e)
	{
		*(util->error) << e.what() << log_util::endl; //"The parameter is incorrect" exception
	}
	//*(util->info) << "dis-connection" <<  log_util::endl;
}

void server::server_service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
{
	server_services_list(socket, response);
}

void server::server_services_list(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response)
{

	std::ostringstream user_files_stream;
	user_files_stream << "[";

	std::map<std::string, boost::shared_ptr<server_utils::service_container> >::iterator it;

	for ( it=util->description.service_map.begin() ; it != util->description.service_map.end(); it++ )
	{
		boost::shared_lock<boost::shared_mutex> lock_r(it->second->edit_mutex_);

		if (boost::iequals(it->second->description_type , "public"))
		{
			user_files_stream << "\n\t{\n\t\t\"name\": \""
				<< it->first << "\",\n\t\t\"description\": \""
				<<  it->second->description_text << "\",\n\t\t\"url\": \""
				<< it->second->description_default_url_path << "\",\n\t\t\"icon\": \""
				<< it->second->description_icon_file_path << "\"\n\t},";
		}

	}

	std::string files_ = user_files_stream.str();
	if (files_.length() > 5)
		files_ = files_.substr(0, files_.length() - 1);

	response->body = files_.append("\n]");
	response->body_size = response->body.length();
	response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(response->body_size)));
	response->send(*socket);

	return;
}

void server::user_info(boost::asio::ip::tcp::socket &socket)
{
	boost::asio::ip::tcp::endpoint remote_endpoint = socket.remote_endpoint();
	boost::asio::ip::address addr = remote_endpoint.address();
	std::string addr_string = addr.to_string();
	unsigned short port = remote_endpoint.port();

	*(util->info) << "User address: " << addr_string << log_util::endl;
	*(util->info) << "User port: " << port << log_util::endl;
}

boost::property_tree::ptree server::get_configuration()
{
	return util->save_config(util->description);
}
