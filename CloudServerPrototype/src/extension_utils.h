#ifndef UTILITIES_H
#define UTILITIES_H 

#include <string>



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

class extension_utils
{
public:
	extension_utils();
	virtual ~extension_utils(){}
	std::string add_prefix_and_suffix(std::string name);
private:
	
	std::string current_prefix;
	std::string current_extention;
};

#endif // UTILITIES_H