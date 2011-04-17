#include <iostream>
#include <cstdlib>
#include "ExtendedCharPtr.h"

#ifndef _GETrenderer_h_
#define _GETrenderer_h_

using namespace std ;

class  simpleRenderer
{
private: // API

	void renderChar(ExtendedCharPtr data) { 
		cout << "Received char: ";
		for (int i = 0; i < data.length; i++)
			//cout << *data.data++;
			cout << data.data[i];
		cout << endl;
	}

public:

	void renderCastedData(ExtendedCharPtr data) 
	{ 
		renderChar(data);
	}

};
#endif //_GETrenderer_h_
