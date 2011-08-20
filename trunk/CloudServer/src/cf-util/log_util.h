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
#include <boost/thread.hpp>

class flush_internal;

class log_util
{
public:

	static flush_internal *endl;

	log_util( int buffer_length, bool do_print=true);
	log_util( int buffer_length, bool do_print, bool do_save, boost::filesystem::path save_file_path);

	~log_util();
	
	template <class T>
	log_util &operator<<(const T &v)
	{
		boost::shared_ptr<std::ostringstream> this_stream = find_stream(boost::this_thread::get_id());
		*this_stream << v;
		return *this;
	}

	log_util &operator<<(std::ostream&(*f)(std::ostream&)) 
	{
		boost::shared_ptr<std::ostringstream> this_stream = find_stream(boost::this_thread::get_id());
		*this_stream << *f;
		return *this;
	}

	log_util &operator<<(flush_internal*)
	{
		boost::shared_ptr<std::ostringstream> this_stream = find_stream(boost::this_thread::get_id());
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
		{
			boost::mutex::scoped_lock lock(mut);
			messages_buffer[i] = this_message;
			i++;
			if(print)
			{
				std::cout << this_message;
			}
			is_filled();
		};
		
		{
			boost::mutex::scoped_lock lock(mut_threads_pool);
			threads_pool.erase(boost::this_thread::get_id());
		};

		return *this;
	}

	void use_time();

	void use_prefix(std::string pref);

	std::string *messages_buffer;
	bool print;
	bool save;
	boost::filesystem::path file_path;
private:
	int i;
	int log_length;
	bool add_time;
	bool add_prefix;
	std::string prefix;
	
	mutable boost::mutex mut;
	mutable boost::mutex mut_threads_pool;

	// current_message;
	std::map<boost::thread::id, boost::shared_ptr<std::ostringstream> > threads_pool;

	void is_filled();

	boost::shared_ptr<std::ostringstream> find_stream(boost::thread::id thread_id);

	void clean_ostringstream(std::ostringstream &message);
	void add_string_into_file( std::string contents, boost::filesystem::path file_path );
};

#endif // LOG_UTIL
