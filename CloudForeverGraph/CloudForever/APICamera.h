#ifndef _CAMERA_API_H__
#define _CAMERA_API_H__

#include <iostream>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "CamerasList.h"
using namespace std;

class APICamera
{
public:
	void initOpenCV(int width, int height, int captureFrameRate){
selectCamera:
		CamerasList  * CamList  = new CamerasList();
		int cameraInt = CamList->SelectFromList();
		if (cameraInt != 999)
		{
			/* initialize camera */
			capture = cvCaptureFromCAM(cameraInt);

			cvSetCaptureProperty(capture, CV_CAP_PROP_FPS   , captureFrameRate );
			try
			{
				cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH , (double)  width);

				cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT  , (double) height);
			}
			catch (exception* e)
			{
				cout << "resize ex" << endl;
			}

			/* always check */
			if (!capture)
			{
				fprintf(stderr, "Cannot initialize selected web cam!\n");
				//cin.get(); //п роверить: а мы ваобще до сюда когдалибо доходим?
				goto selectCamera;
			}

			CVframe = cvQueryFrame(capture);
			//cvSaveImage("test.jpg" ,CVframe);
			destination = cvCreateImage(cvSize(width, height), CVframe->depth, CVframe->nChannels);
		}
	}

	char* CaptureFrame(char* buffer)
	{
		/* get a frame */
		CVframe = cvQueryFrame(capture);

		/* always check */
		if (!CVframe)
		{
			printf("No CV frame captured!\n");
			cin.get();
		}

		cvResize(CVframe, destination);
		//cvSaveImage("test2.jpg" ,destination);

		for(int i = 0; i < destination->imageSize; i=i+3)
		{ 

			buffer[2] = destination->imageData[i];
			buffer[1] = destination->imageData[i+1];
			buffer[0] = destination->imageData[i+2];
			buffer+=3;
		}
	/*	for(int i = 0; i < destination->imageSize; i=i+3)
		{ 

			buffer[0] = destination->imageData[i];
			buffer[1] = destination->imageData[i+1];
			buffer[2] = destination->imageData[i+2];
			buffer+=3;
		}*/
//buffer = destination->imageSize;
		return buffer;

	}

	void closeOpenCV()
	{
		cvReleaseCapture(&capture);
	//	cvReleaseImage(&destination);
	//	cvReleaseImage(&CVframe);
	}


private:
	CvCapture* capture;
	IplImage* CVframe;
	IplImage* destination;
};
#endif // _CAMERA_API_H__