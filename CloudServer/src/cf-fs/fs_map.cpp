#include "fs_map.h"

std::set<std::string> fs_map::list_directory( std::string &path )
{
	std::set<std::string> output;

	{
		boost::shared_lock<boost::shared_mutex> lock_r(mut_);

		std::transform(_ds.begin(),
			_ds.end(),
			std::inserter(output, output.end()),
			fs_get_pertinent_part_on_pair(path));

	}

	output.erase("");

	if (output.size() == 0)
	{
		throw std::runtime_error("directory not found");
	}

	return output;
}

std::set<std::string> fs_map::compare_and_clean( std::set<std::string> &new_ )
{
	std::set<std::string> result;
	std::set<std::string> old;

	boost::upgrade_lock<boost::shared_mutex> lock(mut_);
	boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);


	for (std::map<std::string, boost::shared_ptr<fs_file> >::iterator mi = _ds.begin(); mi != _ds.end(); ++mi)
		old.insert(mi->first);

	std::set_difference( old.begin(), old.end(), new_.begin(), new_.end(), inserter(result, result.begin()));

	for (std::set<std::string>::iterator i = result.begin(); i != result.end(); ++i) {
		_ds.erase(*i);
	}
	return result;
}

boost::shared_ptr<fs_file> fs_map::get( std::string key )
{
	boost::shared_lock<boost::shared_mutex> lock_r(mut_);
	return _ds[key];
}

boost::shared_ptr<fs_file> fs_map::find( std::string key )
{
	boost::shared_lock<boost::shared_mutex> lock_r(mut_);
	std::map<std::string, boost::shared_ptr<fs_file> >::iterator a = _ds.find(key);
	if (a != _ds.end())
	{
		return a->second;
	}
	throw std::runtime_error("not found");
}

std::string fs_map::put( std::string key, boost::shared_ptr<fs_file> value )
{
	boost::upgrade_lock<boost::shared_mutex> lock(mut_);
	boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
	_ds.insert(std::pair<std::string, boost::shared_ptr<fs_file> >(key,value));
	return key;
}

void fs_map::remove( std::string key )
{
	boost::upgrade_lock<boost::shared_mutex> lock(mut_);
	boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
	_ds.erase(key);
}

int fs_map::size()
{
	boost::shared_lock<boost::shared_mutex> lock_r(mut_);
	return _ds.size();
}

void fs_map::print()
{
	boost::shared_lock<boost::shared_mutex> lock_r(mut_);
	http_utils h;
	for (std::map<std::string, boost::shared_ptr<fs_file> >::iterator i = _ds.begin(); i != _ds.end(); ++i) 
	{
		boost::filesystem::path pa = h.utf8_to_utf16(h.url_decode(i->first));
		std::cout << pa.string() << std::endl;
	}
}