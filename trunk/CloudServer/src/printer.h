#ifndef PRINTER_H
#define PRINTER_H

//STD
#include <iostream>
#include <string>
#include <map>

class printer
{
public:
	printer(){};
	virtual ~printer(){};
	void print_map_contents(std::map <std::string, std::string> data);
	void print_map_contents(std::map <std::string, std::string> data, std::string name);
};

#endif //PRINTER_H
