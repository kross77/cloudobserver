#ifndef TIMER_H
#define TIMER_H

#include <boost/asio.hpp>

#include <boost/date_time.hpp>

class timer 
{ 
public: 
	timer() : start_time_(boost::posix_time::microsec_clock::local_time()) {} 
	
	void restart() 
	{
		start_time_ = boost::posix_time::microsec_clock::local_time();
	} 

	boost::posix_time::time_duration elapsed() const 
	{
		return boost::posix_time::microsec_clock::local_time() - start_time_;
	} 
private: 
	boost::posix_time::ptime start_time_; 
};

#endif // TIMER_H