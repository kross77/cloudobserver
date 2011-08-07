#ifndef HTTP_UTILITIES_H
#define HTTP_UTILITIES_H

//STD
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <locale>
#include <set>
#include <vector>
#include <iterator>

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>

// Cloud Forever
#include <http.h>

#include "general_utils.h"

class http_utils
{
public:
	/************************************************************************/
	/* Sets grammar (`tag_set_cookie`)
	/************************************************************************/
	http_utils();

	~http_utils(){}

	/************************************************************************/
	/* Encodes string 
	/************************************************************************/ 
	std::string url_encode(std::string data);

	/************************************************************************/
	/* Decodes URL encoded string
	/************************************************************************/ 
	std::string url_decode(std::string data);

	/************************************************************************/
	/* Parses cookie string into map of pairs - `cookie name` : `cookie value`
	/************************************************************************/ 
	std::map<std::string, std::string> parse_cookie(std::string cookie_data);

	/************************************************************************/
	/*  Parses form request body string with enctype: `multipart/form-data` 
	/*  into map of pairs - `Content-Disposition field name` : `field data`  
	/*  Use parse_file_upload_body on each 
	/************************************************************************/ 
	std::map<std::string, std::string> parse_multipart_form_data(std::string form_data);

	/************************************************************************/
	/* Saves cookie as `tag_set_cookie` into http_response headers
	/************************************************************************/
	boost::shared_ptr<http_response> save_cookie(std::string cookie_data, boost::shared_ptr<http_response> response);

	/************************************************************************/
	/* turns map of <std::string, std::string> into string
	/* formated as POST request
	/************************************************************************/
	std::string map_to_post_without_escape(std::map<std::string, std::string> request_map); // you shall provide one with automated escape and one without. Because escape(escape(str)) will produce bad results.

private:
	std::string parse_file_upload_body(std::string contents);
	std::string tag_set_cookie;

	template<typename _OutputIterator>
	inline void split(std::string str, std::string delim, _OutputIterator result);

};
#include "http_utils_inl.h"
#endif HTTP_UTILITIES_H