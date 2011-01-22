#ifndef _GraphElementCamera_h_
#define _GraphElementCamera_h_
#include "IGraphElement.h"
#include "APICamera.h"
#include <iostream>
using namespace std ;
class GraphElementCamera : public IGraphElement, public APICamera
{
public:
	// we want costume init
	void Init(char * buffer, int width, int height, int captureFrameRate, int bufferSize, int sleepTime)
	{
		bufferRef = buffer;
		initOpenCV(width, height, captureFrameRate);
		InitGet(bufferRef, bufferSize); // we need to set this for our subscribers to get correct data
		SetSleepTime(sleepTime);
	}
	// we want to use some costume data update
	void updateData()
	{
		CaptureFrame(bufferRef);
	}
private:
	// Private data object we use in "call" public class function
	char* bufferRef;

};
#endif // _GraphElementCamera_h_