#ifndef FILE_S_H
#define FILE_S_H

#include <boost/filesystem.hpp>
#include <boost/thread/locks.hpp>
#include <boost/shared_array.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/cstdint.hpp>

struct fs_file
{
	boost::shared_mutex mutex_;
	boost::filesystem::path path;
	std::string type_extension;
	std::string mime_type;
	boost::uintmax_t size;
	bool is_cachable;
	bool is_cached;
	boost::shared_ptr<std::string> buffer;
	std::string modified;
};

#endif //FILE_S_H
