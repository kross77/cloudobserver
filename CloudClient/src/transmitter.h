#ifndef TRANSMITTER_H
#define TRANSMITTER_H

// The default network protocol.
#define DEFAULT_PROTOCOL "HTTP"

// The list of all supported network protocols.
// Use ', ' (a comma followed by a space) as a delimiter.
#define SUPPORTED_PROTOCOLS "HTTP"

// The default port number.
#define DEFAULT_PORT "4773"

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/regex.hpp>

#include "http/http.h"

class transmitter
{
public:
	transmitter();
	~transmitter();
	void connect(std::string url);
	void reset();
	void send(const char* data, int size);
	void set_username(std::string username);
private:
	boost::asio::io_service* io_service;
	boost::asio::ip::tcp::socket* socket;
	boost::asio::ip::tcp::resolver* resolver;
};

#endif // TRANSMITTER_H
