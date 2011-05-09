#ifndef FILE_SERVICE_HPP
#define FILE_SERVICE_HPP

#include "../../../service-interface/service.hpp"


#include <iostream>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector> 

#include <boost/process.hpp> 
// Boost
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

using namespace boost::asio::ip;
using namespace boost::filesystem;
using namespace boost::posix_time;
using namespace boost::local_time;
using namespace boost::gregorian;
using namespace std;

class BOOST_EXTENSION_EXPORT_DECL file_service : virtual public service
{
public:
	file_service(path default_path) : service(default_path){std::cout << "\nCreated a File-Service";}
	virtual ~file_service(void){std::cout << "\nDestroyed a File-Service";}
	virtual bool service_call (http_request request, boost::shared_ptr<tcp::socket> socket)
	{
		stringstream body;
		path p = (file_service_default_path/request.url);
		http_response response;
		response.headers.insert(pair<string, string>("Connection", "close"));
		if (exists(p))
		{
			if (is_regular_file(p))
			{       

				if(file_size(p) != 0)
				{
					if(request.arguments["info"] == "true")
					{
						ptime t = from_time_t(last_write_time(p));
						body << p.filename() << "<br/> size is : " << file_size(p) <<" bytes. <br/> file was modified last time @ " << t << ".<br/><a href='/" << file_service_get_dif_path(file_service_default_path, p) << "' > click here to download. </a>";
					}
					else if(file_service_file_can_exec(p))
					{
						if(request.arguments["execute"] == "true")
						{
							if(request.arguments["args"] == "true")
							{
								// if args vector existsts fill it up like
								//   std::vector<std::string> args; 
								//   args.push_back("--version"); 
							}
							//execute (http://www.highscore.de/boost/process/process/tutorials.html)
							//std::string exec = "bjam"; 
							//bp::context ctx; 
							//ctx.stdout_behavior = bp::silence_stream(); 
							//bp::child c = bp::launch(exec, args, ctx); 
						}
						body << p.filename() << "<br/> Can execute!" ;
					}
					else
					{
						ptime t = from_time_t(last_write_time(p));
						ptime cur = second_clock::local_time();
						time_duration  ex = hours(32) + minutes(10);
						ptime expire = cur + ex;
						string lt = boost::lexical_cast<string>(ex.total_seconds());

						ostringstream Created , Current, Expires;
						static char const* const facet = "%a, %d %b %Y %H:%M:%S GMT";

						Created.imbue(std::locale(std::cout.getloc(), new time_facet(facet)));
						Current.imbue(std::locale(std::cout.getloc(), new time_facet(facet)));
						Expires.imbue(std::locale(std::cout.getloc(), new time_facet(facet)));

						Created << t ;
						Current << cur;	
						Expires << expire;

						response.headers.insert(pair<string, string>("Date", Current.str()));
						response.headers.insert(pair<string, string>("Server", "CF: RAC"));	

						if (  Created.str() == request.headers["If-Modified-Since"])
						{
							response.status=304;
							response.description="Not Modified";
						}
						else
						{
							int length = file_size(p);

							response.headers.insert(pair<string, string>("Last-Modified", Created.str()));
							response.headers.insert(pair<string, string>("Content-Length", boost::lexical_cast<string>(length)));
							response.headers.insert(pair<string, string>("Cache-Control", "max-age="+lt));
							response.headers.insert(pair<string, string>("Expires", Expires.str()));

							body << std::ifstream( p.string().c_str(), ios::binary).rdbuf();
							response.body = body.str();
						}

						response.send(*socket);
						return 1;
					}
				}

			}
			else if (is_directory(p))
			{
				body << p << " is a directory containing:\n";

				for (boost::filesystem::directory_iterator itr(p); itr!=boost::filesystem::directory_iterator(); ++itr)
				{

					body << "<br/><a href='/" << file_service_get_dif_path(file_service_default_path, itr->path())	<< "' >"<< itr->path().filename() << "</a>";
				}
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

	bool file_service_file_can_exec(path p)
	{
		#ifdef WIN
			if((p.extension().string() == ".exe")||(p.extension().string() == ".bat"))
			{
				return true;
			}
		#elif defined LIN
			if( !access(p, X_OK)){ return true;}
		#elif defined MAC
			if( !access(p, X_OK)){ return true;} // probably...
		#else
			#error "unknown platform";
		#endif
		return false;
	}

	string file_service_get_dif_path(path base_path, path new_path)
	{
		path sdiffpath;
		path stmppath = new_path;
		while(stmppath != base_path) {
			sdiffpath = path(stmppath.stem().string() + stmppath.extension().string())/ sdiffpath;
			stmppath = stmppath.parent_path();
		}
		string diff_path = boost::lexical_cast<string>(sdiffpath);
		diff_path = diff_path.substr(1, (diff_path.length()-2));
		return diff_path;
	}


};

#endif