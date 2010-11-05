#include "stdafx.h"
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#include <windows.h>
#include <iostream>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "VideoEncoder.h"
#include "Settings.h"
#include <boost/thread.hpp>
#include <boost/timer.hpp>

namespace this_thread = boost::this_thread;
using namespace std;

class BaseThread
{
public:
	BaseThread()
	{ }
	virtual ~BaseThread()
	{ }

	void operator()()
	{
		try
		{
			for (;;)
			{
				// Check if the thread should be interrupted
				this_thread::interruption_point();

				DoStuff();
			}
		}
		catch (boost::thread_interrupted)
		{
			// Thread end
		}
	}

protected:
	virtual void DoStuff() = 0;
};


//variables

//for FFMpeg
VideoEncoder encoder;
int w = W_VIDEO;
int h = H_VIDEO;
AVFrame* frame;
AVFrame* readyFrame;
int nSampleSize;

char* sample;
char* readySample;
//for OpenAL

//for OpenCV
CvCapture *capture;
IplImage  *CVframe;
IplImage  *destination;
IplImage* bluechannel;
IplImage* redchannel;
IplImage* greenchannel;

int       key;
int offset = 0;

//set up OpenCV
void initOpenCV()
{
	capture = 0;
	CVframe = 0;
	key = 0;

	/* initialize camera */
	capture = cvCaptureFromCAM( 0 );

	/* always check */
	if ( !capture ) {
		fprintf( stderr, "Cannot open initialize webcam!\n" );
		cin.get();
	}

	/* create a window for the video */
	cvNamedWindow( "result", CV_WINDOW_AUTOSIZE );

}

//set up OpenAL
void initOpenAL()
{

}

//set up FFmpeg
void initFFmpeg(string filename, string container, int w, int h, int fps)
{
	encoder.SetFps(fps);
	if (!encoder.InitFile(filename, container))
	{
		printf("Cannot init file \n" );
		cin.get();
	}

	int bufferImgSize = avpicture_get_size(PIX_FMT_BGR24, w, h);

	// Create frame
	frame = avcodec_alloc_frame();
	uint8_t* frameBuffer = (uint8_t*)av_mallocz(bufferImgSize);
	avpicture_fill((AVPicture*)frame, frameBuffer, PIX_FMT_BGR24, w, h);

	// Create ready frame
	readyFrame = avcodec_alloc_frame();
	uint8_t* readyFrameBuffer = (uint8_t*)av_mallocz(bufferImgSize);
	avpicture_fill((AVPicture*)readyFrame, readyFrameBuffer, PIX_FMT_BGR24, w, h);

	nSampleSize = 2 * 22050.0f / fps; // 1 / fps sec * FORMAT SIZE(S16)

	// Create sample
	sample = new char[nSampleSize];

	// Create ready sample
	readySample = new char[nSampleSize];
}

//set up libs and comps
void initAll()
{
	initOpenCV();
	initOpenAL();
	initFFmpeg(FILE_NAME, CONTAINER, w, h, FPS);
}
// Create test video frame
void CreateFrame(char * buffer, int w, int h, int bytespan)
{
	/* get a frame */
	CVframe = cvQueryFrame( capture );

	/* always check */
	if( !CVframe ) {
		printf("No CV frame captured");
		cin.get();
	}

	/* display current frame */

	destination = cvCreateImage( cvSize(w , h ), CVframe->depth, CVframe->nChannels );

	//use cvResize to resize source to a destination image
	cvResize(CVframe, destination);

	redchannel = cvCreateImage(cvGetSize(destination), 8, 1);
	greenchannel = cvCreateImage(cvGetSize(destination), 8, 1);
	bluechannel = cvCreateImage(cvGetSize(destination), 8, 1);

	cvSplit(destination, bluechannel, greenchannel, redchannel, NULL);
	for(int y=0;y<destination->height;y++)
	{
		char* line = buffer + y * bytespan;
		for(int x=0;x<destination->width;x++)
		{

			line[0] = cvGetReal2D(redchannel, y, x);
			line[1] = cvGetReal2D(greenchannel, y, x);
			line[2] = cvGetReal2D(bluechannel, y, x);
			line += 3;
		}
	}

	cvShowImage( "result", destination );

}

// Create sample
void CreateSample(short * buffer, int sampleCount)
{
	int frequency = 440;
	int amplitude = 2000; // volume
	float temp =  3.14 * frequency / sampleCount;
	for (int i = 0; i < sampleCount; i++)
		buffer[i] = amplitude * sin(temp * (offset + i));
	//float nu = 3.14 / (22050.0f) * 15.0f;
	//for (int i = 0; i < sampleCount; i ++)
	//{
	//	// Sound :)
	//	buffer [i] = sin( nu *i  ) * 0x4FFF;
	//}
} 
void closeOpenCV()
{
	/* free memory */
	cvDestroyWindow( "result" );
	cvReleaseCapture( &capture );
}

void closeOpenAL()
{
}

void closeFFmpeg()
{
	encoder.Finish();
	av_free(frame->data[0]);
	av_free(frame);
	delete[] sample;
	sample = NULL;

	av_free(readyFrame->data[0]);
	av_free(readyFrame);
	delete[] readySample;
	readySample = NULL;
}
void closeUp()
{
	closeOpenCV();
	closeOpenAL();
	closeFFmpeg();
}





class ThreadCaptureVideo : public BaseThread
{
protected:
	virtual void DoStuff()
	{
		CreateFrame((char *)frame->data[0], w, h, frame->linesize[0]);

		// swap buffers
		AVFrame* swap = frame;
		frame = readyFrame;
		readyFrame = swap;

		//CreateSample((short *)sample, nSampleSize/2, offset);
		//offset += nSampleSize/2;
		//	if (offset == 7*nSampleSize/2)
		//	{
		//		offset = 0;
		//		cout << "cleared!"<< endl;
		//	}
	}
};
class ThreadCaptureAudio : public BaseThread
{
protected:
	virtual void DoStuff()
	{
		CreateSample((short *)sample, nSampleSize/2);
		offset += nSampleSize/2;
		//	if (offset == 7*nSampleSize/2)
		//	{
		//		offset = 0;
		//		cout << "cleared!"<< endl;
		//	}

		// swap buffers
		char* swap = sample;
		sample = readySample;
		readySample = swap;
	}
};


int main()
{
	initAll();
	
	ThreadCaptureVideo thread_ThreadCaptureVideo_instance;
	boost::thread ThreadCaptureVideo = boost::thread(thread_ThreadCaptureVideo_instance);

	ThreadCaptureAudio thread_ThreadCaptureAudio_instance;
	boost::thread ThreadCaptureAudio = boost::thread(thread_ThreadCaptureAudio_instance);

	double desiredTime = 1000.0f / FPS;
	boost::timer t;

	while(key != 'q')
	{
		t.restart();

		if (!encoder.AddFrame(readyFrame, readySample, nSampleSize))
			printf("Cannot write frame\n");
		
		double leftTime = desiredTime - t.elapsed();

		if (leftTime>0)
			this_thread::sleep(boost::posix_time::milliseconds(leftTime));

		/* exit if user press 'q' */		
		key = cvWaitKey( 1 );
	}
	
	closeUp();
	return 0;
}
