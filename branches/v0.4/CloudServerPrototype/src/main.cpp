#include "util.h"
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>
// Boost
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

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
//CF
#include <http.h>


#ifdef _WIN32
#include "Windows.h"
#define _USE_32_BIT_TIME_T
#endif

using namespace boost::asio::ip;
using namespace boost::filesystem;
using namespace boost::posix_time;
using namespace boost::local_time;
using namespace boost::gregorian;
using namespace std;

int port_number;
path file_service_default_path;

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

void file_service(http_request request, boost::shared_ptr<tcp::socket> socket)
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
					return;
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
}

void request_response_loop(boost::shared_ptr<tcp::socket> socket)
{
	try
	{
		http_request request(*socket);
		cout << "request url: " << request.url << "\n";
		//print_map_contents(request.headers, "headers");
		print_map_contents(request.arguments, "arguments");
		//response.body = "<head></head><body><h1>It Rocks!</h1></body>";
		file_service(request, socket);
		socket->close();
		cout << "connection resolved." << endl;
	}
	catch(exception &e)
	{
		cout << e.what() << endl; //"The parameter is incorrect" exception
	}
}


void acceptor_loop(){
	boost::asio::io_service io_service;
	int m_nPort = port_number;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), m_nPort));
	cout << "Waiting for connection..." << endl;
	while(true)
	{
		try
		{
			boost::shared_ptr<tcp::socket> socket =
				boost::make_shared<tcp::socket>(boost::ref(io_service));			
			acceptor.accept(*socket);
			cout << "connection accepted." << endl;
			print_user_info(*socket);
			boost::thread workerThread(request_response_loop, socket);
		}
		catch(exception &e)
		{
			cout << e.what() << endl; //"The parameter is incorrect" exception
		}
	}
}
int main()
{ 
	port_number = 12345;
	file_service_default_path = boost::filesystem::current_path();

	boost::thread workerThread(acceptor_loop);
	std::cout << "Type 'exit' and hit enter to stop broadcasting and close the application..." << std::endl;
	std::string exit;
	do
	{
		cin >> exit;
		boost::this_thread::sleep(boost::posix_time::milliseconds(250));
	} while (exit != "exit");
}