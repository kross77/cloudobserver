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
	std::string host = url_parts[1];
	std::string port = url_parts[2];

	// Use the default port if no port is specified.
	if (port.empty())
		port = "4773";

	// Resolve the hostname.
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), host, port);
	boost::asio::ip::tcp::resolver::iterator iterator;
	try
	{
		iterator = resolver->resolve(query);
	}
	catch (boost::system::system_error&)
	{
		throw server_connection_exception();
	}
	
	// Create a socket for communication.
	socket = new boost::asio::ip::tcp::socket(*io_service);

	// Try to connect to the server using one of the endpoints.
	bool connected = false;
	for (iterator; iterator != boost::asio::ip::tcp::resolver::iterator(); ++iterator)
	{
		boost::asio::ip::tcp::endpoint endpoint = iterator->endpoint();
		try
		{
			socket->connect(endpoint);
			connected = true;
		}
		catch (boost::system::system_error&)
		{
		}
	}

	// Check if the connection is successful.
	if (!connected)
		throw server_connection_exception();

	// Send the HTTP request.
	http_request request;
	request.url = '/' + username;
	request.arguments.insert(std::pair<std::string, std::string>("action", "write"));
	request.send(*this->socket);

	// Receive the HTTP response.
	http_response response(*socket);

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
