#ifndef LOG_UTIL
#define LOG_UTIL 

#include <iostream>
#include <sstream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

class flush_internal;
/*!
 *  \addtogroup Utilities
 *  @{
 */
class log_util
{
public:
	class log_message
	{
		friend class log_util;
	public:
		explicit log_message(log_util &parent) : parent(parent) { }

		template <class T> log_message &operator<<(const T &v)
		{
			data << v;
			return *this;
		}

		log_message &operator<<(std::ostream&(*f)(std::ostream&))
		{
			data << *f;
			return *this;
		}

		void operator<<(flush_internal*)
		{
			parent.write(this);
			delete this; // commit suicide =(
		}
	private:
		log_util &parent;
		std::ostringstream data;
	};

	static flush_internal *endl;

	log_util( int buffer_length, bool do_print=true);
	log_util( int buffer_length, bool do_print, bool do_save, boost::filesystem::path save_file_path);
	log_util( int buffer_length, bool do_print, bool do_save, bool do_print_time, boost::filesystem::path save_file_path);

	~log_util();
	
	template <class T>
	log_message &operator<<(const T &v)
	{
		return *(new log_message(*this)) << v;
	}

	log_message &operator<<(std::ostream&(*f)(std::ostream&)) 
	{
		return *(new log_message(*this)) << f;
	}

	// No definition is provided to force the 'unresolved external' error when
	// trying to use this operator with 'endl' argument as it is meaningless.
	void operator<<(flush_internal* endl);

	void write(log_message *message);

	void use_time();

	void use_prefix(std::string pref);

	bool print;
	bool save;
	boost::filesystem::path file_path;
private:
	int i;
	int log_length;
	bool add_time;
	bool add_prefix;
	std::string prefix;
	std::string buffer;

	mutable boost::mutex mut;

	void flush();
	void init();
	void set_options( int buffer_length, bool do_print, bool do_save, bool do_print_time, boost::filesystem::path save_file_path);
};
/*! @} */
#endif // LOG_UTIL
