#include <iostream>
#include <cstdlib>
#include <boost/extension/extension.hpp>
#include "ExtendedCharPtr.h"

#ifndef _PublicRendererPrototype_h_
#define _PublicRendererPrototype_h_

using namespace std ;

class  PublicRendererPrototype
{

public:
	PublicRendererPrototype() {}
	virtual ~PublicRendererPrototype(void) {}

	virtual void renderCastedData(ExtendedCharPtr data) { 	}

};
#endif //_PublicRendererPrototype_h_
