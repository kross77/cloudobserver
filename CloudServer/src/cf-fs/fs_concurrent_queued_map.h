#ifndef FS_CONCURRENT_QUEUED_MAP_H
#define FS_CONCURRENT_QUEUED_MAP_H

#include <map>
#include <set>
#include <deque>
#include <boost/cstdint.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

#include "fs_file.h"

class fs_concurrent_queued_map
{
private:
	std::map<std::string, boost::shared_ptr<fs_file> > _ds;
	std::deque<std::string> _queue;
	mutable boost::mutex mut_;
public:

	boost::shared_ptr<fs_file>  find(std::string key);
	boost::shared_ptr<fs_file>  get(std::string key);
	boost::shared_ptr<fs_file>  get_last(std::string key);
	std::string put(std::string key, boost::shared_ptr<fs_file>  value);
	void remove(std::string key);
	boost::uintmax_t remove_last();
	boost::uintmax_t remove_set(std::set<std::string> r);
	int size();

};

#endif // FS_CONCURRENT_QUEUED_MAP_H
