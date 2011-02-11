#include "GETproducer.h"
#include "GETrenderer.h"

using namespace std;

class GraphElementTutorialTest
{
public:
	void main()
	{
		simpleProducerGraphElement * generator = new simpleProducerGraphElement();
		simpleRendererGraphElement * renderer = new simpleRendererGraphElement();

		generator->Init(20, 50);
		renderer->Init((IGraphElement<ExtendedCharPtr>*) generator,1000/15);

		generator->StartThread();
		renderer->StartThread();

		boost::this_thread::sleep(boost::posix_time::milliseconds(10000));

		generator->Clean();	
		renderer->Clean();

		cout << "Success!" << endl;
		cin.get();
	}


};