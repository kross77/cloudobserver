#include <iostream>
#include <map>

#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

#include "ExtendedCharPtr.h"

#include "PublicRendererPrototype.h"

#ifndef _simpleRenderer_h_
#define _simpleRenderer_h_

using namespace std ;

class  simpleRenderer : public PublicRendererPrototype
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

	virtual void  renderCastedData(ExtendedCharPtr data) 
	{ 
		renderChar(data);
	}

};

BOOST_EXTENSION_TYPE_MAP_FUNCTION {
	using namespace boost::extensions;
	std::map<std::string, factory<PublicRendererPrototype, void> >&
		Renderer_factories(types.get());
	Renderer_factories["simpleRenderer"].set<simpleRenderer>();
}

#endif //_simpleRenderer_h_
