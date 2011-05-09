#include <iostream>
#include <string>
#include <map>

#include <boost/asio.hpp>

using namespace boost::asio::ip;
using namespace std;

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
string extention = ".dll";
#elif defined LIN
string extention = ".so";
#elif defined MAC
string extention = ".dylib"; // as wall .bundle can be used.
#else
#error "unknown platform";
#endif

// Shared library prefixes
#ifdef WIN
string prefix = "";
#elif defined LIN
string prefix = "lib";
#elif defined MAC
string prefix = "lib"; // as wall .bundle can be used.
#else
#error "unknown platform";
#endif

string add_prefix_and_suffix(string name)
{
	string library_name = prefix;
	library_name +=	name;
	library_name +=	extention;
	return library_name;
}

void print_user_info(boost::asio::ip::tcp::socket& socket)
{
	tcp::endpoint remote_endpoint = socket.remote_endpoint();
	address addr = remote_endpoint.address();
	string addr_string = addr.to_string();
	unsigned short port = remote_endpoint.port();

	cout << "User address: " << addr_string << endl;
	cout << "User port: " << port << endl;
}

void print_map_contents(map <string, string> data)
{
	map<string, string>::const_iterator end = data.end();
	if(data.end() != data.begin())
	{
		cout << "Received request contained:\n";
		for (map<string, string>::const_iterator it = data.begin(); it != end; ++it)
		{
			cout << it->first << " : " << it->second << '\n';
		}
	}
}

void print_map_contents(map <string, string> data, string name)
{
	map<string, string>::const_iterator end = data.end();
	if(data.end() != data.begin())
	{
		cout << "Received request contained next "<< name << ":\n";
		for (map<string, string>::const_iterator it = data.begin(); it != end; ++it)
		{
			cout << it->first << " : " << it->second << '\n';
		}
	}
}

/*
FILE* f = fopen(request.url.c_str(), "rb");

char* buf = new char[length];
fread(buf, 1, length, f);
response.body = string(buf, length);


delete buf;
fclose(f);
*/

