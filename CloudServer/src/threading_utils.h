#ifndef THREADING_UTILITIES_H
#define THREADING_UTILITIES_H 
//STD
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <boost/thread.hpp>

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

	template <class first_variable_T,class second_variable_T>
	second_variable_T safe_search_in_map(first_variable_T variable, std::map<first_variable_T, second_variable_T> &into)
	{
		boost::mutex::scoped_lock lock(mut);
		std::map<first_variable_T, second_variable_T>::iterator return_val = into.find(variable);
		if (return_val != into.end())
		{
			return return_val->second;
		}
		else
		{
			throw std::runtime_error("Not found.");
		}
	}

private:
	mutable boost::mutex mut;
};
#endif //THREADING_UTILITIES_H 
