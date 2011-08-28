#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <exception>

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
			boost::packaged_task<void> task_w(boost::bind(&thread_pool::run, this, thread));
			thread = boost::shared_ptr<boost::thread>( new boost::thread(std::move(task_w)));
			threads.add(thread);
		}

		for (std::size_t i = 0; i < cores_number; ++i)
		{
			boost::shared_ptr<boost::thread> internal_thread;
			boost::packaged_task<void> internal_task_w(boost::bind(&thread_pool::internal_run, this, internal_thread));
			internal_thread = boost::shared_ptr<boost::thread>( new boost::thread(std::move(internal_task_w)));
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

	template <class task_return_t>
	void post(boost::shared_ptr<boost::packaged_task<task_return_t> > pt, boost::shared_future<task_return_t> fi)
	{
		std::cout <<  threads.size() <<  std::endl;
		tasks.post(boost::bind(&thread_pool::pool_item<task_return_t>, this, pt, fi));
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
			boost::packaged_task<void> ptt(boost::bind(&thread_pool::run, this, thread));
			thread = boost::shared_ptr<boost::thread>(new boost::thread(std::move(ptt)));
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
		boost::shared_future<task_return_t> fi= pt->get_future();

		internal_tasks.post(boost::bind(&thread_pool::run_item<task_return_t>, this, pt, fi));

		if(fi.timed_wait(boost::posix_time::milliseconds(time_limit)))
		{
			return;
		}
		else
		{
			boost::shared_ptr<boost::thread> thread;
			boost::packaged_task<void> task(boost::bind(&thread_pool::internal_run, this, thread));
			thread = boost::shared_ptr<boost::thread>(new boost::thread(std::move(task)));
			internal_threads.add(thread);
		}
	}

	template <class task_return_t>
	void pool_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt, boost::shared_future<task_return_t> fi)
	{
		internal_tasks.post(boost::bind(&thread_pool::run_item<task_return_t>, this, pt, fi));

		if(fi.timed_wait(boost::posix_time::milliseconds(time_limit)))
		{
			std::cout << "sucsess function returned: " << fi.get() << std::endl;
		}
		else
		{
			boost::shared_ptr<boost::thread> thread;
			boost::packaged_task<void> task(boost::bind(&thread_pool::internal_run, this, thread));
			thread = boost::shared_ptr<boost::thread>(new boost::thread(std::move(task)));
			internal_threads.add(thread);
		}
	}

	template <class task_return_t>
	void run_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt, boost::shared_future<task_return_t> fi)
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