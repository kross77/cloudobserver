#include "transmitter.h"

transmitter::transmitter()
{
	io_service = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*io_service);
	resolver = new boost::asio::ip::tcp::resolver(*io_service);
}

transmitter::~transmitter()
{
	delete io_service;

	socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	socket->close();
	delete socket;

	delete resolver;
}

void transmitter::connect(std::string url)
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
		// The protocol is not supported. Report a failure.
		throw std::exception((protocol + " protocol is not valid. Use one of the following protocols: " + SUPPORTED_PROTOCOLS + ".").c_str());

	// Resolve the hostname.
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), host, port);
	boost::asio::ip::tcp::resolver::iterator iterator;
	try
	{
		iterator = resolver->resolve(query);
	}
	catch (std::exception)
	{
		// Failed to resolve the hostname. Report a failure.
		throw std::exception("Cannot resolve the hostname.");
	}
	
	// Try to connect to the server using one of the endpoints.
	for (iterator; iterator != boost::asio::ip::tcp::resolver::iterator(); ++iterator)
	{
		boost::asio::ip::tcp::endpoint endpoint = *iterator;
		std::cout << "Trying to connect to the server at " << endpoint.address().to_string() << ":" << port << "...";
		try
		{
			socket->connect(endpoint);

			// Connection succeeded. Report a success.
			std::cout << " OK." << std::endl;
			return;
		}
		catch (std::exception)
		{
			// Failed to connect to the endpoint. Try the next one if any.
			std::cout << " failed." << std::endl;
		}
	}

	// Unable to connect to all the endpoints. Report a failure.
	throw std::exception("Unable to connect to all the endpoints.");
}

void transmitter::reset()
{
	socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	socket->close();
	delete socket;

	socket = new boost::asio::ip::tcp::socket(*io_service);
}

void transmitter::send(const char* data, int size)
{
	boost::asio::write(*socket, boost::asio::buffer(data, size));
}

void transmitter::set_username(std::string username)
{
	std::string http_header = "GET /" + username + "?action=write HTTP/1.1\r\n\r\n";
	this->send(http_header.c_str(), http_header.length());

	http_response_parser parser;
	http_response response = parser.parse(*socket);

	if (response.status != 200)
		throw std::exception(("HTTP response: " + response.description).c_str());
}
