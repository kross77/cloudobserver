#include "log_util.h"

log_util::log_util( int buffer_length, bool do_print)
{
	this->thread_util = new threading_utils();
	this->i = 0;
	this->log_length = buffer_length;
	this->messages_buffer = new std::string[log_length];
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
	this->messages_buffer = new std::string[log_length];
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
	if (i >= log_length)
	{
		if (save)
		{
			for(int j = 0; j==i; ++j)
				add_string_into_file(messages_buffer[j], this->file_path);
			
			i = 0;
		}
	}
}

boost::shared_ptr<std::ostringstream> log_util::find_stream(boost::thread::id thread_id)
{
	typedef std::map<boost::thread::id, boost::shared_ptr<std::ostringstream> > map_ts;
	typedef std::pair<boost::thread::id, boost::shared_ptr<std::ostringstream> > pair_ts;
	try
	{
		return thread_util->safe_search_in_map<boost::thread::id, boost::shared_ptr<std::ostringstream>, map_ts::iterator>(thread_id, threads_pool);
	}
	catch(std::exception &e)
	{
		boost::shared_ptr<std::ostringstream> thread_stream(new std::ostringstream());
		thread_util->safe_insert<pair_ts, map_ts>(std::make_pair(thread_id, thread_stream), threads_pool);
		return thread_stream;
	}
}

void log_util::clean_ostringstream(std::ostringstream &message)
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
		for(int j = 0; j==i; ++j)
			add_string_into_file(messages_buffer[j], this->file_path);

		i = 0;
	}
}
flush_internal* log_util::endl = 0;
