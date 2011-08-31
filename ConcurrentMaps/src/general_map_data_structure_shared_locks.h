#ifndef GENERAL_MAP_DATA_STRUCTURE_SHARED_LOCKS
#define GENERAL_MAP_DATA_STRUCTURE_SHARED_LOCKS

#include <map>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

#include "test_data_structure.h"

class general_map_data_structure_shared_locks: public test_data_structure
{
private:

	std::map<int,int> _ds;
	boost::shared_mutex mut_;
public:
	general_map_data_structure_shared_locks() {}

	bool containsKey(int key) 
	{
        boost::shared_lock<boost::shared_mutex> lock_r(mut_);
        return _ds.find(key) != _ds.end();
    }

	int get(int key) {
		boost::shared_lock<boost::shared_mutex> lock_r(mut_);
		return _ds[key];
	}

	int put(int key, int value) {
		boost::upgrade_lock<boost::shared_mutex> lock(mut_);
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
		_ds.insert(std::pair<int, int>(key,value));
		return key;
	}

	int remove(int key) {
		boost::upgrade_lock<boost::shared_mutex> lock(mut_);
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
		return _ds.erase(key);
	}

	int size() {
		boost::shared_lock<boost::shared_mutex> lock_r(mut_);
		return _ds.size();
	}
	const char* name() {
		return "StdMap with shared locks";
	}
	void print() {}
	void shutdown() {}

};

#endif // GENERAL_MAP_DATA_STRUCTURE_SHARED_LOCKS