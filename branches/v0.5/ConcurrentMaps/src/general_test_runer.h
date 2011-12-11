#include <iostream>
//Data structures
#include "general_map_data_structure.h"
#include "general_map_data_structure_shared_locks.h"
#include "unordered_map_data_structure.h"
#include "unordered_map_data_structure_shared_locks.h"
// Testing Utils
#include "general_test.h"

class general_test_runer
{
private:
	int tests;
	int tasks_n;
	int threads_n;
	log_util lu;
public:
	general_test_runer(int tests_number=5, int tasks_number=10000, int threads_number=0)
	{
	 tests = tests_number;
	 tasks_n = tasks_number;
	 if (threads_number == 0)
	 {
		 threads_n = boost::thread::hardware_concurrency(); 
	 }
	 else
	 {
		 threads_n = threads_number;
	 }
	}

	void start()
	{
	lu << "Each test task will put a value into container, get it 3 times, remove it from container." << log_util::endl;
	lu << "Number of required tests: " << tests << std::endl << "Number of tasks in each test: " << tasks_n << std::endl <<  "Number of threads in each test: " << threads_n << std::endl << "Wait for it..." << log_util::endl;

	lu << std::endl << "----" << std::endl << "Int tests" << std::endl << "----" << log_util::endl;
	// Boost Unordered
	//---------------------------------------------------------
	lu << std::endl << "testing unordered_map_data_structure_shared_locks:" << log_util::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<unordered_map_data_structure_shared_locks<int, int>, int, int > GeneralMapTest(tasks_n, threads_n);
		GeneralMapTest.start_tests("int");
		GeneralMapTest.tests_end();
	}
	lu << std::endl << "testing unordered_map_data_structure:" << log_util::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<unordered_map_data_structure<int, int>, int, int > GeneralMapTest(tasks_n, threads_n);
		GeneralMapTest.start_tests("int");
		GeneralMapTest.tests_end();
	}
	// STD Map
	//---------------------------
	lu << std::endl << "testing general_map_data_structure:" << log_util::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<general_map_data_structure<int, int>, int, int > GeneralMapTest(tasks_n, threads_n);
		GeneralMapTest.start_tests("int");
		GeneralMapTest.tests_end();
	}
	lu << std::endl << "testing general_map_data_structure_shared_locks:" << log_util::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<general_map_data_structure_shared_locks<int, int>, int, int > GeneralMapTest(tasks_n, threads_n);
		GeneralMapTest.start_tests("int");
		GeneralMapTest.tests_end();
	}

	lu << std::endl << "----" << std::endl << "String tests" << std::endl << "----" << log_util::endl;
	// Boost Unordered
	//---------------------------------------------------------
	lu << std::endl << "testing unordered_map_data_structure_shared_locks:" << log_util::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<unordered_map_data_structure_shared_locks<std::string, std::string>, std::string, std::string > GeneralMapTest(tasks_n, threads_n);
		GeneralMapTest.start_tests("string");
		GeneralMapTest.tests_end();
	}
	lu << std::endl << "testing unordered_map_data_structure:" << log_util::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<unordered_map_data_structure<std::string, std::string>, std::string, std::string > GeneralMapTest(tasks_n, threads_n);
		GeneralMapTest.start_tests("string");
		GeneralMapTest.tests_end();
	}
	
	// STD Map
	//---------------------------
	lu << std::endl << "testing general_map_data_structure:" << log_util::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<general_map_data_structure<std::string, std::string>, std::string, std::string > GeneralMapTest(tasks_n , threads_n);
		GeneralMapTest.start_tests("string");
		GeneralMapTest.tests_end();
	}
	lu << std::endl << "testing general_map_data_structure_shared_locks:" << log_util::endl;
	for(int i = 1; i < tests+1; ++i)
	{
		general_test<general_map_data_structure_shared_locks<std::string, std::string>, std::string, std::string > GeneralMapTest(tasks_n, threads_n);
		GeneralMapTest.start_tests("string");
		GeneralMapTest.tests_end();
	}

	lu << std::endl  << "General_test_runer tests complete" << log_util::endl;
	}
};