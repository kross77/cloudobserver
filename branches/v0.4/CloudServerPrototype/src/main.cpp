#include <stdio.h>
#include <iostream>
#include "server.h"

//Boost
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{ 
	int port_number = 12345;
	server *s = new server(port_number);
	std::cout << "Type 'exit' and hit enter to stop broadcasting and close the application..." << std::endl;
	std::string exit;
	do
	{
		std::cin >> exit;
		boost::this_thread::sleep(boost::posix_time::milliseconds(250));
	} while (exit != "exit");
	return 0;
}