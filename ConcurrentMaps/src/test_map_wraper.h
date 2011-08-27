#ifndef TEST_MAP_WRAPER_H
#define TEST_MAP_WRAPER_H

#include <iostream>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/date_time.hpp>

#include "timer.h"

template <class map_wraper_t>
class test_map_wraper
{
public:

	test_map_wraper(int threads_number)
	{
		n = threads_number;
		wait = true;
	}

	void start_tests()
	{

		boost::upgrade_lock<boost::shared_mutex> lock(tests);
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

		boost::shared_lock<boost::shared_mutex> lock_r(results);

		for(int i=0; i<n; i++)
		{
			boost::thread worker(&test_map_wraper::test, this, i);
		}
		boost::thread worker_r(&test_map_wraper::result, this);
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
	int n;
	bool wait;
	boost::shared_mutex  tests;
	boost::shared_mutex  results;
	boost::random::mt19937 rng;
	timer timerForCaptureFame;
	map_wraper_t Ds;

	void test( int i)
	{
		boost::shared_lock<boost::shared_mutex> lock_r(results);
		boost::shared_lock<boost::shared_mutex> lock(tests);
		Ds.put(i, 0);
		if (Ds.containsKey(i))
		{
			Ds.get(i);
		}
		Ds.remove(i);
	}

	void result()
	{
		boost::upgrade_lock<boost::shared_mutex> lock(results);
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

		std::cout <<  std::endl << "test of " << Ds.name() << " complite;" << std::endl << "test performed on " << n << " items" << std::endl << "test duration: " << timerForCaptureFame.elapsed() << std::endl;
		wait = false;
	}
};

#endif // TEST_MAP_WRAPER_H