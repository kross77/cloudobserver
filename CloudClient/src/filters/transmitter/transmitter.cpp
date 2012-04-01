#include "transmitter.h"

transmitter::transmitter() : socket(io_service)
{
}

transmitter::~transmitter()
{
	this->disconnect();
}

void transmitter::connect(std::string username, std::string url)
{
	// Send the HTTP request and receive the response.
	http_request request;
	request.arguments.insert(std::pair<std::string, std::string>("action", "write"));
	http_response response(request.send(url + '/' + username, this->socket));

	// Check for the response status.
	if (response.status != 200)
	{
		this->disconnect();
		throw invalid_username_exception();
	}
}

void transmitter::disconnect()
{
	if (socket.is_open())
	{
		try
		{
			socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			socket.close();
		}
		catch (boost::system::system_error&) { }
	}
}

void transmitter::send(const char* data, int size)
{
	if (!socket.is_open())
		throw server_connection_exception();
	
	boost::asio::write(socket, boost::asio::buffer(data, size));
}
