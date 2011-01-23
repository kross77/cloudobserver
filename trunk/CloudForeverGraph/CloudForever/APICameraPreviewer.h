#ifndef _APICameraPreviewer_h_
#define _APICameraPreviewer_h_

#include <iostream>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace std;

class APICameraPreviewer
{
public:
	int key;

	void createPreviewWindow(string WindowName, int width, int height)
	{
		key = 0;
		windowName = WindowName;
	//cvNamedWindow(windowName.c_str(), CV_WINDOW_AUTOSIZE);
	destination = cvCreateImage(cvSize(width, height),IPL_DEPTH_8U, 3);  //создавать картинку каждый раз глупо
	}

	void OpenCVShowFrame(char * frame)
	{
//		IplImage* destination = cvCreateImage(cvSize(320, 240),IPL_DEPTH_8U, 3); 
		destination->imageData = (char *)frame;
		//IplImage* destination2 = cvCreateImage(cvSize(320, 240), destination->depth, destination->nChannels); 
		//cvResize(destination, destination2);
		//cvSaveImage("test.jpg" ,destination);
		
		cvShowImage(windowName.c_str(), destination);
		delete[] frame;	
		

		//destination->imageData = (char*)frame; // возможно понадобитс€ мен€ть последовтельность цветов // надоли потом удал€ть фрейм?
	//	IplImage* destination2 = cvCreateImage(cvSize(width, width), destination->depth, destination->nChannels);  // неразу не оптимальный трюк
	//	cvResize(destination, destination2);
	//	cvSaveImage("test.jpg" ,destination);// нумы хот€бы увидем если хоть чтонибудь работает...
		//cvReleaseImage(&destination);
	//	cvShowImage(windowName.c_str(), destination);
		// теперь пора стереть фрейм? // а может в этом и была суть...
		key = cvWaitKey(1);
	}

	void CleanUp()
	{
	//cvReleaseImage(&destination);
	cvDestroyWindow(windowName.c_str());
	cvReleaseImage(&destination);
	}
	
private:
	string windowName;
	IplImage* destination;
	
};

#endif // _APICameraPreviewer_h_