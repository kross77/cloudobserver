#ifndef TIMER_H
#define TIMER_H

#include <boost/date_time.hpp>

class timer
{
public:
	timer() : start_time(boost::posix_time::microsec_clock::local_time()) { }

	void restart()
	{
		start_time = boost::posix_time::microsec_clock::local_time();
	}

	boost::posix_time::time_duration elapsed() const
	{
		return boost::posix_time::microsec_clock::local_time() - start_time;
	}
private:
	boost::posix_time::ptime start_time;
};

#endif // TIMER_H
