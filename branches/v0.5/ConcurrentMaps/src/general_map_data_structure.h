#ifndef GENERAL_MAP_DATA_STRUCTURE_H
#define GENERAL_MAP_DATA_STRUCTURE_H

#include <map>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

#include "test_data_structure.h"

class general_map_data_structure: public test_data_structure
{
private:

	std::map<int,int> _ds;
	mutable boost::mutex mut_;
public:
	general_map_data_structure() {}

	bool containsKey(int key) 
	{
        boost::mutex::scoped_lock lock(mut_);
        return _ds.find(key) != _ds.end();
    }

	int get(int key) {
		boost::mutex::scoped_lock lock(mut_);
		return _ds[key];
	}

	int put(int key, int value) {
		boost::mutex::scoped_lock lock(mut_);
		_ds.insert(std::pair<int, int>(key,value));
		return key;
	}

	int remove(int key) {
		boost::mutex::scoped_lock lock(mut_);
		return _ds.erase(key);
	}

	int size() {
		boost::mutex::scoped_lock lock(mut_);
		return _ds.size();
	}
	const char* name() {
		return "StdMap";
	}
	void print() {}
	void shutdown() {}

};

#endif // GENERAL_MAP_DATA_STRUCTURE_H