#include <iostream>
#include <cstdlib>
#include "ExtendedCharPtr.h"

#ifndef _GETrenderer_h_
#define _GETrenderer_h_

using namespace std ;
// lets write simple API class
class  simpleRendererLibAPI // here we declare all lib functions with specific for our lib possibilities 
{
public:

	void renderChar(ExtendedCharPtr data) { // simple function of API
		cout << "Received char: ";
		for (int i = 0; i < data.length; i++)
			//cout << *data.data++;
			cout << data.data[i];
		cout << endl;
	}
	void DWOWWCG() 
	{
		cout << "Data was obtained when we called Get()" << endl; 
	}
	void DWCTU() 
	{
		cout << "Data casted to us because we subscribed with Add()" << endl; 
	}
};
// now lets write simple graph element based on that API class

#include "IGraphElement.h"

class  simpleRendererGraphElement : public IGraphElementBase, public simpleRendererLibAPI
{
public:
	CoreEvents<ExtendedCharPtr>* charGenerator;
	// we owerrite init
	void Init(CoreEvents<ExtendedCharPtr>* CharGenerator, int sleepTime)
	{
		charGenerator = CharGenerator;
		charGenerator->Add(boost::bind(&simpleRendererGraphElement::renderCastedData, this, _1)); 
		SetSleepTime(sleepTime);
	}
	void renderCastedData(ExtendedCharPtr data) //  our event system receives functions declared like void FuncCharPtr(char*, int) ;
	{ 
		DWCTU();
		renderChar(data);
	}
	// or we can grab data when we want
	void updateData()
	{
		DWOWWCG();	
		renderChar(charGenerator->Get());
	}

	void CleanAPI()
	{
	}

};
#endif //_GETrenderer_h_
