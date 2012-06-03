#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <exception>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

#include "thread_group.h"
#include "timer.h"

/*!
 * \brief internal thread_pool exception
 *
 */
class not_finished_on_time_exception: public std::exception { };


/*!
 *  \addtogroup Utilities
 *  @{
 */

/*!
* \brief Provides a thread pool mechanism 
*
* Designed to safely manage tasks in multi threaded treads pool
* tasks are provided in form of boost::shared_ptr<boost::packaged_task<void> >
* Creates N slots for parallel execution (N ~ number of cores)
* Gives to each incoming task some time (defined in constructor) to execute and 
* if task does not execute in desired time swaps it into pool of long living threads
* where threads can execute all time they need.
* \n\n
* When it is needed: when you have threads that execute in some M time and you want them to execute no more than N at a time.
*
* \note timer class requires boost_date_time, boost_system and boost_thread library
* 
* \n\n  quick demo when we are not interested in task result:
* \include cf-util/thread_pool_no_returns_demo.cpp
* 
* \n\n  quick demo when we are indeed interested in task result and we use boost::futures:
* \include cf-util/thread_pool_returns_future_demo.cpp
* 
* \n\n  quick demo when we are showing multiple tasks submissions and tasks parallel execution:
* \include cf-util/thread_pool_parallel_load_demo.cpp
* 
*/
class thread_pool
{
public:
	/*!
	 * \brief Initializes a new instance of the thread_pool class 
	 *
	 * \n FullName:  thread_pool::thread_pool
	 * \n Access:    public  
	 *
	 * \param desired_thread_lifetime int time to wait for each new task to execute in milliseconds
	 * \param useLog bool save info on task execution into log
	 * \warning useLog is not implemented yet so this constructor works the same way as thread_pool::thread_pool(const int & desired_thread_lifetime) does
	 *
	 */
	thread_pool(int desired_thread_lifetime, bool useLog)
	{
		thread_pool_g(desired_thread_lifetime);
	}

	/*!
	 * \brief Initializes a new instance of the thread_pool class 
	 *
	 * \n FullName:  thread_pool::thread_pool
	 * \n Access:    public  
	 *
	 * \param desired_thread_lifetime int time to wait for each new task to execute in milliseconds
	 */
	thread_pool(const int & desired_thread_lifetime)
	{
		thread_pool_g(desired_thread_lifetime);
	}

	/*!
	 * \brief cleanes up after thread_pool
	 * 
	 * \n FullName:  thread_pool::~thread_pool
	 * \n Access:    public  
	 */
	~thread_pool()
	{
		tasks.stop();
		internal_tasks.stop();
		threads.join_all();
		internal_threads.join_all();

	}

	/*!
	 * \brief posts task into thread_pool
	 *
	 * \n FullName:  thread_pool::post
	 * \n Access:    public  
	 *
	 * \param pt boost::shared_ptr<boost::packaged_task<void> > your packaged_task
	 * \return void
	 * \note We force you to use boost::packaged_task<void> > here. You can always wrap your task into a wrapper task like so:
	 * \code
	 * template <class task_return_t>
	 * void run_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt)
	 *	{
	 *		(*pt)();
	 *	}
	 * //...
	 * 	boost::shared_ptr< boost::packaged_task<void> > wrapper_pt(new boost::packaged_task<void>(boost::bind(run_item<your_task_return_Type>, your_task)));
	 * 	thread_pool.post(wrapper_pt);
	 * \endcode
	 * \n
	 * \warning You shall not take any kinds of futures (nor boost::unique_future nor boost::shared_future) from the end task you send into thread_pool (take futures from wrapped task) \n
	 * \warning boost::shared_future does not work on Linux
	 */
	void post(boost::shared_ptr<boost::packaged_task<void> > pt)
	{
		tasks.post(boost::bind(&thread_pool::pool_item<void>, this, pt));
	}

private:

	boost::asio::io_service tasks;
	boost::asio::io_service::work *work;
	thread_group threads;

	thread_group internal_threads;
	boost::asio::io_service internal_tasks;
	boost::asio::io_service::work *internal_work;

	int time_limit;

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

		boost::shared_ptr<boost::promise<bool> > started(new boost::promise<bool>());
		boost::unique_future<bool> has_started = started->get_future();

		internal_tasks.post(boost::bind(&thread_pool::run_item<task_return_t>, this, task, started));

		has_started.wait();
	
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
	void run_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt, boost::shared_ptr<boost::promise<bool> > started)
	{
		started->set_value(true);

		run_item<task_return_t>(pt);
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
/*! @} */
#endif // THREAD_POOL_H