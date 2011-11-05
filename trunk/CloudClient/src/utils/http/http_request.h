#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/optional.hpp>

#include <boost/shared_array.hpp>

#include <boost/bind.hpp>
#include <boost/date_time.hpp>

#include <boost/interprocess/detail/move.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>


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
	bool timed_receive(boost::asio::ip::tcp::socket& socket, int& seconds_to_wait);
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
	typedef enum { METHOD, URL, URL_PARAM, URL_VALUE, VERSION, HEADER_KEY, HEADER_VALUE, BODY, OK } http_request_parser_state;
	void parse_buffer(char* buffer, http_request_parser_state &parser_state, std::string &key, std::string &value, int bytes_read);
	bool timed_receive_base(boost::asio::ip::tcp::socket& socket, size_t& buffer_size, int& seconds_to_wait);
	int read_some( boost::asio::ip::tcp::socket *sock, char* buffer, size_t& buffer_size );
};

#endif // HTTP_REQUEST_H
