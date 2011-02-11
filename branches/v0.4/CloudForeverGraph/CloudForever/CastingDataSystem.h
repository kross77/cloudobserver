#include <iostream>
#include <vector>

#include <boost/thread.hpp>

// parts of c++0x std
#include <boost/bind.hpp> 
#include <boost/function.hpp>

#ifndef _CastingDataSystem_h_
#define _CastingDataSystem_h_

using namespace std ;
template <typename DataType >
class CastingDataSystem {

	typedef boost::function<void(DataType)>   Function;
	typedef std::vector<Function>      FunctionSequence;
	typedef typename FunctionSequence::iterator FunctionIterator; 

public:
	DataType* dataElement;
	FunctionSequence funcs;
	boost::thread_group tg;

	// Function for adding subscribers functions
	// use something like std::bind(&currentClassName::FunctionToAdd, this, std::placeholders::_1) to add function to vector
	void Add(Function f)
	{
		funcs.push_back(f);
	}

	// Cast data to subscribers and clean up given pointer
	virtual void Cast(){
		for (FunctionIterator it(funcs.begin()); it != funcs.end(); ++it){
			DataType dataCopy = *dataElement;
			tg.create_thread(boost::bind(*it, dataCopy));
		}
	}

};
#endif // _CastingDataSystem_h_