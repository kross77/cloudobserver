#include "file_service.h"

file_service::file_service()
{
	general_util = new general_utils();
	http_util = new http_utils();
	fs_util = new fs_utils();
	this->root_path = boost::filesystem::current_path().string();
	this->show_directory_contents = false;
	this->expiration_period = boost::posix_time::minutes(200);
	this->max_age = "max-age=" + boost::lexical_cast<std::string>(this->expiration_period.total_seconds());
	current_cach_size = 0;
	nowTime = boost::posix_time::second_clock::universal_time();
	first_time = true;

	//TODO: make editable from config
	desiredTimeFame = (long long)(5000.0f);
	cach_size_limit = 500000;
	cachable_file_size_limit = 200000;

}

void file_service::apply_config(boost::shared_ptr<boost::property_tree::ptree> config)
{
	this->root_path = config->get<std::string>("root_file_system_directory", this->root_path.string());
	first_time = true;
	boost::thread workerThread(boost::bind(&file_service::files_walker, this));
	this->show_directory_contents = config->get<bool>("show_directory_contents", this->show_directory_contents);
}

boost::shared_array<char> file_service::cach_file( boost::shared_ptr<fs_file> f )
{
	boost::shared_array<char> b = load_file_into_memory(f);
	f->buffer = b;
	f->is_cached = true;
	return b;
}

boost::shared_ptr<fs_file> file_service::create_file( boost::filesystem::path p )
{
	boost::shared_ptr<fs_file> f( new fs_file());
	f->path = p;
	{
		f->is_cachable = false;
		f->is_cached = false;
		f->buffer.reset();
	}

	f->size = boost::filesystem::file_size(p);
	f->modified = boost::posix_time::to_iso_extended_string( boost::posix_time::from_time_t(last_write_time(p)) );
	if (f->size <= cachable_file_size_limit)
	{
		f->is_cachable = true;
		f->is_cached = false;
	}
	else
		f->is_cachable = false;

	return f;
}

void file_service::create_file( boost::filesystem::path p, fs_map &m1, std::set<std::string> &m2 )
{
	boost::shared_ptr<fs_file> f = create_file(p);
	std::string ue = "/" + encode_path( f->path );
	m1.put(ue, f);
	m2.insert(ue);
	try
	{
		cached_files.remove(ue);
	}
	catch(std::exception){}
}

void file_service::create_file( boost::filesystem::path p, std::set<std::string> &m )
{
	boost::shared_ptr<fs_file> f = create_file(p);
	std::string ue = "/" + encode_path( f->path );
	m.insert(ue);
}

std::string file_service::encode_path( boost::filesystem::path &p )
{
	return http_util->url_encode(http_util->utf16_to_utf8(general_util->get_dif_path_wstring(root_path, p)));
}

void file_service::files_walker()
{
	while(true)
	{
		timerFame.restart();

		oldTime = nowTime;
		nowTime = boost::posix_time::second_clock::universal_time();

		std::set<std::string> new_fs;
		is_dir(root_path, fs, new_fs);
		first_time=false;
		current_cach_size -= cached_files.remove_set(fs.compare_and_clean(new_fs));
		spendedTimeFame = (long long)timerFame.elapsed();
		if (spendedTimeFame < desiredTimeFame)
			boost::this_thread::sleep(boost::posix_time::milliseconds(desiredTimeFame - spendedTimeFame));
	}
}

std::string file_service::get_user_name( boost::shared_ptr<http_request> request )
{
	std::string response = "";
	std::map<std::string, std::string>::iterator it = request->headers.find("email");
	if (it != request->headers.end())
		response = it->second;

	return response;
}

void file_service::insert_file_headers( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket > socket, boost::shared_ptr<http_response> response )
{

	response->headers.insert(std::pair<std::string, std::string>("Last-Modified", f->modified));
	response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(f->size)));
	response->headers.insert(std::pair<std::string, std::string>("Cache-Control", max_age ));
	response->headers.insert(std::pair<std::string, std::string>("Expires", boost::posix_time::to_iso_extended_string( boost::posix_time::second_clock::local_time() + this->expiration_period ) ));
}

void file_service::is_dir( boost::filesystem::path dir, fs_map &old_fs, std::set<std::string> &new_fs )
{
	if(!exists(dir))
	{
		return;
	}
	//create_file(dir, old_fs, new_fs);
	if (boost::filesystem::is_directory(dir))
	{
		boost::filesystem::directory_iterator dirIter( dir );
		boost::filesystem::directory_iterator dirIterEnd;

		while ( dirIter != dirIterEnd )
		{
			if ( boost::filesystem::exists( *dirIter ) && !boost::filesystem::is_directory( *dirIter ) )
			{
				try
				{
					is_file((*dirIter), old_fs, new_fs);
				}
				catch(std::exception){}
			}
			else
			{
				try
				{
					is_dir((*dirIter), old_fs, new_fs);
				}
				catch(std::exception){}
			}
			++dirIter;
		}


	}
}

bool file_service::is_directory_call( std::string &s )
{
	if (*s.rbegin() == '/')
		return true;

	return false;
}

void file_service::is_file( boost::filesystem::path p, fs_map &old_fs, std::set<std::string> &new_fs )
{
	if (!first_time)
	{
		std::time_t t = boost::filesystem::last_write_time( p );
		boost::posix_time::ptime lastAccessTime = boost::posix_time::from_time_t( t );
		if ( lastAccessTime >= oldTime && lastAccessTime <= nowTime )
		{

			/*
			// Debug info
			std::cout << "updating file:" << p.filename() << std::endl 
			<< " that has been modified between : " <<  boost::posix_time::to_iso_extended_string(oldTime)
			<< " and " << boost::posix_time::to_iso_extended_string(nowTime)
			<< " at " << boost::posix_time::to_iso_extended_string(lastAccessTime) 
			<< std::endl;
			*/


			create_file(p, old_fs, new_fs);
			return;
		}
		create_file(p, new_fs);
	}
	else
	{
		create_file(p, old_fs, new_fs);
	}
}

boost::shared_array<char> file_service::load_file_into_memory( boost::shared_ptr<fs_file> f )
{
	boost::shared_array<char> buffer( new char[f->size]);
	std::ifstream stream;
	stream.open( f->path.string().c_str(), std::ios_base::binary );
	while (stream)
	{
		stream.read(buffer.get(), f->size);
	}
	stream.close();
	return buffer;
}

void file_service::process_request( std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	boost::shared_ptr<fs_file>  f;
	boost::shared_array<char> b;
	boost::uintmax_t size;

	if (is_directory_call(encoded_url))
	{
		try
		{
			send_directory_contents(fs.list_directory(encoded_url), socket, request, response);
		}
		catch (std::exception)
		{
			fs_util->send_404(encoded_url, socket, request, response);
			return;
		}
	}
	else
	{

		try
		{
			f = cached_files.find(encoded_url);
		}
		catch(std::exception)
		{}

		if (f)
		{

			if(request->arguments["info"] == "true")
			{
				send_info(f, socket, request, response);
				return;
			}

			std::map<std::string, std::string>::iterator it= request->headers.find("If-Modified-Since");
			if (it != request->headers.end() )
			{
				if (f->modified == it->second)
				{
					fs_util->send_not_modified_304(socket, response);
					return;
				}
			}

			insert_file_headers(f, socket, response);

			{
				boost::shared_lock<boost::shared_mutex> lock_r(f->mutex_);
				size = f->size;
				b = f->buffer;
			}

			send_cached_file(size,b, socket, response);
			return;
		}


		try
		{
			f = fs.find(encoded_url);
		}
		catch(std::exception)
		{
			fs_util->send_404(encoded_url, socket,request,response);
			return;
		}

		if (f)
		{
			if(request->arguments["info"] == "true")
			{
				send_info(f, socket, request, response);
				return;
			}

			std::map<std::string, std::string>::iterator it= request->headers.find("If-Modified-Since");
			if (it != request->headers.end() )
			{
				if (f->modified == it->second)
				{
					fs_util->send_not_modified_304(socket, response);
					return;
				}
			}

			insert_file_headers(f, socket, response);

			if (f->is_cachable)
			{

				if (f->is_cached)
				{
					{
						boost::shared_lock<boost::shared_mutex> lock_r(f->mutex_);
						size = f->size;
						b = f->buffer;
					}
					send_cached_file(size,b, socket, response);
					return;
				}
				else
				{
					{
						boost::upgrade_lock<boost::shared_mutex> lock(f->mutex_);
						boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
						while((current_cach_size+f->size) >= cach_size_limit)
						{
							current_cach_size = current_cach_size - cached_files.remove_last();
						}
						b = cach_file(f);
						size = f->size;
						current_cach_size = current_cach_size + size;
					}
					send_cached_file(size,b, socket, response);
					{
						cached_files.put(encoded_url,f);
					}
					return;
				}
			}
			else
			{
				send_uncachable_file(f, socket, response);
				return;
			}
		}
	}

}



void file_service::send_cached_file( boost::uintmax_t size, boost::shared_array<char> buffer, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	response->send(*socket);
	boost::asio::write(*socket, boost::asio::buffer(buffer.get(), size));
}

void file_service::send_directory_contents( std::set<std::string> list, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	std::ostringstream body;
	boost::filesystem::path target = root_path.wstring();
	target /= http_util->utf8_to_utf16(http_util->url_decode(request->url));
	if (show_directory_contents)
	{
		response->headers.insert(std::pair<std::string, std::string>("Content-Type", "text/html; charset=utf-8"));
		body << http_util->utf16_to_utf8(target.wstring()) << " is a directory containing:" ;

		BOOST_FOREACH(std::string s, list)
		{
			body << "<br/><a href=\""
				<< s
				<< "\">"
				<< http_util->url_decode(s) << "</a>";

		}

		target /= "./../";
		body << "<br/><a href=\"/"
			<<  http_util->url_encode(http_util->utf16_to_utf8(general_util->get_dif_path_wstring(root_path, target)))
			<< "/\"> up (../) </a>"
			<< "<br/><a href='/'>site root</a>";
	}
	else
		body << "Error 403! Listing the contents of the " << target.filename() << " directory is forbidden.";

	response->body = "<head></head><body><h1>" + body.str() + "</h1></body>";
	response->send(*socket);
}

void file_service::send_uncachable_file( boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	response->send(*socket);
	//std::cout << "I have sent a big file!" << std::endl;
	boost::shared_lock<boost::shared_mutex> lock_r(f->mutex_);
	std::ifstream stream;
	int buff_length = 8192;
	boost::shared_array<char> buffer( new char[buff_length]);
	stream.open( f->path.string().c_str(), std::ios_base::binary);
	while (stream)
	{
		stream.read(buffer.get(), buff_length);
		boost::asio::write(*socket, boost::asio::buffer(buffer.get(), stream.gcount()));
	}
	stream.close();
}

void file_service::send_info( boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	std::ostringstream body;
	body << f->path.filename()
		<< "<br/> size: " << f->size << " byte" << ((f->size > 1) ? "s" : "")
		<< "<br/> modified: " << f->modified
		<< "<br/><a href=\"" << http_util->url_encode(request->url) << "\">download</a>";
	response->body = "<head></head><body><h1>" + body.str() + "</h1></body>";
	response->send(*socket);
}

void file_service::service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
{
	if (request->url == "/")
	{
		try
		{
			fs.find("/index.html");
			request->url = "/index.html";
		}
		catch(std::exception){}
	}

	if(http_util->url_decode(this->get_user_name(request)) != "guest")
	{
		if(request->body.length() > 0)
		{
			try
			{
				std::map<std::string, std::string> save_file;
				save_file = http_util->parse_multipart_form_data(request->body);
				std::string file_name =save_file.find("file_name")->second;
				fs_util->save_string_into_file(save_file.find("datafile")->second, file_name,  this->root_path / "users");
			}
			catch(std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	process_request(request->url, socket, request, response);
}

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<service> > &factories(types.get());
	factories["file_service"].set<file_service>();
}
