#include "log_util.h"

log_util::log_util( int buffer_length, bool do_print)
{
	this->i = 0;
	this->log_length = buffer_length;
	this->messages_buffer = new std::string[log_length];
	this->print = do_print;
	this->save = false;
	this->add_prefix = false;
	this->add_time = false;
}

log_util::log_util( int buffer_length, bool do_print, bool do_save, boost::filesystem::path save_file_path)
{
	this->i = 0;
	this->log_length = buffer_length;
	this->messages_buffer = new std::string[log_length];
	this->print = do_print;
	this->save = do_save;
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
			std::string ls = "";
			for(int j = 0; j < i; ++j)
				ls += messages_buffer[j];

			add_string_into_file(ls, this->file_path);
			i = 0;
		}
	}
}

boost::shared_ptr<std::ostringstream> log_util::find_stream(std::string thread_id)
{
	boost::mutex::scoped_lock lock(mut_threads_pool);
	boost::shared_ptr<std::ostringstream>& result = threads_pool[thread_id];
	if (result.get() == 0)
		result.reset(new std::ostringstream());
	return result;
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
		std::string ls = "";
		for(int j = 0; j < i; ++j)
			ls += messages_buffer[j];

		add_string_into_file(ls, this->file_path);
		i = 0;
	}
}
flush_internal* log_util::endl = 0;
