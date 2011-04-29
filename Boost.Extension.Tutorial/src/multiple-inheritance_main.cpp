#include <iostream>
#include <string>
#include <map>

#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/shared_library.hpp>
#include <boost/extension/type_map.hpp>
#include <boost/extension/convenience.hpp>

//  See the FAQ for info about why the following is necessary
//  here, but usually isn't.

#include "headers-interfaces/vehicle.hpp"
#include "headers-interfaces/computer.hpp"
#include <boost/scoped_ptr.hpp>

#include "utilities.h"

using namespace std;

int main() {
  using namespace boost::extensions;
  //  Create the type_map object - it will hold all of the available
  //  constructors.
  type_map types;

  string library_path_to_Vehicle = add_prefix_and_suffix("lib-multiple-inheritance-Vehicle");

  string library_path_to_Car = add_prefix_and_suffix("lib-multiple-inheritance-Car");

  string library_path_to_Boat = add_prefix_and_suffix("lib-multiple-inheritance-Boat");

  string library_path_to_Plane = add_prefix_and_suffix("lib-multiple-inheritance-Plane");

  string library_path_to_Flying_Car = add_prefix_and_suffix("lib-multiple-inheritance-Flying-Car");

  string library_path_to_Computer = add_prefix_and_suffix("lib-multiple-inheritance-Computer");

  string library_path_to_Car_Of_The_Future = add_prefix_and_suffix("lib-multiple-inheritance-Car-Of-The-Future");

  //  Load the constructors and information into the factory_map.
  load_single_library(types, library_path_to_Vehicle);
  load_single_library(types, library_path_to_Car);
  load_single_library(types, library_path_to_Boat);
  load_single_library(types, library_path_to_Plane);
  load_single_library(types, library_path_to_Flying_Car);
  load_single_library(types, library_path_to_Computer);
  load_single_library(types, library_path_to_Car_Of_The_Future);

  //  Get a reference to the list of constructors.
  //  Note that the factories can be copied just fine - meaning that the 
  //  map of factories can be copied from the type_map object into a
  // different data structure, and the type_map can be destroyed.
  // Here, we just use the efficient map::swap function.
  cout << "\n>>>>>>>>>>>>\nComputers:\n>>>>>>>>>>>>>>>>>>>";
  map<string, factory<computer> >& computers(types.get());
  if (computers.empty()) {
    cout << "Error - no computers were found.";
    return 1;
  }
  
  for (map<string, factory<computer> >::iterator comp = 
       computers.begin(); comp != computers.end(); ++comp) {
    //  Using scoped_ptr to avoid needing delete. Using smart_ptrs is 
    //  recommended.
    //  Note that this has a zero argument constructor - currently constructors
    //  with up to six arguments can be used.
    boost::scoped_ptr<computer> computer_ptr(comp->second.create());
    cout << "\n--------\nLoaded the class described as: ";
    cout << comp->first;
    cout << "\n\nIt claims the following capabilities: ";
    cout << computer_ptr->list_capabilities() << endl;
  }
  cout << "\n\n";

  cout << "\n>>>>>>>>>>>>\nVehicles:\n>>>>>>>>>>>>>>>>>>>" << endl;
  map<string, factory<vehicle> >& vehicles(types.get());
  if (vehicles.empty()) {
    cout << "Error - no vehicles were found.";
    return 1;
  }
  for (map<string, factory<vehicle> >::iterator v = 
       vehicles.begin(); v != vehicles.end(); ++v) {
    //  Using auto_ptr to avoid needing delete. Using smart_ptrs is 
    //  recommended.
    //  Note that this has a zero argument constructor - currently constructors
    //  with up to six arguments can be used.
    auto_ptr<vehicle> vehicle_ptr(v->second.create());
    cout << "\n--------\nLoaded the class described as: ";
    cout << v->first;
    cout << "\n\nIt claims the following capabilities: ";
    cout << vehicle_ptr->list_capabilities() << endl;
  } 
  
  cout << "\n\n"; 
  cin.get();
  return 0;
}
