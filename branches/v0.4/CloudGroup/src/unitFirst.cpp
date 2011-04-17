#include <iostream>
#include <cstdlib>
#include "ExtendedCharPtr.h"
#include <boost/extension/extension.hpp>

#ifndef _GETproducer_h_
#define _GETproducer_h_
using namespace std ;

class simpleProducer 
{
private: // API

	void initSimpleProducerLibAPI(int i) 
	{
		std::srand(i);
	}

	void genRandomFilledChar(char *s, int len) { 
		const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		s[len] = 0;
	}

	void genCharFilledWithCapitals(char *s, int len) {
		const char alphanum[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		s[len] = 0;
	}

	void genCharFilledWithNumbers(char *s, int len) {
		const char alphanum[] =
			"0123456789";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		s[len] = 0;
	}

	void genCharFilledWithLoverCase(char *s, int len) {
		const char alphanum[] =
			"abcdefghijklmnopqrstuvwxyz";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		s[len] = 0;
	}

	int generator;

public:

	void BOOST_EXTENSION_EXPORT_DECL Init(int generator)
	{
		initSimpleProducerLibAPI(0); 
		this->generator = generator;
	}

	void BOOST_EXTENSION_EXPORT_DECL updateData(ExtendedCharPtr localCharPtr)
	{
		switch ( generator ) {
			case 1 : 
				{genCharFilledWithNumbers(localCharPtr.data, localCharPtr.length); }
				break;
			case 2 : 
				{genCharFilledWithLoverCase(localCharPtr.data, localCharPtr.length); }
				break;
			case 3 : 
				{genCharFilledWithCapitals(localCharPtr.data, localCharPtr.length); }
				break;
			default : 
				{ genRandomFilledChar(localCharPtr.data, localCharPtr.length); }
		}
	}
};

#endif //_GETproducer_h_