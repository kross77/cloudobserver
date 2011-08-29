#include "file_service.h"

file_service::file_service()
{
	general_util = new general_utils();
	http_util = new http_utils();
	this->root_path = boost::filesystem::current_path().string();
	this->show_directory_contents = false;
}

void file_service::service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
{
	response->headers.insert(std::pair<std::string, std::string>("Connection", "close"));

	if ((request->url == "/") &&( boost::filesystem::exists( boost::filesystem::path(this->root_path / "index.html"))))
		request->url = "/index.html";

	if(http_util->url_decode(this->get_user_name(request)) != "guest")
	{
		if(request->body.length() > 0)
		{
			try
			{
				std::map<std::string, std::string>save_file;
				save_file = http_util->parse_multipart_form_data(request->body);
				std::string file_name =save_file.find("file_name")->second;
				this->save_string_into_file(save_file.find("datafile")->second, file_name);
			}
			catch(std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	request->url = http_util->url_decode(request->url);
	std::ostringstream body;
	boost::filesystem::path target = root_path.wstring();
	target /= http_util->utf8_to_utf16(http_util->url_decode(request->url));

	if (exists(target))
	{
		if (is_regular_file(target))
		{
			boost::uintmax_t target_size = file_size(target);
			if (target_size != 0)
			{
				boost::posix_time::ptime target_modified = boost::posix_time::from_time_t(last_write_time(target));
				if (request->arguments["info"] == "true")
					body << target.filename()
					<< "<br/> size: " << target_size << " byte" << ((target_size > 1) ? "s" : "")
					<< "<br/> modified: " << target_modified
					<< "<br/><a href=\"" << http_util->url_encode(request->url) << "\">download</a>";
				else
				{
					std::string modified = boost::posix_time::to_iso_extended_string( target_modified );
					if ( modified == request->headers["If-Modified-Since"])
					{
						response->status = 304;
						response->description = "Not Modified";
						response->send(*socket);
						return;
					}
					else
					{
						response->headers.insert(std::pair<std::string, std::string>("Last-Modified", modified	));
						response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(target_size)));
						response->headers.insert(std::pair<std::string, std::string>("Cache-Control", "max-age=" + boost::lexical_cast<std::string>(this->expiration_period.total_seconds())));
						response->headers.insert(std::pair<std::string, std::string>("Expires", boost::posix_time::to_iso_extended_string( boost::posix_time::second_clock::local_time() + this->expiration_period ) ));
						response->send(*socket);

						std::ifstream stream;
						int buff_length = 8192;
						char *buffer = new char[buff_length];
						stream.open( target.string().c_str(), std::ios_base::binary );
						while (stream)
						{
							stream.read(buffer, buff_length);
							boost::asio::write(*socket, boost::asio::buffer(buffer, stream.gcount()));  
						}
						delete[] buffer;
						stream.close();
						return;
					}


				}
			}
		}
		else if (is_directory(target))
		{
			if (show_directory_contents)
			{
				response->headers.insert(std::pair<std::string, std::string>("Content-Type", "Content-Type: text/html; charset=utf-8"));
				body << http_util->utf16_to_utf8(target.wstring()) << " is a directory containing:" ;
				for (boost::filesystem::directory_iterator i(target); i != boost::filesystem::directory_iterator(); ++i)
					body
					<< "<br/><a href=\"/"
					<<   http_util->url_encode(http_util->utf16_to_utf8(general_util->get_dif_path_wstring(root_path, (*i)))) 
					<< "\">"
					<< http_util->utf16_to_utf8(i->path().filename().wstring()) << "</a>";

				target /= "./../";
				body << "<br/><a href=\"/"
					<<  http_util->url_encode(http_util->utf16_to_utf8(general_util->get_dif_path_wstring(root_path, target)))
					<< "/\"> up (../) </a>"
					<< "<br/><a href='/'>site root</a>";
			}
			else
				body << "Error 403! Listing the contents of the " << target.filename() << " directory is forbidden.";
		}
		else
			body << "Error! "<< target.filename() << "exists, but is neither a regular file nor a directory.";
	}
	else
		body << "Error 404!" << target.filename() << "does not exist\n <br/> <a href='/'>" << "Dear " << http_util->url_decode(this->get_user_name(request)) <<", please come again!</a>";

	response->body = "<head></head><body><h1>" + body.str() + "</h1></body>";
	response->send(*socket);
}

void file_service::apply_config(boost::property_tree::ptree config)
{
	this->root_path = config.get<std::string>("root_file_system_directory", this->root_path.string());
	this->show_directory_contents = config.get<bool>("show_directory_contents", this->show_directory_contents);
}

std::string file_service::get_user_name( boost::shared_ptr<http_request> request )
{
	std::string response = "";
	std::map<std::string, std::string>::iterator it = request->headers.find("email");
	if (it != request->headers.end())
		response = it->second;

	return response;
}

void file_service::save_string_into_file( std::string contents, std::string s_name )
{
	boost::filesystem::path users_path ( this->root_path / "users" );
	users_directory_path = users_path;
	general_util->create_directory(users_directory_path);
	boost::filesystem::ofstream datFile;
	boost::filesystem::path name (users_directory_path / s_name);
	datFile.open(name, std::ofstream::binary | std::ofstream::trunc | std::ofstream::out	);
	datFile.write(contents.c_str(), contents.length());
	datFile.close();
}

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<service> > &factories(types.get());
	factories["file_service"].set<file_service>();
}
