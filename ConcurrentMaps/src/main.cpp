#include <iostream>
#include "general_map_data_structure.h"
#include "general_map_data_structure_shared_locks.h"
#include "test_map_wraper_with_asio_based_thread_pool.h"

int main()
{
	int tests = 5;
	int tasks_n = 1000;
	std::cout << "Number of required tests: " << tests << std::endl << "Number of threads in each test: " << tasks_n << std::endl << "Wait for it..." << std::endl;

	std::cout << std::endl << "----" << std::endl << "Int tests" << std::endl << "----" << std::endl;

	for(int i = 1; i < tests+1; ++i)
	{
		std::cout << "Thread pool used - number of tasks != number of created threads in this test (number: " << i << ")" << std::endl;
		test_map_wraper_pooled<general_map_data_structure<int, int>, int, int > GeneralMapTest(tasks_n);
		GeneralMapTest.start_tests("int");
		GeneralMapTest.tests_end();
		std::cout << std::endl << "test complete" << std::endl <<  std::endl; 
	}

	for(int i = 1; i < tests+1; ++i)
	{
		std::cout << "Thread pool used - number of tasks != number of created threads in this test (number: " << i << ")" << std::endl;
		test_map_wraper_pooled<general_map_data_structure_shared_locks<int, int>, int, int > GeneralMapTest(tasks_n);
		GeneralMapTest.start_tests("int");
		GeneralMapTest.tests_end();
		std::cout << std::endl << "test complete" << std::endl <<  std::endl; 
	}
	std::cout << std::endl << "----" << std::endl << "String tests" << std::endl << "----" << std::endl;

	for(int i = 1; i < tests+1; ++i)
	{
		std::cout << "Thread pool used - number of tasks != number of created threads in this test (number: " << i << ")" << std::endl;
		test_map_wraper_pooled<general_map_data_structure<std::string, std::string>, std::string, std::string > GeneralMapTest(tasks_n);
		GeneralMapTest.start_tests("string");
		GeneralMapTest.tests_end();
		std::cout << std::endl << "test complete" << std::endl <<  std::endl; 
	}

	for(int i = 1; i < tests+1; ++i)
	{
		std::cout << "Thread pool used - number of tasks != number of created threads in this test (number: " << i << ")" << std::endl;
		test_map_wraper_pooled<general_map_data_structure_shared_locks<std::string, std::string>, std::string, std::string > GeneralMapTest(tasks_n);
		GeneralMapTest.start_tests("string");
		GeneralMapTest.tests_end();
		std::cout << std::endl << "test complete" << std::endl <<  std::endl; 
	}

	std::cout << std::endl  << "All tests complete" << std::endl;
	std::cin.get();
	return 0;
}