#include "server.h"

server::server(boost::property_tree::ptree config) 
{
	util = new server_utils();
	util->description = util->parse_config(config);
	this->acceptor_thread = new boost::thread(&server::acceptor_loop, this);
	std::cout << "server created on port: " << util->description.port << std::endl;
}

server::~server()
{
}

void server::acceptor_loop(){
	boost::asio::io_service io_service;
	int m_nPort = util->description.port;
	boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), m_nPort));
	std::cout << "Waiting for connection..." << std::endl << std::endl;
	while(true)
	{
		try
		{
			boost::shared_ptr<boost::asio::ip::tcp::socket> socket =
				boost::make_shared<boost::asio::ip::tcp::socket>(boost::ref(io_service));			
			acceptor.accept(*socket);
			std::cout << "connection accepted." << std::endl;
			user_info(*socket);
			boost::thread workerThread(&server::request_response_loop, this, socket);
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl; //"The parameter is incorrect" exception
		}
	}
}

// We should forward request to shared library
void server::request_response_loop(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	try
	{
		http_request request;
		try
		{
			request.receive(*socket);
		}
		catch (http_request::policy_file_request_exception)
		{
			std::cout << "Sending the 'crossdomain.xml' file." << std::endl;
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

		std::cout << "request url: " << request.url << "\n";
		util->print->print_map_contents(request.headers, "headers");
		util->print->print_map_contents(request.arguments, "arguments");
		try
		{
			boost::shared_ptr<service> requested_service = server::find_service(request);
			requested_service->service_call(request, socket);
			if (requested_service->get_auto_close_socket())
			{
				socket->close();
			}
		}
		catch(std::exception &e)
		{
			std::cout << "Could not find service for request." << std::endl;
		}

		std::cout << "connection resolved." << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl; //"The parameter is incorrect" exception
	}
}

void server::user_info(boost::asio::ip::tcp::socket &socket)
{
	boost::asio::ip::tcp::endpoint remote_endpoint = socket.remote_endpoint();
	boost::asio::ip::address addr = remote_endpoint.address();
	std::string addr_string = addr.to_string();
	unsigned short port = remote_endpoint.port();

	std::cout << "User address: " << addr_string << std::endl;
	std::cout << "User port: " << port << std::endl;
}

boost::property_tree::ptree server::get_configuration()
{
	return util->save_config(util->description);
}

boost::shared_ptr<service> server::find_service( http_request request )
{
	server_utils::request_data request_data = util->parse_request(request);
	return util->find_service(request_data);
}