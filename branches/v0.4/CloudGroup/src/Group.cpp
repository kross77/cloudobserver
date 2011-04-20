// DO NOT FORGET TO CLEAN PROJECTS AFTER BUILD! It is needed because our shared libraries are not directly connected to main project.

#include <iostream>
#include <map>

//#include <boost/circular_buffer.hpp> // there are plans on using circular_buffer as transport layer inside process between dlls

#include <boost/shared_ptr.hpp> // aka std::shared_ptr

#include <boost/extension/factory.hpp>
#include <boost/extension/extension.hpp>
#include <boost/extension/shared_library.hpp>
#include <boost/extension/type_map.hpp>

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

template <class BaseClass, class ConstructorType>
map<string, factory<BaseClass, ConstructorType> > get_factories (shared_library & lib) {
	type_map lib_types;
	if (!lib.call(lib_types)) {
		cerr << "Types map not found!" << endl;
		cin.get();
	}

	map<string, factory<BaseClass, ConstructorType> > lib_factories(lib_types.get());
	if (lib_factories.empty()) {
		cerr << "Producers not found!" << endl;
		cin.get();
	}
	return lib_factories;
}

template <class BaseClass, class ConstructorType>
boost::shared_ptr<BaseClass> get_class (shared_library & lib, std::string class_name, ConstructorType value ) {
	map<string, factory<BaseClass, ConstructorType> > lib_factories = get_factories<BaseClass, ConstructorType>(lib);
	boost::shared_ptr<BaseClass> lib_class(lib_factories[class_name].create(value));
	return lib_class;
}

template <class BaseClass>
map<string, factory<BaseClass> > get_factories (shared_library & lib) {
	type_map lib_types;
	if (!lib.call(lib_types)) {
		cerr << "Types map not found!" << endl;
		cin.get();
	}

	map<string, factory<BaseClass> > lib_factories(lib_types.get());
	if (lib_factories.empty()) {
		cerr << "Producers not found!" << endl;
		cin.get();
	}
	return lib_factories;
}

template <class BaseClass>
boost::shared_ptr<BaseClass> get_class (shared_library & lib, std::string class_name ) {
	map<string, factory<BaseClass> > lib_factories = get_factories<BaseClass>(lib);
	boost::shared_ptr<BaseClass> lib_class(lib_factories[class_name].create());
	return lib_class;
}



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

	ExtendedCharPtr CharPtr;
	CharPtr.data = new char[10];
	CharPtr.length = 10; 
	cout << "CharPtr created successfully \n";
	int generator_number = 1;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////Usage://////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//one way to create classes from dll - create all possible classes using factories, tested, works

	//map<string, factory<PublicProducerPrototype, int> > producer_factories = get_factories<PublicProducerPrototype, int>(simple_producer);
	//for (map<string, factory<PublicProducerPrototype, int> >::iterator it
	//	= producer_factories.begin();
	//	it != producer_factories.end(); ++it) {
	//		++generator_number;
	//		cout << "Creating Producers using factory: " << it->first << endl;
	//		boost::scoped_ptr<PublicProducerPrototype> current_producer(it->second.create(generator_number));
	//		cout << "Created data producer, " << 
	//			" Lets try it on data generation: " << endl;
	//		renderChar(current_producer->updateData(CharPtr));
	//}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//another way to create one class from dll by name having factories, tested, works

	//map<string, factory<PublicProducerPrototype, int> > producer_factories = get_factories<PublicProducerPrototype, int>(simple_producer);
	//boost::scoped_ptr<PublicProducerPrototype> producer(producer_factories["simpleProducer"].create(generator_number));
	//renderChar(producer->updateData(CharPtr));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//last way is to create a class having only int name (declared in realization)
	//its prototype interface class and that class constructor argument type and value we want to use
	//boost::shared_ptr<PublicProducerPrototype> producer ( get_class<PublicProducerPrototype, int>(simple_producer, "simpleProducer", generator_number));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	boost::shared_ptr<PublicProducerPrototype> producer ( get_class<PublicProducerPrototype, int>(simple_producer, "simpleProducer", generator_number));
	boost::shared_ptr<PublicRendererPrototype> renderer ( get_class<PublicRendererPrototype>(simple_renderer, "simpleRenderer"));

	renderer->renderCastedData(producer->updateData(CharPtr));

	cin.get();

}