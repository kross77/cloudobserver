#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
#include <map>

struct http_response
{
	std::string version;
	int status;
	std::string description;
	std::map<std::string, std::string> headers;
	int body_size;
	std::string body;
};

#endif // HTTP_RESPONSE_H
