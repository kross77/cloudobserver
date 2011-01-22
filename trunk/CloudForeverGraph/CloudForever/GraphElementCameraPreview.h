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
	void Init(IGraphElement* ImageGenerator,  string WindowName, int width, int height, int sleepTime)
	{
		createPreviewWindow(WindowName, width, height);
		imageGenerator = ImageGenerator;
		SetSleepTime(sleepTime);
	}
	// we want to use some costume data update
	void updateData()
	{
		if(key != 1){
			OpenCVShowFrame(imageGenerator->Get().ptr);
		}
		else{
			Clean();
		}
	}

	void CleanAPI()
	{
		CleanUp();
	}
	IGraphElement* imageGenerator;
private:
	//
};
#endif // _GraphElementCameraPreviewer_h_