#ifndef FS_CONCURRENT_QUEUED_MAP_H
#define FS_CONCURRENT_QUEUED_MAP_H

#include <map>
#include <set>
#include <deque>
#include <boost/cstdint.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

template <class map_t_1, class map_t_2>
class concurrent_queued_map
{
private:
	std::map<map_t_1, map_t_2> _ds;
	std::deque<map_t_1> _queue;
	mutable boost::mutex mut_;
public:

	boost::uintmax_t remove_set(std::set<map_t_1> r)
	{
		boost::mutex::scoped_lock lock(mut_);
		boost::uintmax_t totall_removed = 0;
		for (std::set<std::string>::iterator i = r.begin(); i != r.end(); ++i) {
			try{
				std::map<map_t_1, map_t_2>::iterator it = _ds.find(*i);
				if (it != _ds.end())
					totall_removed += it->second->size;

				_ds.erase(*i);
				_queue.erase(std::remove(_queue.begin(), _queue.end(), *i), _queue.end());
			}
			catch(std::exception){}
		}
		return totall_removed;
	}

	map_t_2 get(map_t_1 key) {
		boost::mutex::scoped_lock lock(mut_);
		return _ds[key];
	}

	map_t_2 find(map_t_1 key)
	{
		boost::mutex::scoped_lock lock(mut_);
		//	std::for_each(_ds.begin(), _ds.end(), [](std::pair<std::string, boost::shared_ptr<fs_file> > s){std::cout << s.first << std::endl;});
		std::map<map_t_1, map_t_2>::iterator a = _ds.find(key);
		if (a != _ds.end())
		{
			return a->second;
		}
		throw std::runtime_error("not found");
	}

	map_t_1 put(map_t_1 key, map_t_2 value) {
		boost::mutex::scoped_lock lock(mut_);
		_ds.insert(std::pair<map_t_1, map_t_2>(key,value));
		_queue.push_back(key);
		return key;
	}

	map_t_2 get_last(map_t_1 key) {
		boost::mutex::scoped_lock lock(mut_);
		const map_t_1 k = _queue.front();
		return _ds[k];
	}

	boost::uintmax_t remove_last() {
		boost::uintmax_t size;
		boost::mutex::scoped_lock lock(mut_);
		const map_t_1 k = _queue.front();
		size =_ds[k]->size;
		_ds.erase(k);
		_queue.pop_front();
		return size;
	}

	void remove(map_t_1 key) {
		boost::mutex::scoped_lock lock(mut_);
		_queue.erase(std::remove(_queue.begin(), _queue.end(), key), _queue.end());
		_ds.erase(key);
	}

	int size() {
		boost::mutex::scoped_lock lock(mut_);
		return _ds.size();
	}

};

#endif // FS_CONCURRENT_QUEUED_MAP_H
