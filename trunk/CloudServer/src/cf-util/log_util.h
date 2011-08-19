#ifndef LOG_UTIL
#define LOG_UTIL 

#include <iostream>
#include <sstream>
#include <map>
#include <boost/circular_buffer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "threading_utils.h"

class FlushInternal;

class log_util
{
public:

	static FlushInternal *endl;

	log_util( int buffer_length, bool do_print=true);
	log_util( int buffer_length, bool do_print, bool do_save, boost::filesystem::path save_file_path);

	~log_util();
	
	template <class T>
	log_util &operator<<(const T &v)
	{
		boost::shared_ptr<std::stringstream> this_stream = find_stream(boost::this_thread::get_id());
		*this_stream << v;
		return *this;
	}

	log_util &operator<<(std::ostream&(*f)(std::ostream&)) 
	{
		boost::shared_ptr<std::stringstream> this_stream = find_stream(boost::this_thread::get_id());
		*this_stream << *f;
		return *this;
	}

	log_util &operator<<(FlushInternal*)
	{
		boost::shared_ptr<std::stringstream> this_stream = find_stream(boost::this_thread::get_id());
		std::string this_message = "";
		if (add_prefix)
		{
			this_message += this->prefix;
		}
		if (add_time)
		{
			std::ostringstream formatter;
			formatter.imbue(std::locale(std::cout.getloc(), new boost::posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT:")));
			formatter <<  boost::posix_time::second_clock::local_time();	
			this_message +=formatter.str();
		}
		this_message += this_stream->str();
		this_message += "\n";
		boost::mutex::scoped_lock lock(mut);
		++i;
		messages_buffer->push_back(this_message);
		if(print)
		{
			std::cout << this_message;
		}
		is_filled();
		lock.unlock();
		clean_stringstream(*this_stream);
		return *this;
	}

	void use_time();

	void use_prefix(std::string pref);

	boost::circular_buffer<std::string> *messages_buffer;

private:
	int i;
	int log_length;
	bool print;
	bool save;
	bool add_time;
	bool add_prefix;
	std::string prefix;
	boost::filesystem::path file_path;
	mutable boost::mutex mut;
	threading_utils *thread_util;

	// current_message;
	std::map<boost::thread::id, boost::shared_ptr<std::stringstream> > threads_pool;

	void is_filled();

	boost::shared_ptr<std::stringstream> find_stream(boost::thread::id thread_id);

	void clean_stringstream(std::stringstream &message);
	void add_string_into_file( std::string contents, boost::filesystem::path file_path );
};

#endif // LOG_UTIL
