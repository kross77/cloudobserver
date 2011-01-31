#include <iostream>
#include <vector>

#include <boost/thread.hpp>
#include <boost/timer.hpp>

#ifndef _IGraphElementBase_h_
#define _IGraphElementBase_h_
#pragma once

using namespace std ;

class IGraphElementBase {

public:
	boost::timer ElementTimer;
	double spentTime;
	boost::thread GraphWorker;
	mutable boost::mutex GraphItemMutex;
	boost::condition_variable GraphItemMutexConditionVariable;
	int SleepTime;

	// Function for preparing class to work 
	virtual void Init(){ SetSleepTime(1);}

	void SetSleepTime(int timeMS)
	{
		SleepTime = timeMS;
	}

	// Function for data update // word virtual makes it possible to overwrite it
	virtual void updateData(){}


	void StartThread()
	{
		GraphWorker = boost::thread(&IGraphElementBase::Call, this);
	}

	virtual void CleanAPI(){}

	virtual void Clean()
	{
		GraphWorker.interrupt();
		GraphWorker.join();
		CleanAPI();

	}
	virtual void CastData(){}

	//Here is a main class thread function in infinite loop it calls for updateData function
	void Call()
	{
		try
		{
			for(;;){

				ElementTimer.restart();
			
				boost::mutex::scoped_lock lock(GraphItemMutex);
				boost::this_thread::interruption_point() ;

				updateData();

				lock.unlock();
				CastData();

				GraphItemMutexConditionVariable.notify_one();
				spentTime = ElementTimer.elapsed();
				if(spentTime < SleepTime){
					boost::this_thread::sleep(boost::posix_time::milliseconds(SleepTime - spentTime));
				}
			}
		}
		catch (boost::thread_interrupted)
		{
			// Thread end
		}
	}  
};

#endif // _IGraphElementBase_h_