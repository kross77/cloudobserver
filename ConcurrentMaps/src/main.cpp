#include <iostream>
#include "general_map_data_structure.h"
#include "general_map_data_structure_shared_locks.h"
#include "test_map_wraper.h"
#include "test_map_wraper_with_asio_based_thread_pool.h"

int main()
{
	int threads_n = 1000;
	int tests = 5;

	std::cout << "Number of required tests: " << tests << std::endl << "Number of threads in each test: " << threads_n << std::endl << "Wait for it..." << std::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		std::cout << "number of tasks == number of created threads in this test (number: " << i << ")" << std::endl;
		test_map_wraper<general_map_data_structure> GeneralMapTest(threads_n);
		GeneralMapTest.start_tests();
		GeneralMapTest.tests_end();
		std::cout << "test complete" << std::endl <<  std::endl; 
	}

	for(int i = 1; i < tests+1; ++i)
	{
		std::cout << "Thread pool used - number of tasks != number of created threads in this test (number: " << i << ")" << std::endl;
		test_map_wraper_pooled<general_map_data_structure> GeneralMapTest(threads_n);
		GeneralMapTest.start_tests();
		GeneralMapTest.tests_end();
		std::cout << std::endl << "test complete" << std::endl <<  std::endl; 
	}

	for(int i = 1; i < tests+1; ++i)
	{
		std::cout << "number of tasks == number of created threads in this test (number: " << i << ")" << std::endl;
		test_map_wraper<general_map_data_structure_shared_locks> GeneralMapTest(threads_n);
		GeneralMapTest.start_tests();
		GeneralMapTest.tests_end();
		std::cout << "test complete" << std::endl <<  std::endl; 
	}

	for(int i = 1; i < tests+1; ++i)
	{
		std::cout << "Thread pool used - number of tasks != number of created threads in this test (number: " << i << ")" << std::endl;
		test_map_wraper_pooled<general_map_data_structure_shared_locks> GeneralMapTest(threads_n);
		GeneralMapTest.start_tests();
		GeneralMapTest.tests_end();
		std::cout << std::endl << "test complete" << std::endl <<  std::endl; 
	}

	std::cout << std::endl  << "All tests complete" << std::endl;
	std::cin.get();
	return 0;
}