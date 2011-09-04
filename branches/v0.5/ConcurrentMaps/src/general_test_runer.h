#include <iostream>
#include "general_map_data_structure.h"
#include "general_map_data_structure_shared_locks.h"
#include "general_test.h"

class general_test_runer
{
private:
	int tests;
	int tasks_n;
public:
	general_test_runer(int tests_number=5, int tasks_number=10000)
	{
	 tests = tests_number;
	 tasks_n = tasks_number;
	}

	void start()
	{
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

	std::cout << std::endl  << "General_test_runer tests complete" << std::endl;
	}
};