#include <iostream>
#include <map>

// Boost
#include <boost/asio.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>

#include <boost/extension/factory.hpp>
#include <boost/extension/extension.hpp>
#include <boost/extension/shared_library.hpp>
#include <boost/extension/type_map.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>

#include "ExtendedCharPtr.h"

using namespace boost::extensions;
using namespace std;

#ifdef WIN
string extention = ".dll";
#elif defined LIN
string extention = ".so";
#elif defined MAC
string extention = ".dylib"; // as wall .bundle can be used.
#else
#error "unknown platform";
#endif

void try_open_lib(shared_library lib, string path)
{
	if (!lib.open()) {
		cout << "Library failed to open: " << path << endl;
	}
	else
	{
		cout << "Library " << path << " opened." << endl;
	}
}

int main()
{
	string LastUnit_path = "LastUnit";
	string FirstUnit_path = "FirstUnit";

	LastUnit_path = LastUnit_path + extention; 
	FirstUnit_path = FirstUnit_path + extention; 

	shared_library LastUnit(LastUnit_path);
	shared_library FirstUnit(FirstUnit_path);

	try_open_lib(LastUnit, LastUnit_path );
	try_open_lib(FirstUnit, FirstUnit_path);

	cin.get();
}