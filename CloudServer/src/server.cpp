#include "server.h"

server::server(boost::property_tree::ptree config) 
{
	util = new server_utils();
	util->description = util->parse_config(config);

	uac = new user_control(); 
	boost::property_tree::ptree pt; // TODO: extract config for uac in server_utils
	uac->apply_config(pt);

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
			boost::shared_ptr<boost::thread> p(new boost::thread(&server::request_response_loop, this, socket));
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
	util->tread_util->safe_insert<boost::thread::id, std::set<boost::thread::id> >(boost::this_thread::get_id(),threads_pool);
	try
	{
		boost::shared_ptr<http_request> request = boost::make_shared<http_request>();
		try
		{
			request->receive(*socket);
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

		std::cout << "request url: " << request->url << "\n";

		boost::shared_ptr<http_response> response = boost::make_shared<http_response>();
		std::ostringstream formatter;
		formatter.imbue(std::locale(std::cout.getloc(), new boost::posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT")));
		formatter << boost::posix_time::second_clock::local_time();
		response->headers.insert(std::pair<std::string, std::string>("Date", formatter.str()));
		response->headers.insert(std::pair<std::string, std::string>("Server", "Cloud Server v0.5"));

		try
		{
			std::pair<boost::shared_ptr<http_request>, boost::shared_ptr<http_response> > login = uac->service_call(socket, request, response);
			request = login.first;
			response = login.second;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}

		boost::shared_ptr<server_utils::service_container> service_cont;
		try
		{
			service_cont = util->find_service(*request);
		}
		catch(std::exception &e)
		{
			std::cout << "Could not find service for request." << std::endl;
		}

		boost::shared_ptr<service> requested_service = service_cont->service_ptr;

		util->tread_util->safe_insert<boost::thread::id, std::set<boost::thread::id> >(boost::this_thread::get_id(),service_cont->threads_ids);

		std::cout << "ids size: " << service_cont->threads_ids.size() << std::endl;

		try
		{
			requested_service->service_call(socket, request, response);
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl; //"The parameter is incorrect" exception
		}

		util->tread_util->safe_erase<boost::thread::id, std::set<boost::thread::id> >(boost::this_thread::get_id(), service_cont->threads_ids);

		std::cout << "connection resolved." << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl; //"The parameter is incorrect" exception
	}
	util->tread_util->safe_erase<boost::thread::id, std::set<boost::thread::id> >(boost::this_thread::get_id(),threads_pool);
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
