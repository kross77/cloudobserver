#include <iostream>
#include <vector>

#include <boost/thread.hpp>

// parts of c++0x std
#include <boost/bind.hpp> 
#include <boost/function.hpp>

#ifndef _CoreEvents_h_
#define _CoreEvents_h_

using namespace std ;
template <typename DataType >
class CoreEvents{

	typedef boost::function<void(DataType)>   Function;
	typedef std::vector<Function>      FunctionSequence;
	typedef typename FunctionSequence::iterator FunctionIterator; 

public:
	DataType* dataElement;
	FunctionSequence funcs;
	boost::thread_group tg;

	CoreEvents()
	{
		dataElement = new DataType();
	}
	// Function for adding subscribers functions
	// use something like std::bind(&currentClassName::FunctionToAdd, this, std::placeholders::_1) to add function to vector
	void Add(Function f)
	{
		funcs.push_back(f);
	}

	// Cast data to subscribers and clean up given pointer
	//ToDo: One  will be solved when pool of pre-initialized objects will be developed 
	virtual void Cast(){

		for (FunctionIterator it(funcs.begin()); it != funcs.end(); ++it){
			DataType dataCopy = *dataElement;
			tg.create_thread(boost::bind(*it, dataCopy));
		}
	}

	// yep - you probably need to overrite this one 
	virtual DataType Get(){
		DataType dataCopy = *dataElement;
		return dataCopy;
	}

};
#endif // _CoreEvents_h_