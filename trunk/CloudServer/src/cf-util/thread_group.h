#ifndef THREAD_GROUP_H
#define THREAD_GROUP_H

#include <set>

#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/foreach.hpp>

class thread_group
{
public:
	void add( boost::shared_ptr<boost::thread> to_add)
	{
		boost::mutex::scoped_lock lock(m);
		ds_.insert(to_add);
	}
	void remove( boost::shared_ptr<boost::thread> to_remove)
	{
		boost::mutex::scoped_lock lock(m);
		ds_.erase(to_remove);
	}

	int size()
	{
		boost::mutex::scoped_lock lock(m);
		return ds_.size();
	}

	void join_all(boost::posix_time::milliseconds interuption_time=boost::posix_time::milliseconds(1000))
	{
		boost::mutex::scoped_lock lock(m);
		BOOST_FOREACH(boost::shared_ptr<boost::thread> t, ds_)
		{
			boost::thread interrupter(boost::bind(&thread_group::interupt_thread, this, t, interuption_time));
		}
		boost::upgrade_lock<boost::shared_mutex> lock_k(killer);
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock_k);
	}

private:
	std::set< boost::shared_ptr<boost::thread> > ds_;
	mutable boost::mutex m;
	boost::shared_mutex  killer;
	void interupt_thread(boost::shared_ptr<boost::thread> t, boost::posix_time::milliseconds interuption_time)
	{
		boost::shared_lock<boost::shared_mutex> lock(killer);
		try
		{
			if(!t->timed_join(interuption_time))
				t->interrupt();

		}
		catch(std::exception &e)
		{
		}
	}
};

#endif // THREAD_GROUP_H