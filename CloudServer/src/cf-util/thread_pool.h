#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <exception>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

#include "thread_group.h"
#include "timer.h"

class not_finished_on_time_exception: public std::exception { };

class thread_pool
{
public:
	thread_pool(int desired_thread_lifetime, bool useLog)
	{
		thread_pool_g(desired_thread_lifetime);
	}

	thread_pool(int desired_thread_lifetime)
	{
		thread_pool_g(desired_thread_lifetime);
	}

	void thread_pool_g(int desired_thread_lifetime)
	{
		time_limit = desired_thread_lifetime;

		work = new boost::asio::io_service::work(tasks);
		internal_work = new boost::asio::io_service::work(internal_tasks);
		int cores_number = boost::thread::hardware_concurrency(); 
		for (std::size_t i = 0; i < cores_number; ++i)
		{
			boost::shared_ptr<boost::thread> thread;
			thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&thread_pool::run, this, thread)));
			threads.add(thread);
		}

		for (std::size_t i = 0; i < cores_number; ++i)
		{
			boost::shared_ptr<boost::thread> internal_thread;
			internal_thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&thread_pool::internal_run, this, internal_thread)));
			internal_threads.add(internal_thread);
		}

	}

	~thread_pool()
	{
		tasks.stop();
		internal_tasks.stop();
		threads.join_all();
		internal_threads.join_all();

	}

	template <class task_return_t>
	void post(boost::shared_ptr<boost::packaged_task<task_return_t> > pt)
	{
		tasks.post(boost::bind(&thread_pool::pool_item<task_return_t>, this, pt));
	}

private:

	boost::asio::io_service tasks;
	boost::asio::io_service::work *work;
	thread_group threads;

	thread_group internal_threads;
	boost::asio::io_service internal_tasks;
	boost::asio::io_service::work *internal_work;

	int time_limit;

	void run(boost::shared_ptr<boost::thread> thread_ptr)
	{
		try
		{
			tasks.run();
		}		
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
			boost::shared_ptr<boost::thread> thread;
			thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&thread_pool::run, this, thread)));
			threads.add(thread);
			threads.remove(thread_ptr);
			return;
		}
	}

	void internal_run(boost::shared_ptr<boost::thread> internal_thread_ptr)
	{
		try
		{
			internal_tasks.run();
		}		
		catch(not_finished_on_time_exception &e)
		{
			internal_threads.remove(internal_thread_ptr);
			return;
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
	}

	template <class task_return_t>
	void pool_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt)
	{
		boost::shared_ptr < boost::packaged_task<void> > task (  new boost::packaged_task<void> ( boost::bind(&thread_pool::run_item<task_return_t>, this, pt)));
		boost::unique_future<void> fi= task->get_future();

		//internal_tasks.post( *task);
		internal_tasks.post(boost::bind(&thread_pool::run_item<task_return_t>, this, task));

		if(fi.timed_wait(boost::posix_time::milliseconds(time_limit)))
		{
			return;
		}
		else
		{
			boost::shared_ptr<boost::thread> thread;
			thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&thread_pool::internal_run, this, thread)));
			internal_threads.add(thread);
		}
	}

	template <class task_return_t>
	void run_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt)
	{
		timer t;
		t.restart();

		(*pt)();

		if (t.elapsed().total_milliseconds() > time_limit)
		{
			throw not_finished_on_time_exception(); //self kill
		}
	}
};

#endif // THREAD_POOL_H