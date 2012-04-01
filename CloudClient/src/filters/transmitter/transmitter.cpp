#include "transmitter.h"

transmitter::transmitter()
{
	io_service = new boost::asio::io_service();
}

transmitter::~transmitter()
{
	this->disconnect();

	delete io_service;
}

void transmitter::connect(std::string username, std::string url)
{
	// Create a socket for communication.
	socket = new boost::asio::ip::tcp::socket(*io_service);

	// Send the HTTP request and receive the response.
	http_request request;
	request.arguments.insert(std::pair<std::string, std::string>("action", "write"));
	http_response response(request.send(url + '/' + username, *this->socket));

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
