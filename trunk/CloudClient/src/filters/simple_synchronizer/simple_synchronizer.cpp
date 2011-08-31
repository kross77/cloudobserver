#include "simple_synchronizer.h"

void simple_synchronizer::set_synchronization_callback(boost::function<void ()> synchronization_callback)
{
	this->synchronization_callback = synchronization_callback;
}

void simple_synchronizer::set_synchronization_period(int synchronization_period)
{
	this->synchronization_period = boost::posix_time::milliseconds(synchronization_period);
}

void simple_synchronizer::start()
{
	this->synchronization_thread = boost::shared_ptr<boost::thread>(new boost::thread(&simple_synchronizer::synchronization_loop, this));
}

void simple_synchronizer::stop()
{
	this->synchronization_thread->interrupt();
}

void simple_synchronizer::synchronization_loop()
{
	timer time;
	while (true)
	{
		time.restart();
		this->synchronization_callback();

		boost::this_thread::sleep(this->synchronization_period - time.elapsed());
	}
}
