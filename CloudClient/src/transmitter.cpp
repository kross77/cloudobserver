#include "transmitter.h"

transmitter::transmitter()
{
	io_service = new boost::asio::io_service();
	resolver = new boost::asio::ip::tcp::resolver(*io_service);
}

transmitter::~transmitter()
{
	this->disconnect();

	delete resolver;
	delete io_service;
}

void transmitter::connect(std::string username, std::string url)
{
	// Parse the URL.
	std::vector<std::string> url_parts;
	boost::regex url_expression(
		// protocol            host               port
		"^(\?:([^:/\?#]+)://)\?(\\w+[^/\?#:]*)(\?::(\\d+))\?"
		// path                file       parameters
		"(/\?(\?:[^\?#/]*/)*)\?([^\?#]*)\?(\\\?(.*))\?"
		);
	boost::regex_split(std::back_inserter(url_parts), url, url_expression);
	std::string protocol = url_parts[0];
	std::string host = url_parts[1];
	std::string port = url_parts[2];

	// Use the default protocol if no protocol is specified.
	if (protocol.empty())
		protocol = DEFAULT_PROTOCOL;

	// Use the default port if no port is specified.
	if (port.empty())
		port = DEFAULT_PORT;

	// Get the list of all supported protocols.
	std::vector<std::string> protocols;
	boost::split(protocols, SUPPORTED_PROTOCOLS, boost::is_any_of(", "));

	// Check if the given protocol is supported.
	boost::to_upper(protocol);
	if (std::find(protocols.begin(), protocols.end(), protocol) == protocols.end())
	{
		// The protocol is not supported. Report a failure.
		std::cout << protocol << " protocol is not valid. Use one of the following protocols: " << SUPPORTED_PROTOCOLS << "." << std::endl;
		throw transmitter::server_connection_exception();
	}

	// Resolve the hostname.
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), host, port);
	boost::asio::ip::tcp::resolver::iterator iterator;
	std::cout << "Resolving the hostname...";
	try
	{
		iterator = resolver->resolve(query);
		std::cout << " OK." << std::endl;
	}
	catch (boost::system::system_error&)
	{
		// Failed to resolve the hostname. Report a failure.
		std::cout << " failed." << std::endl;
		throw server_connection_exception();
	}

	// Count the number of endpoints.
	int number_of_endpoints = 0;
	boost::asio::ip::tcp::resolver::iterator counter = iterator;
	for (counter; counter != boost::asio::ip::tcp::resolver::iterator(); ++counter)
		number_of_endpoints++;
	std::cout << "Endpoints found: " << number_of_endpoints << std::endl;
	
	// Create a socket for communication.
	socket = new boost::asio::ip::tcp::socket(*io_service);

	// Try to connect to the server using one of the endpoints.
	bool connected = false;
	for (iterator; iterator != boost::asio::ip::tcp::resolver::iterator(); ++iterator)
	{
		boost::asio::ip::tcp::endpoint endpoint = iterator->endpoint();
		std::cout << "Trying to connect to the server at " << endpoint.address().to_string() << ":" << port << "...";
		try
		{
			socket->connect(endpoint);
			connected = true;

			// Connection succeeded. Report a success.
			std::cout << " OK." << std::endl;
		}
		catch (boost::system::system_error&)
		{
			// Failed to connect to the endpoint. Try the next one if any.
			std::cout << " failed." << std::endl;
		}
	}

	// Check if the connection is successful.
	if (!connected)
	{
		// Unable to connect to all the endpoints. Report a failure.
		std::cout << "Unable to connect to all the endpoints." << std::endl;
		this->disconnect();
		throw server_connection_exception();
	}

	// Send an HTTP header.
	std::string http_header = "GET /" + username + "?action=write HTTP/1.1\r\n\r\n";
	this->send(http_header.c_str(), http_header.length());

	// Parse the HTTP response.
	http_response_parser parser;
	http_response response = parser.parse(*socket);
	std::cout << "Server responded: " << response.status << " " << response.description << "." << std::endl;

	// Check for the response status.
	if (response.status != 200)
	{
		this->disconnect();
		throw invalid_username_exception();
	}
}

void transmitter::disconnect()
{
	if (socket)
	{
		try
		{
			socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			socket->close();
		}
		catch (boost::system::system_error&) { }
		delete socket;
		socket = NULL;
	}
}

void transmitter::send(const char* data, int size)
{
	if (!socket)
		throw server_connection_exception();
	
	boost::asio::write(*socket, boost::asio::buffer(data, size));
}
