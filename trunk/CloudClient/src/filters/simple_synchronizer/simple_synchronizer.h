#ifndef SIMPLE_SYNCHRONIZER_H
#define SIMPLE_SYNCHRONIZER_H

// Boost
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "../../utils/synchronizer/synchronizer.h"
#include "../../utils/timer/timer.h"

class simple_synchronizer: public synchronizer
{
public:
	virtual void set_synchronization_callback(boost::function<void ()> synchronization_callback);
	virtual void set_synchronization_period(int synchronization_period);
	virtual void start();
	virtual void stop();
private:
	void synchronization_loop();

	boost::posix_time::time_duration synchronization_period;
	boost::function<void ()> synchronization_callback;

	boost::shared_ptr<boost::thread> synchronization_thread;
};

#endif // SIMPLE_SYNCHRONIZER_H
