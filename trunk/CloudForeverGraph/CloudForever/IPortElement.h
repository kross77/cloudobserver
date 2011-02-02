#include "CastingDataSystem.h"

#include <boost/thread.hpp>

// parts of c++0x std
#include <boost/bind.hpp> 
#include <boost/function.hpp>

#ifndef _IPortElement_h_
#define _IPortElement_h_

using namespace std ;
template <typename DataType >
class IPortElement : public CastingDataSystem<DataType> {

private:
	mutable boost::mutex GraphItemMutex;
	boost::condition_variable GraphItemMutexConditionVariable;

public:

	// sets up a pointer holding a copy of pointer of data we want to return on Get() call
	void Set(DataType* DataElement)
	{
		boost::mutex::scoped_lock lock(GraphItemMutex);
		dataElement = DataElement;
		lock.unlock();
	}

	// Returns pointer to copy of current graphItem processed data
	DataType Get()
	{
		DataType dataCopy;
		boost::mutex::scoped_lock lock(GraphItemMutex);
		dataCopy = *dataElement;
		lock.unlock();
		GraphItemMutexConditionVariable.notify_one();
		return dataCopy;
	}

};
#endif // _IPortElement_h_