#include "IGraphElementBase.h"
#include "CoreEvents.h"

// parts of c++0x std
#include <boost/bind.hpp> 
#include <boost/function.hpp>

#ifndef _IGraphElement_h_
#define _IGraphElement_h_

using namespace std ;
template <typename DataType >
class IGraphElement : public IGraphElementBase, public CoreEvents<DataType> {

public:

	// initGet sets up a pointer holding a copy of pointer of data we want to return on Get() call
	void InitGet(DataType* DataElement)
	{
		dataElement = DataElement;
	}
	virtual void CastData()
	{
		Cast();
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

	void Clean()
	{
		GraphWorker.interrupt();
		GraphWorker.join();
		CleanAPI();
	}

};
#endif // _IGraphElement_h_