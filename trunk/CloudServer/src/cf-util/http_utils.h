#ifndef HTTP_UTILITIES_H
#define HTTP_UTILITIES_H

//STD
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <locale>

// Boost
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

// Cloud Forever
#include <http.h>

class http_utils
{
public:
	http_utils();
	~http_utils(){}

	std::map<std::string, std::string> parse_cookie(std::string cookie_data);
	boost::shared_ptr<http_response> save_cookie(std::string cookie_data, boost::shared_ptr<http_response> response);
	std::string map_to_post_without_escape(std::map<std::string, std::string> request_map); // you shall provide one with automated escape and one without. Because escape(escape(str)) will produce bad results.

private:
	std::string tag_set_cookie;

};
#endif HTTP_UTILITIES_H