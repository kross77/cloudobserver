#include <iostream>
#include <vector>

#include <boost/thread.hpp>
#include <boost/timer.hpp>

#ifndef _CoreItem_h_
#define _CoreItem_h_
class CoreItem{
public:
	boost::thread GraphWorker;
	mutable boost::mutex GraphItemMutex;
	boost::condition_variable GraphItemMutexConditionVariable;


};
#endif //_CoreItem_h_