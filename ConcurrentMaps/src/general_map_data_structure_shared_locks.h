#ifndef GENERAL_MAP_DATA_STRUCTURE_SHARED_LOCKS
#define GENERAL_MAP_DATA_STRUCTURE_SHARED_LOCKS

#include <map>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

#include "test_data_structure.h"

template <class map_t_1, class map_t_2>
class general_map_data_structure_shared_locks : public test_data_structure<map_t_1, map_t_2>
{
private:

	std::map<map_t_1, map_t_2> _ds;
	boost::shared_mutex mut_;
public:
	general_map_data_structure_shared_locks() {}

	bool containsKey(map_t_1 key)
	{
        boost::shared_lock<boost::shared_mutex> lock_r(mut_);
        return _ds.find(key) != _ds.end();
    }

	map_t_2 get(map_t_1 key) {
		boost::shared_lock<boost::shared_mutex> lock_r(mut_);
		return _ds[key];
	}

	map_t_1 put(map_t_1 key, map_t_2 value) {
		boost::upgrade_lock<boost::shared_mutex> lock(mut_);
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
		_ds.insert(std::pair<map_t_1, map_t_2>(key,value));
		return key;
	}

	int remove(map_t_1 key) {
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