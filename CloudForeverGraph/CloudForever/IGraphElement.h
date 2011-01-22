#ifndef _IGraphElement_h_
#define _IGraphElement_h_
// This code is my RFC on graph item prototype. 
// Class API use sample is also provided.
// This code compiles under VS with use of boost and is Qt compatible
#include <iostream>
#include <vector>

// Boost
#include <boost/thread.hpp>

using namespace std ;

class IGraphElement {

	// We should define prototype of functions that will be subscribers to our data
	typedef void FuncCharPtr(char*, int) ;

public:
	struct GetResultStructure
	{
		int length;
		char* ptr;
	};

	// Function for preparing class to work 
	virtual void Init(){}

	// initGet sets up a pointer holding a copy of pointer of data we want to return on Get() call
	void InitGet(char * pointerToUseInGetOperations, int pointerToUseInGetOperationsSize)
	{
		pointerToGet = pointerToUseInGetOperations;
		pointerToGetSize = pointerToUseInGetOperationsSize;
	}

	// Function for data update // word virtual makes it possible to overwrite it
	virtual void updateData(){}

	// Function for adding subscribers functions
	void Add(FuncCharPtr* f)
	{
		FuncVec.push_back(f);
	}

	void StartThread()
	{
		GraphWorker = boost::thread(&IGraphElement::Call, this);
	}

	// Returns pointer to copy of current graphItem processed data
	GetResultStructure Get()
	{
		boost::mutex::scoped_lock lock(GraphItemMutex);
		char * dataCopy = new char[pointerToGetSize];
		memcpy (dataCopy,pointerToGet,pointerToGetSize);
		lock.unlock();
		GraphItemMutexConditionVariable.notify_one();
		GetResultStructure result;
		result.ptr = dataCopy;
		result.length = pointerToGetSize;
		return result;
	}

	// Clean up for init
	void Clean()
	{
		GraphWorker.interrupt();
		GraphWorker.join();

		delete[] pointerToGet;
		pointerToGet = 0;

	}

private:

	// Char pointer to hold a copy of pointer of data we want to return on Get() call
	char* pointerToGet;
	int pointerToGetSize;

	// Cast data to subscribers and clean up given pointer
	void CastData(){
		for (size_t i = 0 ; i < FuncVec.size() ; i++){
			char * dataCopy = new char[pointerToGetSize];
			memcpy (dataCopy,pointerToGet,pointerToGetSize);
			FuncVec[i] (dataCopy, pointerToGetSize) ;}
	}

	// Cast given data to subscribers and clean up given pointer
	void CastData(char * data, int length){
		for(size_t i = 0 ; i < FuncVec.size(); i++){
			char* dataCopy = new char[length];
			memcpy(dataCopy, data, length);
			FuncVec[i](dataCopy, length);
		}
	}


	// Vector to hold subscribed functions
	vector<FuncCharPtr*> FuncVec ;

	// Private class mutex for enabling "Get" on function data
	mutable boost::mutex GraphItemMutex;
	boost::condition_variable GraphItemMutexConditionVariable;
	boost::thread GraphWorker;


	//Here is a main class thread function in infinit loop it calls for updateData function
	void Call()
	{
		try
		{
			for(;;){
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

#endif // _IGraphElement_h_