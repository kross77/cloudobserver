#include "file_service.h"

file_service::file_service()
{
	this->root_path = boost::filesystem::current_path().string();
	this->show_directory_contents = false;

	current_cach_size = 0;
	nowTime = boost::posix_time::second_clock::universal_time();
	first_time = true;

	//TODO: make editable from config
	#ifdef DEBUG
	desiredTimeFame = (long long)(1000.0f);
	#else
	desiredTimeFame = (long long)(10000.0f);
	#endif
	cach_size_limit = 15000000;
	cachable_file_size_limit = 2500000;

}

boost::shared_ptr<fs_file> file_service::create_file( boost::filesystem::path p )
{
	 boost::shared_ptr<fs_file> f = fs_utils::create_file(p);
	if (f->size <= cachable_file_size_limit)
	{
		f->is_cachable = true;
		f->is_cached = false;
	}
	else
		f->is_cachable = false;

	return f;
}

void file_service::apply_config(boost::shared_ptr<boost::property_tree::ptree> config)
{
	this->root_path = config->get<std::string>("root_file_system_directory", this->root_path.string());
	first_time = true;
	boost::thread workerThread(boost::bind(&file_service::files_walker, this));
	this->show_directory_contents = config->get<bool>("show_directory_contents", this->show_directory_contents);
}

boost::shared_ptr<std::string> file_service::cach_file( boost::shared_ptr<fs_file> f )
{
	boost::shared_ptr<std::string> b = load_file_into_memory(f);
	f->buffer = b;
	f->is_cached = true;
	return b;
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
	return http_utils::url_encode(http_utils::utf16_to_utf8(general_utils::get_dif_path_wstring(root_path, p)));
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

boost::shared_ptr<std::string> file_service::load_file_into_memory( boost::shared_ptr<fs_file> f )
{
	boost::shared_array<char> buffer( new char[f->size]);
	
	std::ifstream stream;
	stream.open( f->path.string().c_str(), std::ios_base::binary );
	while (stream)
	{
		stream.read(buffer.get(), f->size);
	}
	stream.close();

	std::stringstream temp;
	std::stringstream body;
	boost::iostreams::filtering_streambuf< boost::iostreams::input> in;

	in.push( boost::iostreams::gzip_compressor());
	temp.write(buffer.get(), f->size);
	in.push(temp);
	boost::iostreams::copy(in, body);
	boost::shared_ptr<std::string> gzip_buffer(new std::string(body.str() )) ;


	return gzip_buffer;
}

void file_service::process_request( std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	boost::shared_ptr<fs_file>  f;
	boost::shared_ptr<std::string> b;
	boost::uintmax_t size;

	if (is_directory_call(encoded_url))
	{
		try
		{
			send_directory_contents(fs.list_directory(encoded_url), socket, request, response);
		}
		catch (std::exception)
		{
			fs_utils::send_404(encoded_url, socket, request, response);
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


			if(try_send_info(f, socket, request, response))
				return;
			
			if(if_is_modified(f,socket,response,request))
				return;
			

			fs_utils::insert_file_headers(f, socket, response);

			{
				boost::shared_lock<boost::shared_mutex> lock_r(f->mutex_);
				size = f->size;
				b = f->buffer;
			}

			send_cached_file(size,b, socket, response,request);
			return;
		}


		try
		{
			f = fs.find(encoded_url);
		}
		catch(std::exception)
		{
			fs_utils::send_404(encoded_url, socket,request,response);
			return;
		}

		if (f)
		{
			if(try_send_info(f, socket, request, response))
				return;

			if(if_is_modified(f,socket,response,request))
				return;

			fs_utils::insert_file_headers(f, socket, response);

			if (f->is_cachable)
			{

				if (f->is_cached)
				{
					{
						boost::shared_lock<boost::shared_mutex> lock_r(f->mutex_);
						size = f->size;
						b = f->buffer;
					}
					send_cached_file(size,b, socket, response, request);
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
					send_cached_file(size,b, socket, response, request);
					{
						cached_files.put(encoded_url,f);
					}
					return;
				}
			}
			else
			{
				fs_utils::send_uncachable_file(f, socket, response);
				return;
			}
		}
	}

}

void file_service::send_cached_file( boost::uintmax_t size, boost::shared_ptr<std::string> buffer, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request  )
{
	if (std::string::npos != request->headers["Accept-Encoding"].find("gzip"))
	{
		http_utils::set_gzip_content_type(response);
		//std::cout << "short one" << std::endl;
		http_utils::send(*buffer, socket, response);
	}
	else
	{
		//std::cout << "decode catched file one" << std::endl;
		std::stringstream temp_body(*buffer);
		std::stringstream body;
		boost::iostreams::filtering_streambuf< boost::iostreams::input> out;
		out.push( boost::iostreams::gzip_decompressor());
		out.push(temp_body);
		boost::iostreams::copy(out, body);
		http_utils::send(body.str(), socket, response);
		
	}
}

void file_service::send_directory_contents( std::set<std::string> list, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	std::ostringstream body;
	boost::filesystem::path target = root_path.wstring();
	target /= http_utils::utf8_to_utf16(http_utils::url_decode(request->url));
	if (show_directory_contents)
	{
		response->headers.insert(std::pair<std::string, std::string>("Content-Type", "text/html; charset=utf-8"));
		body << http_utils::utf16_to_utf8(target.wstring()) << " is a directory containing:" ;

		BOOST_FOREACH(std::string s, list)
		{
			body << "<br/><a href=\""
				<< s
				<< "\">"
				<< http_utils::url_decode(s) << "</a>";

		}

		target /= "./../";
		body << "<br/><a href=\"/"
			<<  http_utils::url_encode(http_utils::utf16_to_utf8(general_utils::get_dif_path_wstring(root_path, target)))
			<< "/\"> up (../) </a>"
			<< "<br/><a href='/'>site root</a>";
	}
	else
		body << "Error 403! Listing the contents of the " << target.filename() << " directory is forbidden.";

	response->body = "<head></head><body><h1>" + body.str() + "</h1></body>";
	response->send(*socket);
}

void file_service::service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request,  boost::shared_ptr<shared> shared_data)
{
	boost::shared_ptr<http_response> response(new http_response(), boost::bind(&pointer_utils::delete_ptr<http_response>, _1));

	if (request->url == "/")
	{
		try
		{
			fs.find("/index.html");
			request->url = "/index.html";
		}
		catch(std::exception){}
	}

	if(http_utils::url_decode(this->get_user_name(request)) != "guest")
	{
		if(request->body.length() > 0)
		{
			try
			{
				std::map<std::string, std::string> save_file;
				save_file = http_utils::parse_multipart_form_data(request->body);
				std::string file_name =save_file.find("file_name")->second;
				fs_utils::save_string_into_file(save_file.find("datafile")->second, file_name,  this->root_path / "users");
			}
			catch(std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	process_request(request->url, socket, request, response);
}

bool file_service::if_is_modified(boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request)
{
	std::map<std::string, std::string>::iterator it= request->headers.find("If-Modified-Since");
	if (it != request->headers.end() )
	{
		if (f->modified == it->second)
		{
			fs_utils::send_not_modified_304(socket, response);
			return true;
		}
	}
	return false;
}

bool file_service::try_send_info( boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	std::map<std::string, std::string>::iterator it= request->arguments.find("info");
	if (it != request->arguments.end() )
	{
		if ( std::string("true") == std::string(it->second))
		{
			fs_utils::send_info( f,socket,request,response );
			return true;
		}
	}
	return false;
}

std::string file_service::service_check( boost::shared_ptr<http_request>, boost::shared_ptr<shared> )
{
	return "executor";
}

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<base_service> > &factories(types.get());
	factories["file_service"].set<file_service>();
}
