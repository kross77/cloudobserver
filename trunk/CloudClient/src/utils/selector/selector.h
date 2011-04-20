#ifndef SELECTOR_H
#define SELECTOR_H

// Boost
#include <boost/lexical_cast.hpp>

#include <exception>
#include <iostream>
#include <map>
#include <string>

class selector
{
public:
	selector(std::string greeting);
	~selector();
	void add_option(std::string description, void* identifier);
	void* get_selection();
	void select();

	class internal_exception: public std::exception { };
private:
	std::string greeting;
	std::map<std::string, void*> options;
	void* selection;
	bool selected;
};

#endif // SELECTOR_H
