#ifndef TIMER_H
#define TIMER_H

#include <boost/date_time.hpp>

class timer
{
public:
	timer();
	void restart();
	boost::posix_time::time_duration elapsed() const;
private:
	boost::posix_time::ptime start_time;
};

#endif // TIMER_H
