#include "fs_concurrent_queued_map.h"

boost::uintmax_t fs_concurrent_queued_map::remove_set( std::set<std::string> r )
{
	boost::mutex::scoped_lock lock(mut_);
	boost::uintmax_t totall_removed = 0;
	for (std::set<std::string>::iterator i = r.begin(); i != r.end(); ++i) {
		try{
			std::map<std::string, boost::shared_ptr<fs_file> >::iterator it = _ds.find(*i);
			if (it != _ds.end())
				totall_removed += it->second->size;

			_ds.erase(*i);
			_queue.erase(std::remove(_queue.begin(), _queue.end(), *i), _queue.end());
		}
		catch(std::exception){}
	}
	return totall_removed;
}

boost::shared_ptr<fs_file> fs_concurrent_queued_map::get( std::string key )
{
	boost::mutex::scoped_lock lock(mut_);
	return _ds[key];
}

boost::shared_ptr<fs_file> fs_concurrent_queued_map::find( std::string key )
{
	boost::mutex::scoped_lock lock(mut_);
	//	std::for_each(_ds.begin(), _ds.end(), [](std::pair<std::string, boost::shared_ptr<fs_file> > s){std::cout << s.first << std::endl;});
	std::map<std::string, boost::shared_ptr<fs_file> >::iterator a = _ds.find(key);
	if (a != _ds.end())
	{
		return a->second;
	}
	throw std::runtime_error("not found");
}

std::string fs_concurrent_queued_map::put( std::string key, boost::shared_ptr<fs_file> value )
{
	boost::mutex::scoped_lock lock(mut_);
	_ds.insert(std::pair<std::string, boost::shared_ptr<fs_file> >(key,value));
	_queue.push_back(key);
	return key;
}

boost::shared_ptr<fs_file> fs_concurrent_queued_map::get_last( std::string key )
{
	boost::mutex::scoped_lock lock(mut_);
	const std::string k = _queue.front();
	return _ds[k];
}

boost::uintmax_t fs_concurrent_queued_map::remove_last()
{
	boost::uintmax_t size;
	boost::mutex::scoped_lock lock(mut_);
	const std::string k = _queue.front();
	size =_ds[k]->size;
	_ds.erase(k);
	_queue.pop_front();
	return size;
}

void fs_concurrent_queued_map::remove( std::string key )
{
	boost::mutex::scoped_lock lock(mut_);
	_queue.erase(std::remove(_queue.begin(), _queue.end(), key), _queue.end());
	_ds.erase(key);
}

int fs_concurrent_queued_map::size()
{
	boost::mutex::scoped_lock lock(mut_);
	return _ds.size();
}