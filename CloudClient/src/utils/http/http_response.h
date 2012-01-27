#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

// Boost
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/string.hpp>

#include <map>
#include <string>

class http_response
{
public:
	http_response();
	http_response(boost::asio::ip::tcp::socket& socket);
	~http_response();
	void clear();
	void reset();
	void receive(boost::asio::ip::tcp::socket& socket);
	void send(boost::asio::ip::tcp::socket& socket);
	
	std::string version;
	int status;
	std::string description;
	std::map<std::string, std::string> headers;
	int body_size;
	std::string body;

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version_)
	{
		ar & body;
		ar & body_size;
		ar & headers;
		ar & version;
		ar & status;
		ar & description;
	}

	enum http_response_parser_state { VERSION, STATUS, DESCRIPTION, HEADER_KEY, HEADER_VALUE, BODY, OK };
};

#endif // HTTP_RESPONSE_H
