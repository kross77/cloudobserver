#ifndef TEST_MAP_WRAPER_WITH_ASIO_BASED_THREAD_POOL_H
#define TEST_MAP_WRAPER_WITH_ASIO_BASED_THREAD_POOL_H

#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/date_time.hpp>

#include "timer.h"

template <typename  map_wraper_t, typename  map_t_1, typename  map_t_2>
class general_test
{
public:

	general_test(int tasks_to_run)
	{
		n = tasks_to_run;
		wait = true;
		work = new boost::asio::io_service::work(io_service);
		int cores_number = boost::thread::hardware_concurrency(); 
		for (std::size_t i = 0; i < cores_number; ++i)
			threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
	}

	general_test(int tasks_to_run, int threads_number)
	{
		n = threads_number;
		wait = true;
		work = new boost::asio::io_service::work(io_service);
		for (std::size_t i = 0; i < threads_number; ++i)
			threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
	}

	~general_test()
	{
		io_service.stop();
		threads.join_all();
	}

	void start_tests(std::string test_types)
	{
		test_type = test_types;
		boost::upgrade_lock<boost::shared_mutex> lock(tests);
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

		boost::shared_lock<boost::shared_mutex> lock_r(results);

		for(int i=0; i<n; i++)
		{
			submit_test(i);
		}
		io_service.post(boost::bind(&general_test<map_wraper_t, map_t_1, map_t_2>::result, this));
		timerForCaptureFame.restart();
	}

	void tests_end()
	{
		while(wait)
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		}
	}
	
private:
	std::string test_type;
	int n;
	bool wait;
	boost::shared_mutex  tests;
	boost::shared_mutex  results;
	timer timerForCaptureFame;
	map_wraper_t Ds;
	boost::asio::io_service io_service;
	boost::asio::io_service::work *work;
	boost::thread_group threads;

	void submit_test( int test_number )
	{
		if (test_type == "int")
		{
			io_service.post(boost::bind(&general_test<map_wraper_t, map_t_1, map_t_2>::test_int, this, test_number));
		}
		else if (test_type == "string")
		{
			io_service.post(boost::bind(&general_test<map_wraper_t, map_t_1, map_t_2>::test_string, this, boost::lexical_cast<std::string>(test_number)));
		}
	}

	template< typename  t1, typename  t2>
	void test(t1 k1, t2 v1)
	{
		map_t_1 k = boost::lexical_cast<map_t_1>(k1);
		map_t_2 v = boost::lexical_cast<map_t_2>(v1);

		boost::shared_lock<boost::shared_mutex> lock_r(results);
		boost::shared_lock<boost::shared_mutex> lock(tests);

		Ds.put(k, v);
		if (Ds.containsKey(k))
		{
			Ds.get(k);
			Ds.get(k);
			Ds.get(k);
		}
		Ds.remove(k);
	}

	void test_int( int i)
	{
		test<int, int>(i, i);
	}

	void test_string( std::string s)
	{
		s += "abcdefghigklmnop";
		std::string r = "abcdefghigklmnop" + s;
		test<std::string, std::string>(s, r);
	}

	void result()
	{
		boost::upgrade_lock<boost::shared_mutex> lock(results);
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

		std::cout << "test duration: " << timerForCaptureFame.elapsed() << std::endl;
		wait = false;
	}
};

#endif // TEST_MAP_WRAPER_WITH_ASIO_BASED_THREAD_POOL_H