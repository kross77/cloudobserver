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
	selector(std::string greeting = "", bool autoselection = true);
	~selector();
	void add_option(std::string description, void* identifier);
	void* get_selection();
	void reset();
	void select();
	void set_autoselection(bool autoselection);
	void set_greeting(std::string greeting);

	class internal_exception: public std::exception { };
private:
	bool autoselection;
	std::string greeting;
	std::map<std::string, void*> options;
	bool selected;
	void* selection;
};

#endif // SELECTOR_H
