#include <iostream>
#include <map>

#include <boost/extension/factory.hpp>
#include <boost/extension/shared_library.hpp>
#include <boost/extension/type_map.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>

#include "headers-interfaces/animal.h"
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

int main() {
  using namespace boost::extensions;

  // In the Jamfile, shared libraries are set to have the same
  // prefix and extension, even on different operating systems.
  // This is for convenience in writing cross-platform code, but
  // is not required. All shared libraries are set to start with
  // "lib" and end with "extension".
  string library_path = "lib-simple-inheritance";
library_path +=extention;

  // Create shared_library object with the relative or absolute
  // path to the shared library.
  shared_library lib(library_path);

  // Attempt to open the shared library.
  if (!lib.open()) {
    cerr << "Library failed to open: " << library_path << endl;
    return 1;
  }

  // Use the shared_library::call to automatically call an
  // Extension-specific function in the shared library,
  // which takes a type_map.
  type_map types;
  if (!lib.call(types)) {
    cerr << "Function not found!" << endl;
    return 1;
  }

  // Retrieve a map of all animal factories taking an int and indexed
  // by a string from the type_map.
  map<string, factory<animal, int> >& factories(types.get());
  if (factories.empty()) {
    cerr << "Animals not found!" << endl;
    return 1;
  }

  // Create each animal.
  int age = 1;
  for (map<string, factory<animal, int> >::iterator it
         = factories.begin();
       it != factories.end(); ++it) {
    ++age;
    cout << "Creating an animal using factory: " << it->first << endl;
    boost::scoped_ptr<animal> current_animal(it->second.create(age));
    cout << "Created an animal: " << current_animal->get_name()
              << " Age: " << current_animal->get_age() << endl;
  }
  cin.get();
}
