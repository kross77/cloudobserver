#ifndef PLUGIN_H
#define PLUGIN_H

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

namespace deleter_namespace
{
	template<class T>
	void delete_ptr(T * ptr)
	{
		std::cout << "Deallocator function." << std::endl;
		delete ptr;
	};
}


class deleter
{
	public:

	void delete_ptr(void * ptr)
	{
		std::cout << "Deallocator function." << std::endl;
		delete ptr;
	};


	void delete_array(void * ptr)
	{
		delete [] ptr;
	};
};

class plugin: public deleter
{
public:
	virtual void simple_call() =0;
	virtual void pass_and_modify_data(std::string ** a) =0;
	virtual boost::shared_ptr<std::string> pass_and_modify_data( boost::shared_ptr<std::string>  a) =0;
};

#endif // PLUGIN_H