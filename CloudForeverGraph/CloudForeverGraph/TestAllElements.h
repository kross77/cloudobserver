#include "CameraPreviewTest.h"
#include "GETTest.h"
#include "AGETTest.h"

using namespace std;

class TestAllElements
{
public:
	void main()
	{
		cout << "Camera Elements Test" << endl;
		CameraPreviewTest cpt;
		cpt.main();
		cout << "Graph Elements Tutorial Test" << endl;
		GraphElementTutorialTest gett;
		gett.main();
		cout << "Advanced Graph Elements Tutorial Test" << endl;
		AdvancedGraphElementTutorialTest agett;
		agett.main();
		cout << "All graph elements passed test successfully" << endl;
		cin.get();
	}


};