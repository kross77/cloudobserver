#include "CoreEvents.h"
#include "CoreItem.h"
#include <boost/thread.hpp>

// parts of c++0x std
#include <boost/bind.hpp> 
#include <boost/function.hpp>

#ifndef _IPortElement_h_
#define _IPortElement_h_

using namespace std ;
template <typename DataType >
class IPortElement : public CoreEvents<DataType>, public CoreItem {

public:

	// sets up a pointer holding a copy of pointer of data we want to return on Get() call
	void Set(DataType * DataElement)
	{
		boost::mutex::scoped_lock lock(GraphItemMutex);
		*dataElement = *DataElement;
		Cast();
		lock.unlock();
		GraphItemMutexConditionVariable.notify_one();
	}

	// Returns pointer to copy of current graphItem processed data
	virtual DataType Get()
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