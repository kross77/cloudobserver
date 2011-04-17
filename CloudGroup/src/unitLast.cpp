#include <iostream>
#include <cstdlib>
#include <boost/extension/extension.hpp>
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

	void BOOST_EXTENSION_EXPORT_DECL renderCastedData(ExtendedCharPtr data) 
	{ 
		renderChar(data);
	}

};
#endif //_GETrenderer_h_
