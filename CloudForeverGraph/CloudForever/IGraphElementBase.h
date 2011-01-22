#ifndef _IGraphElementBase_h_
#define _IGraphElementBase_h_
// This code is my RFC on graph item prototype. 
// Class API use sample is also provided.
// This code compiles under VS with use of boost and is Qt compatible
#include <iostream>
#include <vector>

// Boost
#include <boost/thread.hpp>

using namespace std ;

class IGraphElementBase {

public:


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

	// Returns pointer to copy of current graphItem processed data

	virtual void CleanAPI(){}
	// Clean up for init
	virtual void Clean()
	{
		GraphWorker.interrupt();
		GraphWorker.join();
		CleanAPI();

	}
	virtual void CastData();

	boost::thread GraphWorker;
	mutable boost::mutex GraphItemMutex;
	boost::condition_variable GraphItemMutexConditionVariable;
	int SleepTime;
private:

	//Here is a main class thread function in infinit loop it calls for updateData function
	void Call()
	{
		try
		{
			for(;;){
				boost::this_thread::sleep(boost::posix_time::milliseconds(SleepTime));
				boost::mutex::scoped_lock lock(GraphItemMutex);
				boost::this_thread::interruption_point() ;

				updateData();

				lock.unlock();
				CastData();
				GraphItemMutexConditionVariable.notify_one();
			}
		}
		catch (boost::thread_interrupted)
		{
			// Thread end
		}

	}  

};

#endif // _IGraphElementBase_h_