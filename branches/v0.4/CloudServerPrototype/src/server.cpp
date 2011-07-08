#include "server.h"
// We should provide each server client with a thread for dealing with his request

server::server(int config) 
{
	_config = config;
	print = new printer();
	util = new extension_utils();
	this->acceptor_thread = new boost::thread(&server::acceptor_loop, this);
	std::cout << "server created on port: " << _config << std::endl;
}
server::~server()
{
}

void server::acceptor_loop(){
	boost::asio::io_service io_service;
	int m_nPort = _config;
	boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), m_nPort));
	std::cout << "Waiting for connection..." << std::endl;
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
		http_request request(*socket);
		std::cout << "request url: " << request.url << "\n";
		print->print_map_contents(request.headers, "headers");
		print->print_map_contents(request.arguments, "arguments");
		//response.body = "<head></head><body><h1>It Rocks!</h1></body>";
		//TODO: Make server library independent via ptree config and options filtering. 
		//TODO: move services creation to some other place constructor for example.
		boost::extensions::type_map types;
		std::string library_path_to_FS= util->add_prefix_and_suffix("services.file");
		boost::extensions::shared_library lib(library_path_to_FS); 
		if (!lib.open()) {
			std::cerr << "Library failed to open: " << library_path_to_FS << std::endl;
		} 
		if (!lib.call(types)) {
			std::cerr << "Library has no services!" << std::endl;
		}
		std::map<std::string, boost::extensions::factory<service, boost::filesystem::path> >& factories(types.get());
		if (factories.empty()) {
			std::cerr << "Desired service was not found!" << std::endl;
		}
		// Create each service.
		boost::filesystem::path file_service_default_path = boost::filesystem::current_path();
		for (std::map<std::string, boost::extensions::factory<service, boost::filesystem::path> >::iterator it
			= factories.begin();
			it != factories.end(); ++it) {
				
				std::cout << "Creating a service factory: " << it->first << std::endl;
				boost::scoped_ptr<service> current_service(it->second.create(file_service_default_path));
				std::cout << "Service returned: " << current_service->service_call( request, socket)  << std::endl;
		}



		//file_service(request, socket); 
		socket->close();
		std::cout << "connection resolved." << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl; //"The parameter is incorrect" exception
	}
}

void server::user_info(boost::asio::ip::tcp::socket& socket)
{
	boost::asio::ip::tcp::endpoint remote_endpoint = socket.remote_endpoint();
	boost::asio::ip::address addr = remote_endpoint.address();
	std::string addr_string = addr.to_string();
	unsigned short port = remote_endpoint.port();

	std::cout << "User address: " << addr_string << std::endl;
	std::cout << "User port: " << port << std::endl;
}