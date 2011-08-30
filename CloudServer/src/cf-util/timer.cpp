#include "timer.h"

timer::timer() : start_time(boost::posix_time::microsec_clock::local_time()) { }

void timer::restart()
{
	start_time = boost::posix_time::microsec_clock::local_time();
}

boost::posix_time::time_duration timer::elapsed() const
{
	return boost::posix_time::microsec_clock::local_time() - start_time;
}
