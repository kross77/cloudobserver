#ifndef UTILITIES_H
#define UTILITIES_H 

#include <iostream>
#include <string>
#include <map>

#include <boost/asio.hpp>

// 32-bit time space set up
#ifdef WIN
#include "Windows.h"
#define _USE_32_BIT_TIME_T
#elif defined LIN
#include <unistd.h>
#elif defined MAC
#include <unistd.h> // probably...
#else
#error "unknown platform";
#endif

// Shared library suffixes
#ifdef WIN
std::string current_extention = ".dll";
#elif defined LIN
std::string current_extention = ".so";
#elif defined MAC
std::string current_extention = ".dylib"; // as wall .bundle can be used.
#else
#error "unknown platform";
#endif

// Shared library prefixes
#ifdef WIN
std::string current_prefix = "";
#elif defined LIN
std::string current_prefix = "lib";
#elif defined MAC
std::string current_prefix = "lib"; // as wall .bundle can be used.
#else
#error "unknown platform";
#endif

inline std::string add_prefix_and_suffix(std::string name)
{
	std::string library_name = current_prefix;
	library_name +=	name;
	library_name +=	current_extention;
	return library_name;
}





/*
FILE* f = fopen(request.url.c_str(), "rb");

char* buf = new char[length];
fread(buf, 1, length, f);
response.body = string(buf, length);


delete buf;
fclose(f);
*/

#endif // UTILITIES_H
