#ifndef TRANSMITTER_H
#define TRANSMITTER_H

// Boost
#include <boost/asio.hpp>

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
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket;
};

#endif // TRANSMITTER_H
