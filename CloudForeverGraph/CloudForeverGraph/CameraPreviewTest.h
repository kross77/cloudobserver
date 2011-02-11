#include <iostream>
#include "GraphElementCamera.h"
#include "GraphElementCameraPreview.h"

using namespace std;

class CameraPreviewTest
{
public:
	void main()
	{
		int w = 320;
		int h = 240;
		char buffer[230401]; // buff size == w*h*3
		string WindowName = "cam 1"; 

		GraphElementCamera * camera = new GraphElementCamera();
		GraphElementCameraPreviewer * prev = new GraphElementCameraPreviewer();

		camera->Init(buffer, w, h, 15, 230400, 1000/15);
		camera->StartThread();

		prev->Init((IGraphElement<ExtendedCharPtr>*) camera , WindowName, w, h, 1000/15);
		prev->StartThread();

		boost::this_thread::sleep(boost::posix_time::milliseconds(10000));

		prev->Clean();	
		cout << "prev Success!" << endl;
		camera->Clean();

		cout << "Success!" << endl;
		cin.get();
	}


};