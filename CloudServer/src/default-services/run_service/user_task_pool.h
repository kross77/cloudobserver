#ifndef USER_TASK_POOL
#define USER_TASK_POOL
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <iterator>
#include <math.h>

//Boost
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex.hpp>
#include <boost/progress.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/stream.hpp>


// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

//SQLite
#include <sqlite3pp.h>

//CF-UTIL
#include <general_utils.h>
#include <http_utils.h>
#include <timer.h>
#include <fs_utils.h>
#include <log_util.h>
#include <thread_group.h>

//SERVICE INTERFACE
#include <http_service.hpp>

// Boost Process
#include <boost/process.hpp>

class user_task_pool{
public:
	std::string user_name;
	boost::asio::io_service tasks;
	boost::asio::io_service::work *work;
	thread_group threads;
	run_service * parent;

	user_task_pool(int create_threads, run_service * parent, std::string user_name): user_name(user_name), parent(parent)
	{
		work = new boost::asio::io_service::work(tasks);
		for (std::size_t i = 0; i < create_threads; ++i)
		{
			boost::shared_ptr<boost::thread> thread;
			thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&user_task_pool::run, this, thread)));
			threads.add(thread);
		}
	}

	void post(boost::shared_ptr<boost::packaged_task<void> > pt, std::string tid)
	{
		tasks.post(boost::bind(&user_task_pool::pool_item<void>, this, pt, tid, user_name));
	}

private:
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
			thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&user_task_pool::run, this, thread)));
			threads.add(thread);
			threads.remove(thread_ptr);
			return;
		}
	}

	template <class task_return_t>
	void pool_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt, std::string tid, std::string user_name)
	{
		boost::shared_ptr < boost::packaged_task<void> > task (  new boost::packaged_task<void> ( boost::bind(&run_service::run_item<task_return_t>, parent, pt)));
		boost::unique_future<void> fi= task->get_future();

		boost::shared_ptr<boost::promise<boost::thread::id> > started(new boost::promise<boost::thread::id>());
		boost::unique_future<boost::thread::id> has_started = started->get_future();

		if(parent->db->get_if_is_canceled(user_name, tid)){
			parent->remove_task(tid);	
			return;
		}

		parent->internal_tasks.post(boost::bind(&run_service::run_item<task_return_t>, parent, task, started));

		has_started.wait();
		if(has_started.has_exception())
			return;

		boost::thread::id id = has_started.get();

		while( (!(fi.has_value())) && (!(fi.has_exception())) ){
			fi.timed_wait(boost::posix_time::milliseconds(100));
			if(parent->db->get_if_is_canceled(user_name, tid))
			{
				boost::shared_ptr<boost::thread> internal_thread;
				internal_thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&run_service::internal_run, parent, internal_thread)));
				parent->internal_threads.add(internal_thread);
				parent->internal_threads.remove(id)->interrupt();
				parent->remove_task(tid);
			}
		}
	}
};

#endif //USER_TASK_POOL