#include "ExtendedCharPtr.h"
#include "IGraphElement.h"
#include "APICamera.h"


#ifndef _GraphElementCamera_h_
#define _GraphElementCamera_h_

//#include <iostream>
using namespace std ;
class GraphElementCamera : public IGraphElement<ExtendedCharPtr>  , public APICamera
{
public:
	// we want costume init
	void Init(char * buffer, int width, int height, int captureFrameRate, int bufferSize, int sleepTime)
	{

		localCharPtr.data = buffer;
		localCharPtr.length = bufferSize;
		initOpenCV(width, height, captureFrameRate);
		InitGet(&localCharPtr); // we need to set this for our subscribers to get correct data
		SetSleepTime(sleepTime);
	}
	// we want to use some costume data update
	void updateData()
	{
		CaptureFrame(localCharPtr.data);
	}

	void CleanAPI()
	{
		closeOpenCV();
		//delete[] bufferRef;
	}
private:
	// Private data object we use in "call" public class function
	ExtendedCharPtr localCharPtr;

};
#endif // _GraphElementCamera_h_