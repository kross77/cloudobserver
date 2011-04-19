#include <iostream>
#include <map>

#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

#include "ExtendedCharPtr.h"
#include "PublicProducerPrototype.h"

#ifndef _simpleProducer_h_
#define _simpleProducer_h_

using namespace std ;

class simpleProducer : public PublicProducerPrototype
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

		//s[len] = 0;
	}

	void genCharFilledWithCapitals(char *s, int len) {
		const char alphanum[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		//s[len] = 0;
	}

	void genCharFilledWithNumbers(char *s, int len) {
		const char alphanum[] =
			"0123456789";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		//s[len] = 0;
	}

	void genCharFilledWithLoverCase(char *s, int len) {
		const char alphanum[] =
			"abcdefghijklmnopqrstuvwxyz";
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		//s[len] = 0;
	}



public:

	simpleProducer(int generator) : PublicProducerPrototype(generator)
	{
		initSimpleProducerLibAPI(0); 
	}

virtual	ExtendedCharPtr updateData(ExtendedCharPtr localCharPtr)
	{
		switch ( _generator ) {
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
		return localCharPtr;
	}
};

BOOST_EXTENSION_TYPE_MAP_FUNCTION {
	using namespace boost::extensions;
	std::map<std::string, factory<PublicProducerPrototype, int> >&
		Producer_factories(types.get());
	Producer_factories["simpleProducer factory"].set<simpleProducer>();
}
#endif //_simpleProducer_h_