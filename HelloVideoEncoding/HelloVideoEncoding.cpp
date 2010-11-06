#include "stdafx.h"
#include "VideoEncoder.h"
#include "Settings.h"

// FFmpeg
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#include <windows.h>
#include <iostream>

// OpenCV
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

// Boost
#include <boost/thread.hpp>
#include <boost/timer.hpp>

using namespace std;

// FFmpeg
VideoEncoder encoder;
AVFrame* frame;
AVFrame* readyFrame;
int nSampleSize;
char* sample;

// OpenCV
CvCapture* capture;

void initOpenCV()
{
	/* initialize camera */
	capture = cvCaptureFromCAM(0);

	/* always check */
	if (!capture)
	{
		fprintf(stderr, "Cannot initialize webcam!\n");
		cin.get();
	}

	/* create a window for the video */
	cvNamedWindow("HelloVideoEncoding", CV_WINDOW_AUTOSIZE);
}

void initOpenAL()
{
}

void initFFmpeg(string filename, string container, int w, int h, int fps)
{
	encoder.SetFps(fps);

	if (!encoder.InitFile(filename, container))
	{
		printf("Cannot initialize file!\n");
		cin.get();
	}

	int bufferImgSize = avpicture_get_size(PIX_FMT_BGR24, w, h);

	frame = avcodec_alloc_frame();
	uint8_t* frameBuffer = (uint8_t*)av_mallocz(bufferImgSize);
	avpicture_fill((AVPicture*)frame, frameBuffer, PIX_FMT_BGR24, w, h);

	readyFrame = avcodec_alloc_frame();
	uint8_t* readyFrameBuffer = (uint8_t*)av_mallocz(bufferImgSize);
	avpicture_fill((AVPicture*)readyFrame, readyFrameBuffer, PIX_FMT_BGR24, w, h);

	nSampleSize = 2 * 22050.0f / fps;
	sample = new char[nSampleSize];
}

void init()
{
	initOpenCV();
	initOpenAL();
	initFFmpeg(FILE_NAME, CONTAINER, W_VIDEO, H_VIDEO, FRAME_RATE);
}

void CaptureFrame(char* buffer, int w, int h, int bytespan)
{
	/* get a frame */
	IplImage* CVframe = cvQueryFrame(capture);

	/* always check */
	if (!CVframe)
	{
		printf("No CV frame captured!\n");
		cin.get();
	}

	/* display current frame */
	IplImage* destination = cvCreateImage(cvSize(w, h), CVframe->depth, CVframe->nChannels);

	//use cvResize to resize source to a destination image
	cvResize(CVframe, destination);

	IplImage* redchannel = cvCreateImage(cvGetSize(destination), 8, 1);
	IplImage* greenchannel = cvCreateImage(cvGetSize(destination), 8, 1);
	IplImage* bluechannel = cvCreateImage(cvGetSize(destination), 8, 1);

	cvSplit(destination, bluechannel, greenchannel, redchannel, NULL);
	for(int y = 0; y < destination->height; y++)
	{
		char* line = buffer + y * bytespan;
		for(int x = 0; x < destination->width; x++)
		{
			line[0] = cvGetReal2D(redchannel, y, x);
			line[1] = cvGetReal2D(greenchannel, y, x);
			line[2] = cvGetReal2D(bluechannel, y, x);
			line += 3;
		}
	}

	cvShowImage("HelloVideoEncoding", destination);
}

void GenerateSample(short* buffer, int sampleCount, int offset)
{
	double amplitude = 20.0 * pow(10, VOLUME / 20.0);
	double angularFrequency =  2 * M_PI * FREQUENCY / SAMPLE_RATE;
	for (int i = 0; i < sampleCount; i++)
		buffer[i] = amplitude * sin(angularFrequency * (offset + i));
}

void closeOpenCV()
{
	cvDestroyWindow("HelloVideoEncoding");
	cvReleaseCapture(&capture);
}

void closeOpenAL()
{
}

void closeFFmpeg()
{
	encoder.Finish();

	av_free(frame->data[0]);
	av_free(frame);

	av_free(readyFrame->data[0]);
	av_free(readyFrame);

	delete[] sample;
	sample = NULL;
}

void close()
{
	closeOpenCV();
	closeOpenAL();
	closeFFmpeg();
}

class BaseThread
{
public:
	BaseThread() { }

	virtual ~BaseThread() { }

	void operator()()
	{
		try
		{
			for (;;)
			{
				// Check if the thread should be interrupted
				boost::this_thread::interruption_point();

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

class ThreadCaptureVideo : public BaseThread
{
protected:
	virtual void DoStuff()
	{
		CaptureFrame((char *)frame->data[0], W_VIDEO, H_VIDEO, frame->linesize[0]);

		// swap buffers
		AVFrame* swap = frame;
		frame = readyFrame;
		readyFrame = swap;
	}
};

int main()
{
	init();

	ThreadCaptureVideo threadCaptureVideo;
	boost::thread ThreadCaptureVideo = boost::thread(threadCaptureVideo);

	boost::timer t;
	int key = 0;
	int offset = 0;
	double desiredTime = 1000.0f / FRAME_RATE;

	while(key != 'q')
	{
		t.restart();

		GenerateSample((short *)sample, nSampleSize / 2, offset);
		offset += nSampleSize / 2;

		if (!encoder.AddFrame(readyFrame, sample, nSampleSize))
			printf("Cannot write frame!\n");

		double sleepTime = desiredTime - t.elapsed();

		if (sleepTime>0)
			boost::this_thread::sleep(boost::posix_time::milliseconds(sleepTime));

		key = cvWaitKey(1);
	}

	close();
	return 0;
}
