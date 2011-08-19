#include "log_util.h"

log_util::log_util( int buffer_length, bool do_print)
{
	this->thread_util = new threading_utils();
	this->i = 0;
	this->log_length = buffer_length;
	this->messages_buffer = new boost::circular_buffer<std::string>(log_length);
	this->print = true;
	this->save = false;
	this->add_prefix = false;
	this->add_time = false;
}

log_util::log_util( int buffer_length, bool do_print, bool do_save, boost::filesystem::path save_file_path)
{
	this->thread_util = new threading_utils();
	this->i = 0;
	this->log_length = buffer_length;
	this->messages_buffer = new boost::circular_buffer<std::string>(log_length);
	this->print = true;
	this->save = true;
	this->add_prefix = false;
	this->add_time = false;
	this->file_path = save_file_path;
}

void log_util::use_time()
{
	this->add_time = true;
}

void log_util::use_prefix(std::string pref)
{
	this->add_prefix = true;
	this->prefix = pref;
}

void log_util::is_filled()
{
	if (i >= messages_buffer->capacity())
	{
		if (save)
		{
			i = 0;
			BOOST_FOREACH(std::string s, *messages_buffer)
			{
				add_string_into_file(s, this->file_path);
			}
			i = 0;
		}
	}
}

boost::shared_ptr<std::stringstream> log_util::find_stream(boost::thread::id thread_id)
{
	typedef std::map<boost::thread::id, boost::shared_ptr<std::stringstream> > map_ts;
	typedef std::pair<boost::thread::id, boost::shared_ptr<std::stringstream> > pair_ts;
	boost::shared_ptr<std::stringstream> thread_stream;
	try
	{
		thread_stream =	thread_util->safe_search_in_map<boost::thread::id, boost::shared_ptr<std::stringstream>, map_ts::iterator>(thread_id, threads_pool);
	}
	catch(std::exception &e)
	{
		thread_util->safe_insert<pair_ts, map_ts>(std::make_pair(thread_id, boost::shared_ptr<std::stringstream>(new std::stringstream())), threads_pool);
		thread_stream =	thread_util->safe_search_in_map<boost::thread::id, boost::shared_ptr<std::stringstream>, map_ts::iterator>(thread_id, threads_pool);
	}
	return thread_stream;
}

void log_util::clean_stringstream(std::stringstream &message)
{
	message.flush();
	message.clear();
	message.seekp(0);
	message.str("");
}

void log_util::add_string_into_file( std::string contents, boost::filesystem::path file_path )
{
	boost::filesystem::ofstream datFile;
	datFile.open(file_path, std::ofstream::binary | std::ofstream::app | std::ofstream::out	);
	datFile.write(contents.c_str(), contents.length());
	datFile.close();
}

log_util::~log_util()
{
	boost::mutex::scoped_lock lock(mut);
	if (save)
	{
		BOOST_FOREACH(std::string s, *messages_buffer)
		{
			add_string_into_file(s, this->file_path);
		}
	}
}
FlushInternal* log_util::endl = 0;
