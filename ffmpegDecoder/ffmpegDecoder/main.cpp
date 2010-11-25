// ffmpegDecoder.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
// FFmpeg
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#include <iostream>
// OpenCV
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "ffmpegDecode.h"


// Boost
#include <boost/thread.hpp>
#include <boost/timer.hpp>
//#define FILE_NAME          "c:\\temp\\1.avi"
#define FILE_NAME          "rtsp://mobile.rayv.com:80/live/rayv2demo?tcp"

// OpenCV
CvCapture* capture;
IplImage* CVframe ;


//boost
double desiredTimeForCaptureFame;
double spendedTimeForCaptureFame;
boost::timer timerForCaptureFame;

void OpenCVPreview(AVFrame * frame, int w, int h )
{
	IplImage* destination = cvCreateImage(cvSize(w, h),IPL_DEPTH_8U, 3); 
	destination->imageData = (char *)frame->data[0];
	IplImage* destination2 = cvCreateImage(cvSize(w, h), destination->depth, destination->nChannels); 
	cvResize(destination, destination2);
	cvSaveImage("test.jpg" ,destination);
	cvReleaseImage(&destination);
	cvShowImage("ffmpegDecoder", destination2);
	
}


int main()
{ int key = 0;
  cvNamedWindow("ffmpegDecoder", CV_WINDOW_AUTOSIZE);
  FFmpegDecoder decoder;

  if (decoder.OpenFile(std::string(FILE_NAME)))
  {
    int w = decoder.GetWidth();
    int h = decoder.GetHeight();

  
	while(key != 'q')
	{	
      AVFrame * frame = decoder.GetNextFrame();
      if (frame)
      {
        OpenCVPreview(frame, w, h);
   
        av_free(frame->data[0]);
        av_free(frame);
      }  
	  Sleep(1000 / decoder.videoFramePerSecond - 10);
	  key = cvWaitKey(1);
    }

    decoder.CloseFile();
	cvDestroyWindow("ffmpegDecoder");
  }
  else
  {
    printf ("Cannot open file " FILE_NAME "\n");
	std::cin.get();
  }

	return 0;
}

