#include <iostream>
#include "general_map_data_structure.h"
#include "general_map_data_structure_shared_locks.h"
#include "general_test.h"

int main()
{
	int tests = 5;
	int tasks_n = 10000;
	std::cout << "Number of required tests: " << tests << std::endl << "Number of threads in each test: " << tasks_n << std::endl << "Wait for it..." << std::endl;

	std::cout << std::endl << "----" << std::endl << "Int tests" << std::endl << "----" << std::endl;

	std::cout << std::endl << "testing general_map_data_structure:" << std::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<general_map_data_structure<int, int>, int, int > GeneralMapTest(tasks_n);
		GeneralMapTest.start_tests("int");
		GeneralMapTest.tests_end();
	}
	std::cout << std::endl << "testing general_map_data_structure_shared_locks:" << std::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<general_map_data_structure_shared_locks<int, int>, int, int > GeneralMapTest(tasks_n);
		GeneralMapTest.start_tests("int");
		GeneralMapTest.tests_end();
	}

	std::cout << std::endl << "----" << std::endl << "String tests" << std::endl << "----" << std::endl;

	std::cout << std::endl << "testing general_map_data_structure:" << std::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<general_map_data_structure<std::string, std::string>, std::string, std::string > GeneralMapTest(tasks_n);
		GeneralMapTest.start_tests("string");
		GeneralMapTest.tests_end();
	}
	std::cout << std::endl << "testing general_map_data_structure_shared_locks:" << std::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<general_map_data_structure_shared_locks<std::string, std::string>, std::string, std::string > GeneralMapTest(tasks_n);
		GeneralMapTest.start_tests("string");
		GeneralMapTest.tests_end();
	}

	std::cout << std::endl  << "All tests complete" << std::endl;
	std::cin.get();
	return 0;
}