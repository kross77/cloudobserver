#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include <exception>
#include <map>
#include <string>
#include <vector>

class http_request
{
public:
	http_request();
	http_request(boost::asio::ip::tcp::socket& socket);
	~http_request();
	void clear();
	void reset();
	void receive(boost::asio::ip::tcp::socket& socket);
	void send(boost::asio::ip::tcp::socket& socket);
	boost::asio::ip::tcp::socket& send(std::string absolute_url, boost::asio::ip::tcp::socket& socket);

	std::string method;
	std::string url;
	std::string version;
	std::map<std::string, std::string> arguments;
	std::map<std::string, std::string> headers;
	int body_size;
	std::string body;

	class connection_exception: public std::exception { };
	class policy_file_request_exception: public std::exception { };
private:
	enum http_request_parser_state { METHOD, URL, URL_PARAM, URL_VALUE, VERSION, HEADER_KEY, HEADER_VALUE, BODY, OK };
};

#endif // HTTP_REQUEST_H
