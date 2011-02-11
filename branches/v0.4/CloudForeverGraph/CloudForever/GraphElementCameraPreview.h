#include "ExtendedCharPtr.h"
#include "IGraphElement.h"
#include "APICameraPreviewer.h"

#ifndef _GraphElementCameraPreviewer_h_
#define _GraphElementCameraPreviewer_h_

//#include <iostream>
using namespace std ;
class GraphElementCameraPreviewer : public IGraphElementBase, public APICameraPreviewer
{
public:
	// we want costume init
	void Init(IGraphElement<ExtendedCharPtr>* ImageGenerator,  string WindowName, int width, int height, int sleepTime)
	{
		createPreviewWindow(WindowName, width, height);
		imageGenerator = ImageGenerator;
		SetSleepTime(sleepTime);
	}
	// we want to use some costume data update
	void updateData()
	{
		if(key != 'q'){
			OpenCVShowFrame(imageGenerator->Get().data);
		}
		else{
			Clean();
		}
	}

	void CleanAPI()
	{
		CleanUp();
	}
	IGraphElement<ExtendedCharPtr>* imageGenerator;
private:
	//
};
#endif // _GraphElementCameraPreviewer_h_