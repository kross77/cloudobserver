#include <iostream>
#include <cstdlib>

#ifndef _GETproducer_h_
#define _GETproducer_h_
using namespace std ;
// lets write simple API class
class simpleProducerLibAPI // here we declare all lib functions with specific for our lib possibilities 
{
public:
	void initSimpleProducerLibAPI(int i) // simple API init
	{
		std::srand(i);
	}

	void genRandomFilledChar(char *s, int len) { // simple function of API
		const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		s[len] = 0;
	}
	void genCharFilledWithCapitals(char *s, int len) { // simple function of API
		const char alphanum[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		s[len] = 0;
	}
	void genCharFilledWithNumbers(char *s, int len) { // simple function of API
		const char alphanum[] =
			"0123456789";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		s[len] = 0;
	}
	void genCharFilledWithLoverCase(char *s, int len) { // simple function of API
		const char alphanum[] =
			"abcdefghijklmnopqrstuvwxyz";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		s[len] = 0;
	}
};

// now lets write simple graph element based on that API class
// we will use our costume ExtendedCharPtr data type which consists of pointer to char buffer and its length
#include "ExtendedCharPtr.h"
#include "IGraphElement.h"

class  simpleProducerGraphElement : public IGraphElement<ExtendedCharPtr>, public simpleProducerLibAPI
{
private:
	// Private data object we use in "updateData" public class function
	ExtendedCharPtr localCharPtr;
public:
	// we want costume init for our GraphElement
	void Init(int Size, int sleepTime)
	{
		localCharPtr.data = new char[Size]; // we connect a buffer from real world to our local buffer
		localCharPtr.length = Size; 
		initSimpleProducerLibAPI(0); // we call our API inits
		InitGet(&localCharPtr); // we need to set this for our subscribers to get correct data
		SetSleepTime(sleepTime); // we declare how much time a thread will sleep before next cycle
	}
	// we want to use some costume data update, we overwrite updateData. 
	void updateData()
	{
		genRandomFilledChar(localCharPtr.data, localCharPtr.length); // use API function to update data
	}

	void CleanAPI()
	{
		//	delete localCharPtr;
		// here we do not have to clean anything but overwrite of this function would be called on graph item clean call.
	}

};
#endif //_GETproducer_h_