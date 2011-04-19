#include <iostream>
#include "ExtendedCharPtr.h"

#ifndef _PublicProducerPrototype_h_
#define _PublicProducerPrototype_h_

using namespace std ;

class PublicProducerPrototype 
{
protected:
	int _generator;

public:

	PublicProducerPrototype(int generator) : _generator(generator) {}
	~PublicProducerPrototype(void) {}

	virtual ExtendedCharPtr updateData(ExtendedCharPtr localCharPtr){ return localCharPtr;}
	
};

#endif //_PublicProducerPrototype_h_