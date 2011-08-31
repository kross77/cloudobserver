#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

// Boost
#include <boost/function.hpp>

class synchronizer
{
public:
	virtual ~synchronizer() { }
	virtual void set_synchronization_callback(boost::function<void ()> synchronization_callback) = 0;
	virtual void set_synchronization_period(int synchronization_period) = 0;
	virtual void start() { }
	virtual void stop() { }
};

#endif // SYNCHRONIZER_H
