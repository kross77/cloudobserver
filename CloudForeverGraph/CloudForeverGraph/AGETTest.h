#include "AGETgenerator.h"
#include "GETrenderer.h"

using namespace std;

class AdvancedGraphElementTutorialTest
{
public:
	void main()
	{
		AdvancedGeneratorGraphElement * generator = new AdvancedGeneratorGraphElement();
		simpleRendererGraphElement * rendererLC = new simpleRendererGraphElement();
		simpleRendererGraphElement * rendererNumbers = new simpleRendererGraphElement();
		simpleRendererGraphElement * rendererCapitals = new simpleRendererGraphElement();

		generator->Init(20,30,10, 50);

		rendererLC->Init((CoreEvents<ExtendedCharPtr>*) generator->GeneratorLC,1000/15);
		rendererNumbers->Init((CoreEvents<ExtendedCharPtr>*) generator->GeneratorNumbers,1000/15);
		rendererCapitals->Init((CoreEvents<ExtendedCharPtr>*) generator->GeneratorCapitals,1000/15);

		generator->StartThread();

		rendererLC->StartThread();
		rendererNumbers->StartThread();
		rendererCapitals->StartThread();

		boost::this_thread::sleep(boost::posix_time::milliseconds(10000));

		generator->Clean();	

		rendererLC->Clean();
		rendererNumbers->Clean();
		rendererCapitals->Clean();

		cout << "Success!" << endl;
		cin.get();
	}


};