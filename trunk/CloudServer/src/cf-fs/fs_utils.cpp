#include "fs_utils.h"

fs_utils::fs_utils()
{
	this->expiration_period = boost::posix_time::minutes(200);
	this->max_age = "max-age=" + boost::lexical_cast<std::string>(this->expiration_period.total_seconds());

}

void fs_utils::send_404( std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	std::ostringstream body;
	body << "Error 404! " << http_utils::url_decode(request->url) << " does not exist\n <br/> <a href='/'>" << "Dear " << http_utils::url_decode(get_user_name(request)) <<", please come again!</a>";

	response->body = "<head></head><body><h1>" + body.str() + "</h1></body>";
	response->send(*socket);
}

std::string fs_utils::get_user_name( boost::shared_ptr<http_request> request )
{
	std::string response = "";
	std::map<std::string, std::string>::iterator it = request->headers.find("email");
	if (it != request->headers.end())
		response = it->second;

	return response;
}

void fs_utils::send_not_modified_304( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	response->status = 304;
	response->description = "Not Modified";
	response->send(*socket);
}

void fs_utils::save_string_into_file( std::string contents, std::string s_name, boost::filesystem::path users_path )
{
	general_utils::create_directory(users_path);
	boost::filesystem::ofstream datFile;
	boost::filesystem::path name (users_path / s_name);
	datFile.open(name, std::ofstream::binary | std::ofstream::trunc | std::ofstream::out	);
	datFile.write(contents.c_str(), contents.length());
	datFile.close();
}

void fs_utils::send_uncachable_file( boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
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

void fs_utils::send_uncachable_file( boost::shared_ptr<fs_file> f , boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	if(!was_modified( f, socket, request , response))
	{
		insert_file_headers(f, socket, response);
		send_uncachable_file( f, socket, response);
	}
}
void fs_utils::insert_file_headers( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket > socket, boost::shared_ptr<http_response> response )
{
	if (f->type_extension.length() > 1)
	{
		if (boost::iequals(f->type_extension, ".html"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "text/html"));
		}
		else if ( boost::iequals(f->type_extension, ".css"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "text/css"));
		}
		else if (boost::iequals(f->type_extension, ".js"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "text/javascript"));
		}
		else if (boost::iequals(f->type_extension, ".xml"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "text/xml"));
		}
		else if (boost::iequals(f->type_extension, ".jpeg") || boost::iequals(f->type_extension, ".jpg"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "image/jpeg"));
		}
		else if (boost::iequals(f->type_extension, ".png"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "image/png"));
		}
		else if (boost::iequals(f->type_extension, ".gif"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "image/gif"));
		}
		else if (boost::iequals(f->type_extension, ".svg"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "image/svg+xml"));
		}
		else if (boost::iequals(f->type_extension, ".zip"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "application/zip"));
		}
		else if (boost::iequals(f->type_extension, ".Gzip"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "application/x-gzip"));
		}
		else if (boost::iequals(f->type_extension, ".pdf"))
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-Type", "application/pdf"));
		}
	}

	response->headers.insert(std::pair<std::string, std::string>("Last-Modified", f->modified));
	response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(f->size)));
	response->headers.insert(std::pair<std::string, std::string>("Cache-Control", max_age ));
	response->headers.insert(std::pair<std::string, std::string>("Expires", boost::posix_time::to_iso_extended_string( boost::posix_time::second_clock::local_time() + this->expiration_period ) ));
}

boost::shared_ptr<fs_file> fs_utils::create_file( boost::filesystem::path p )
{
	boost::shared_ptr<fs_file> f( new fs_file());
	f->path = p;
	{
		f->is_cachable = false;
		f->is_cached = false;
		f->buffer.reset();
	}
	f->type_extension = boost::filesystem::extension(p);
	f->size = boost::filesystem::file_size(p);
	f->modified = boost::posix_time::to_iso_extended_string( boost::posix_time::from_time_t(last_write_time(p)) );
	f->is_cachable = false;

	return f;
}

bool fs_utils::was_modified( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	std::map<std::string, std::string>::iterator it= request->headers.find("If-Modified-Since");
	if (it != request->headers.end() )
	{
		if (f->modified == it->second)
		{
			send_not_modified_304(socket, response);
			return true;
		}
	}
	return false;
}