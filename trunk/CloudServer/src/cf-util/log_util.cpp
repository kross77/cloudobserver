#include "log_util.h"

log_util::log_util( int buffer_length, bool do_print)
{
	this->i = 0;
	this->log_length = buffer_length;
	this->print = do_print;
	this->save = false;
	this->add_prefix = false;
	this->add_time = false;
}

log_util::log_util( int buffer_length, bool do_print, bool do_save, boost::filesystem::path save_file_path)
{
	this->i = 0;
	this->log_length = buffer_length;
	this->print = do_print;
	this->save = do_save;
	this->add_prefix = false;
	this->add_time = false;
	this->file_path = save_file_path;
}

log_util::log_util( int buffer_length, bool do_print, bool do_save, bool do_print_time, boost::filesystem::path save_file_path)
{
	log_util( buffer_length, do_print, do_save, save_file_path);
	add_time = do_print_time;
}

void log_util::write(log_message *message)
{
	if (!print && !save)
		return;

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
	this_message += message->data.str();
	this_message += "\n";

	if(print)
	{
		std::cout << this_message;
	}

	if (save)
	{
		{
			boost::mutex::scoped_lock lock(mut);
			buffer += this_message;
		};
		i += this_message.length();
		if (i >= log_length)
		{
			flush();
			i = 0;
		}
	}
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

void log_util::flush()
{
	boost::filesystem::ofstream datFile;
	datFile.open(file_path, std::ofstream::app | std::ofstream::out	);
	{
		boost::mutex::scoped_lock lock(mut);
		datFile.write(buffer.c_str(), buffer.length());
		buffer.clear();
	};
	datFile.close();
}

log_util::~log_util()
{
	if (save)
		flush();
}

flush_internal* log_util::endl = 0;
