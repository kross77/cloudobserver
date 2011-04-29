#include <iostream>
#include <string>

using namespace std;

#ifdef WIN
string extention = ".dll";
#elif defined LIN
string extention = ".so";
#elif defined MAC
string extention = ".dylib"; // as wall .bundle can be used.
#else
#error "unknown platform";
#endif

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

