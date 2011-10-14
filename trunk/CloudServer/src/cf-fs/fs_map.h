#ifndef FS_MAP_H
#define FS_MAP_H

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <deque>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/locks.hpp>
#include <http_utils.h>
#include "fs_file.h"
#include "fs_get_pertinent_part_on_pair.h"


class fs_map
{
private:
	std::map<std::string, boost::shared_ptr<fs_file> > _ds;
	boost::shared_mutex mut_;
public:

	std::set<std::string> compare_and_clean(std::set<std::string> &new_);
	boost::shared_ptr<fs_file> find(std::string key);
	boost::shared_ptr<fs_file> get(std::string key);
	std::set<std::string> list_directory(std::string &path);
	void print();
	std::string put(std::string key, boost::shared_ptr<fs_file>  value);
	void remove(std::string key);
	int size();

};
#endif // FS_MAP_H
