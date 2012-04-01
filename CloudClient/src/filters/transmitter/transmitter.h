#ifndef TRANSMITTER_H
#define TRANSMITTER_H

// The default port number.
#define DEFAULT_PORT "4773"

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/regex.hpp>

#include "../../utils/http/http.h"

class transmitter
{
public:
	transmitter();
	~transmitter();
	void connect(std::string username, std::string url);
	void disconnect();
	void send(const char* data, int size);

	class invalid_username_exception: public std::exception { };
	class server_connection_exception: public std::exception { };
private:
	boost::asio::io_service* io_service;
	boost::asio::ip::tcp::resolver* resolver;
	boost::asio::ip::tcp::socket* socket;
};

#endif // TRANSMITTER_H
