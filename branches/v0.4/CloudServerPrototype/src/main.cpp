// Map (for Boost Extension), Socket Utils
#include "utilities.h"
//General STD
#include <sstream>
#include <set>

//Boost
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

//General Service header Class\Interface
#include "../service-interface/service.hpp"

//TODO get rid of using namespace
using namespace boost::asio::ip;
using namespace boost::filesystem;
using namespace boost::posix_time;
using namespace boost::local_time;
using namespace boost::gregorian;
using namespace std;

//Params for requests unification - each service presents us with request arguments and headers 
struct sl_service
{
	string name;         
	set<string> arguments;
	set<string> headers;
	string relm;
};

//set filled with services requirements
set<sl_service> read_config;

int port_number;
path file_service_default_path;

// We should forward request to shared library
void request_response_loop(boost::shared_ptr<tcp::socket> socket)
{
	try
	{
		http_request request(*socket);
		cout << "request url: " << request.url << "\n";
		print_map_contents(request.headers, "headers");
		print_map_contents(request.arguments, "arguments");
		//response.body = "<head></head><body><h1>It Rocks!</h1></body>";
		//file_service(request, socket); 
		socket->close();
		cout << "connection resolved." << endl;
	}
	catch(exception &e)
	{
		cout << e.what() << endl; //"The parameter is incorrect" exception
	}
}

// We should provide each server client with a thread for dealing with his request
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

// We provide server with port number and start it in a new thread.
int main()
{ 
	port_number = 12345;
	//file_service_default_path = boost::filesystem::current_path();

	boost::thread workerThread(acceptor_loop);
	std::cout << "Type 'exit' and hit enter to stop broadcasting and close the application..." << std::endl;
	std::string exit;
	do
	{
		cin >> exit;
		boost::this_thread::sleep(boost::posix_time::milliseconds(250));
	} while (exit != "exit");
}