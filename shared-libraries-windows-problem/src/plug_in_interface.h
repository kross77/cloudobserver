#ifndef PLUGIN_H
#define PLUGIN_H
#include <string>
class deleter
{
	public:
	void delete_ptr(void * ptr)
	{
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
};

#endif // PLUGIN_H