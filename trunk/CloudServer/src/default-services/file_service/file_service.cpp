

#include "../../../service-interface/service.hpp"

//STD
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector> 

// Boost
#include <boost/process.hpp> 
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/timer.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

///////////////////////////////
#include <map>
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

#ifndef _FILE_SERVICE
#define _FILE_SERVICE
// class accessible thru Boost Extension for programs with access to service class\interface
class file_service : public service
{
public:
	file_service(boost::property_tree::ptree config)
	{ 
		service_default_path = config.get<std::string>("root_file_system_directory", boost::filesystem::current_path().string());
		show_directory_contents = config.get<bool>("show_directory_contents", false);
		std::cout << "\nCreated a File-Service" << std::endl;
	}
	~file_service(void){std::cout << "\nDestroyed a File-Service"<< std::endl;}

	//We provide files download, short files info options.
	//TODO: remove info to another service  
	virtual bool service_call (http_request request, boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
	{
		if (!show_directory_contents && (request.url == "/"))
			request.url = "/index.html";

		std::stringstream body;
		boost::filesystem::path p = (service_default_path/request.url);
		http_response response;
		response.headers.insert(std::pair<std::string, std::string>("Connection", "close"));
		if (exists(p))
		{
			if (is_regular_file(p))
			{       

				if(file_size(p) != 0)
				{
					if(request.arguments["info"] == "true")
					{
						boost::posix_time::ptime t = boost::posix_time::from_time_t(last_write_time(p));
						body << p.filename() << "<br/> size is : " << file_size(p) <<" bytes. <br/> file was modified last time @ " << t << ".<br/><a href='/" << file_service_get_dif_path(service_default_path, p) << "' > click here to download. </a>";
					}
					else
					{
						boost::posix_time::ptime t = boost::posix_time::from_time_t(last_write_time(p));
						boost::posix_time::ptime cur = boost::posix_time::second_clock::local_time();
						boost::posix_time::time_duration  ex = boost::posix_time::hours(32) + boost::posix_time::minutes(10);
						boost::posix_time::ptime expire = cur + ex;
						std::string lt = boost::lexical_cast<std::string>(ex.total_seconds());

						std::ostringstream Created , Current, Expires;
						static char const* const facet = "%a, %d %b %Y %H:%M:%S GMT";

						Created.imbue(std::locale(std::cout.getloc(), new boost::posix_time::time_facet(facet)));
						Current.imbue(std::locale(std::cout.getloc(), new boost::posix_time::time_facet(facet)));
						Expires.imbue(std::locale(std::cout.getloc(), new boost::posix_time::time_facet(facet)));

						Created << t ;
						Current << cur;	
						Expires << expire;

						response.headers.insert(std::pair<std::string, std::string>("Date", Current.str()));
						response.headers.insert(std::pair<std::string, std::string>("Server", "CF: RAC"));	

						if (  Created.str() == request.headers["If-Modified-Since"])
						{
							response.status=304;
							response.description="Not Modified";
						}
						else
						{
							int length = file_size(p);

							response.headers.insert(std::pair<std::string, std::string>("Last-Modified", Created.str()));
							response.headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(length)));
							response.headers.insert(std::pair<std::string, std::string>("Cache-Control", "max-age="+lt));
							response.headers.insert(std::pair<std::string, std::string>("Expires", Expires.str()));

							body << std::ifstream( p.string().c_str(), std::ios::binary).rdbuf();
							response.body = body.str();
						}

						response.send(*socket);
						return 1;
					}
				}

			}
			else if (is_directory(p))
			{
				if (show_directory_contents)
				{
					body << p << " is a directory containing:\n";

					for (boost::filesystem::directory_iterator itr(p); itr!=boost::filesystem::directory_iterator(); ++itr)
						body << "<br/><a href='/" << file_service_get_dif_path(service_default_path, itr->path())	<< "' >"<< itr->path().filename() << "</a>";
				}
				else
					body << "Error 403! Listing the contents of the " << p.filename() << " directory is forbidden.\n";
			}
			else
			{
				body << "Error! "<< p.filename() << "exists, but is neither a regular file nor a directory\n";
			}
		}
		else
		{
			body << "Error 404!" << p.filename() << "does not exist\n <br/> <a href='/'>Please come again!</a>";
		}
		response.body = "<head></head><body><h1>" 
			+ body.str()
			+"</h1></body>";
		response.send(*socket);
		return 1;
	}

private:
	boost::filesystem::path service_default_path;
	bool show_directory_contents;

	std::string file_service_get_dif_path(boost::filesystem::path base_path, boost::filesystem::path new_path)
	{
		boost::filesystem::path sdiffpath;
		boost::filesystem::path stmppath = new_path;
		while(stmppath != base_path) {
			sdiffpath = boost::filesystem::path(stmppath.stem().string() + stmppath.extension().string())/ sdiffpath;
			stmppath = stmppath.parent_path();
		}
		std::string diff_path = boost::lexical_cast<std::string>(sdiffpath);
		diff_path = diff_path.substr(1, (diff_path.length()-2));
		return diff_path;
	}
};

BOOST_EXTENSION_TYPE_MAP_FUNCTION {
	using namespace boost::extensions;
	std::map<std::string, factory<service, boost::property_tree::ptree> >&
		Producer_factories(types.get());
	Producer_factories["file_service"].set<file_service>();
}
#endif //_FILE_SERVICE