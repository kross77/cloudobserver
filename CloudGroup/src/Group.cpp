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
#include "PublicProducerPrototype.h"
#include "PublicRendererPrototype.h"

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

void try_open_lib(shared_library & lib, string & path)
{
	if (!lib.open()) {
		cout << "Library failed to open: " << path << endl;
	}
	else
	{
		cout << "Library " << path << " opened." << endl;
	}
}
void renderChar(ExtendedCharPtr data) { 
	cout << "Received char: ";
	for (int i = 0; i < data.length; i++)
		//cout << *data.data++;
		cout << data.data[i];
	cout << endl;
}
int main()
{
	
	string simple_producer_path = "simpleProducer";
	string simple_renderer_path = "simpleRenderer";

	simple_producer_path = simple_producer_path + extention; 
	simple_renderer_path = simple_renderer_path + extention; 

	shared_library simple_producer(simple_producer_path);
	shared_library simple_renderer(simple_renderer_path);

	try_open_lib(simple_producer, simple_producer_path );
	try_open_lib(simple_renderer, simple_renderer_path);

	// Use the shared_library::call to automatically call an
	// Extension-specific function in the shared library,
	// which takes a type_map.
	type_map producer_types;
	if (!simple_producer.call(producer_types)) {
		cerr << "Function not found!" << endl;
		cin.get();
		return 1;
	}

	// Retrieve a map of all animal factories taking an int and indexed
	// by a string from the type_map.
	map<string, factory<PublicProducerPrototype, int> >& producer_factories(producer_types.get());
	if (producer_factories.empty()) {
		cerr << "Producers not found!" << endl;
		cin.get();
		return 1;
	}

	// Create each animal.
	ExtendedCharPtr CharPtr;
	CharPtr.data = new char[10];
	CharPtr.length = 10; 
	
	int generator = 1;

	for (map<string, factory<PublicProducerPrototype, int> >::iterator it
		= producer_factories.begin();
		it != producer_factories.end(); ++it) {
			++generator;
			cout << "Creating Producers using factory: " << it->first << endl;
			boost::scoped_ptr<PublicProducerPrototype> current_producer(it->second.create(generator));
			cout << "Created data producer: " << 
				" Lets try it on data generation: " << endl;
			renderChar(current_producer->updateData(CharPtr));
	}

	cin.get();

}