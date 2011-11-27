#ifndef THREAD_GROUP_H
#define THREAD_GROUP_H

#include <set>

#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/foreach.hpp>

/*!
* \brief Provides a thread group std::set based container.
* can be used in thread pools
* is thread safe but not throw safe.
*
*/
class thread_group
{
public:
	/*!
	 * \brief adds a thread into thread group
	 *
	 * \n FullName:  thread_group::add
	 * \n Access:    public  
	 *
	 * \param to_add boost::shared_ptr<boost::thread> 
	 * \return void 
	 *
	 */
	void add( boost::shared_ptr<boost::thread> to_add)
	{
		boost::mutex::scoped_lock lock(m);
		ds_.insert(to_add);
	}
	/*!
	 * \brief removes thread from thread group
	 *
	 * \n FullName:  thread_group::remove
	 * \n Access:    public  
	 *
	 * \param to_remove boost::shared_ptr<boost::thread> 
	 * \return void
	 *
	 */
	void remove( boost::shared_ptr<boost::thread> to_remove)
	{
		boost::mutex::scoped_lock lock(m);
		ds_.erase(to_remove);
	}

	/*!
	 * \brief returns current group size
	 *
	 * \n FullName:  thread_group::size
	 * \n Access:    public  
	 *
	 * \return int group size
	 *
	 */
	int size()
	{
		boost::mutex::scoped_lock lock(m);
		return ds_.size();
	}

	/*!
	 * \brief gives to all group threads some time and than kills them
	 *
	 * \n FullName:  thread_group::join_all
	 * \n Access:    public  
	 *
	 * \param interuption_time boost::posix_time::milliseconds time to geive to each thread  before interrupting it
	 * \return void 
	 *
	 */
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