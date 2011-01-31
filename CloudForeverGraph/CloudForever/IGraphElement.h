#include "IGraphElementBase.h"

// parts of c++0x std
#include <boost/bind.hpp> 
#include <boost/function.hpp>

#ifndef _IGraphElement_h_
#define _IGraphElement_h_

using namespace std ;
template <typename DataType >
class IGraphElement : public IGraphElementBase{

	typedef boost::function<void(DataType)>   Function;
	typedef std::vector<Function>      FunctionSequence;
    typedef typename FunctionSequence::iterator FunctionIterator; 

private:
	DataType* dataElement;
	FunctionSequence funcs;

public:

	// initGet sets up a pointer holding a copy of pointer of data we want to return on Get() call
	void InitGet(DataType* DataElement)
	{
		dataElement = DataElement;
	}

	// Function for adding subscribers functions
	// use something like std::bind(&currentClassName::FunctionToAdd, this, std::placeholders::_1) to add function to vector
	void Add(Function f)
	{
		funcs.push_back(f);
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

	void Clean()
	{
		GraphWorker.interrupt();
		GraphWorker.join();
		CleanAPI();
		//delete[] dataElement;
	}

	// Cast data to subscribers and clean up given pointer
	virtual void CastData(){
		for (FunctionIterator it(funcs.begin()); it != funcs.end(); ++it){
			DataType dataCopy;
			dataCopy = *dataElement;
			(*it)(dataCopy);
		}
	}

	// Cast given data to subscribers and clean up given pointer
	/*void CastData(DataType data){
		for (FunctionIterator it(funcs.begin()); it != funcs.end(); ++it){
			DataType dataCopy;
			dataCopy = data;
			(*it)(dataCopy);
		}
	}*/

};
#endif // _IGraphElement_h_