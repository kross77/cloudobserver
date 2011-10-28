#include "log_util.h"

log_util::log_util( int buffer_length, bool do_print)
{
	this->set_options(buffer_length,  do_print,  false,  false, "");
}

log_util::log_util( int buffer_length, bool do_print, bool do_save, boost::filesystem::path save_file_path)
{
	this->set_options(buffer_length,  do_print,  do_save,  false, save_file_path);
}

log_util::log_util( int buffer_length, bool do_print, bool do_save, bool do_print_time, boost::filesystem::path save_file_path)
{
	this->set_options(buffer_length,  do_print,  do_save,  do_print_time, save_file_path);
}

void log_util::init()
{
	this->i = 0;
	this->print = false;
	this->save = false;
	this->add_prefix = false;
	this->add_time = false;
}

void log_util::set_options( int buffer_length, bool do_print, bool do_save, bool do_print_time, boost::filesystem::path save_file_path)
{
	init();

	this->log_length = buffer_length;
	this->print = do_print;
	this->save = do_save;
	this->file_path = save_file_path;
	this->add_time = do_print_time;
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
