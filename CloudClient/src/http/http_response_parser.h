#ifndef HTTP_RESPONSE_PARSER_H
#define HTTP_RESPONSE_PARSER_H

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include "http_response.h"
#include "http_response_parser_state.h"

class http_response_parser
{
public:
	http_response parse(boost::asio::ip::tcp::socket& s);
};

#endif // HTTP_RESPONSE_PARSER_H
