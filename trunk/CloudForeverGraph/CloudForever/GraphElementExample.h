#ifndef _GraphElementExample_h_
#define _GraphElementExample_h_
#include "IGraphElement.h"
#include "APIExample.h"
#include <iostream>
using namespace std ;
class GraphElementExample : public IGraphElement, public APIExample
{
public:
	// we want costume init
	void Init()
	{
		cout << "GraphElementExample override of init" << endl;
		sample = new char[5000];
		InitGet(sample, 5000); // we need to set this for our subscribers to get correct data
		SetSleepTime(100);
	}
	// we want to use some costume data update
	void updateData()
	{
		generateNewData();
	}
private:
	// Private data object we use in "call" public class function
	char* sample;

};
#endif // _GraphElementExample_h_