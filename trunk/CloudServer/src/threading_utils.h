#ifndef THREADING_UTILITIES_H
#define THREADING_UTILITIES_H 
//STD
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

class threading_utils
{
public:
	template <class variable_T, class group_T>
	void safe_insert(variable_T variable, group_T &into)
	{
		boost::mutex::scoped_lock lock(mut);
		into.insert(variable);
	}

	template <class variable_T, class group_T>
	void safe_erase(variable_T variable, group_T &into)
	{
		boost::mutex::scoped_lock lock(mut);
		into.erase(into.find(variable));
	}

private:
		mutable boost::mutex mut;
};
#endif //THREADING_UTILITIES_H 
