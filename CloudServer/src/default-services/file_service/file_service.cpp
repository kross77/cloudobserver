#include "file_service.h"

file_service::file_service()
{
	general_util = new general_utils();
	this->root_path = boost::filesystem::current_path().string();
	this->show_directory_contents = false;
}

void file_service::service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
{
	//std::cout << '\07' << "Request body: " << request->body << std::endl << "Request size: " <<  request->body.length() << std::endl;
	if (!this->show_directory_contents && (request->url == "/"))
		request->url = "/index.html";

	std::ostringstream body;
	boost::filesystem::path target = this->root_path / request->url;

	response->headers.insert(std::pair<std::string, std::string>("Connection", "close"));

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
						<< "<br/><a href=\"" << request->url << "\">download</a>";
				else
				{
					std::ostringstream formatter;
					formatter.imbue(std::locale(std::cout.getloc(), new boost::posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT")));
					formatter << target_modified;
					if (formatter.str() == request->headers["If-Modified-Since"])
					{
						response->status = 304;
						response->description = "Not Modified";
					}
					else
					{
						response->headers.insert(std::pair<std::string, std::string>("Last-Modified", formatter.str()));
						response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(target_size)));
						response->headers.insert(std::pair<std::string, std::string>("Cache-Control", "max-age=" + boost::lexical_cast<std::string>(this->expiration_period.total_seconds())));

						formatter.clear();
						formatter << boost::posix_time::second_clock::local_time() + this->expiration_period;
						response->headers.insert(std::pair<std::string, std::string>("Expires", formatter.str()));

						body << std::ifstream(target.string().c_str(), std::ios::binary).rdbuf();
						response->body = body.str();
					}

					response->send(*socket);
					return;
				}
			}
		}
		else if (is_directory(target))
		{
			if (show_directory_contents)
			{
				body << target << " is a directory containing:";
				for (boost::filesystem::directory_iterator i(target); i != boost::filesystem::directory_iterator(); ++i)
					body << "<br/><a href=\"" << request->url << i->path().filename().string() << "\">" << i->path().filename().string() << "</a>";
			}
			else
				body << "Error 403! Listing the contents of the " << target.filename() << " directory is forbidden.";
		}
		else
			body << "Error! "<< target.filename() << "exists, but is neither a regular file nor a directory.";
	}
	else
		body << "Error 404!" << target.filename() << "does not exist\n <br/> <a href='/'>" << "Dear " << general_util->url_decode(this->get_user_name(request)) <<", please come again!</a>";

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
	std::map<std::string, std::string>::iterator it = request->arguments.find("email");
	if (it != request->arguments.end())
		response = it->second;

	return response;
}

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<service> > &factories(types.get());
	factories["file_service"].set<file_service>();
}
