#include "stdafx.h"
#include "VideoEncoder.h"
#include "Settings.h"
//#include <windows.h>
#include <stdio.h>

// FFmpeg
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#include <iostream>

// OpenCV
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

// OpenAL
#include <al.h>
#include <alc.h>

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
URLContext* StreamToUrl;

// OpenCV
CvCapture* capture;

IplImage* CVframe;
	/* display current frame */
//	IplImage* destination;



// Samples Generator
int soundWaveOffset = 0;

// OpenAL
ALCdevice *dev[2];
ALCcontext *ctx;
ALuint source, buffers[3];
ALchar			*Buffer;
ALuint buf;
ALint val;
ALint			iSamplesAvailable;
int nBlockAlign;

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

void initOpenAL(int fps)
{
	nSampleSize = 2.0f * AUDIO_SAMPLE_RATE / fps;
	//5000
	Buffer = new ALchar[nSampleSize];
	dev[0] = alcOpenDevice(NULL);
	ctx = alcCreateContext(dev[0], NULL);
	alcMakeContextCurrent(ctx);

	//	alGenSources(1, &source);
	//	alGenBuffers(3, buffers);

	/* Setup some initial silent data to play out of the source */
	//	alBufferData(buffers[0], AL_FORMAT_MONO16, Buffer, nSampleSize, AUDIO_SAMPLE_RATE);
	//	alBufferData(buffers[1], AL_FORMAT_MONO16, Buffer, nSampleSize, AUDIO_SAMPLE_RATE);
	//	alBufferData(buffers[2], AL_FORMAT_MONO16, Buffer, nSampleSize, AUDIO_SAMPLE_RATE);
	//	alSourceQueueBuffers(source, 3, buffers);

	/* If you don't need 3D spatialization, this should help processing time */
	alDistanceModel(AL_NONE); 

	dev[1] = alcCaptureOpenDevice(NULL, AUDIO_SAMPLE_RATE, AL_FORMAT_MONO16, nSampleSize/2);

	/* Start playback and capture, and enter the audio loop */
	//alSourcePlay(source);
	alcCaptureStart(dev[1]);
	//ToDo: Refactor nBlockAlign == number of channels * Bits per sample / 8 ; btw: why /8?
	nBlockAlign = 1 * 16 / 8;
}

void initFFmpeg(string url ,string container, int w, int h, int fps)
{

	cout << " 1 "<< endl;
	encoder.SetFps(fps);

	if (!encoder.InitUrl(container, url))
	{
		printf("Cannot initialize file!\n");
		cin.get();
	}
	cout << " 2 "<< endl;
	int bufferImgSize = avpicture_get_size(PIX_FMT_BGR24, w, h);

	frame = avcodec_alloc_frame();
	uint8_t* frameBuffer = (uint8_t*)av_mallocz(bufferImgSize);
	avpicture_fill((AVPicture*)frame, frameBuffer, PIX_FMT_BGR24, w, h);

	readyFrame = avcodec_alloc_frame();
	uint8_t* readyFrameBuffer = (uint8_t*)av_mallocz(bufferImgSize);
	avpicture_fill((AVPicture*)readyFrame, readyFrameBuffer, PIX_FMT_BGR24, w, h);

	sample = new char[nSampleSize];
}

void init()
{
	initOpenCV();
	initOpenAL(VIDEO_FRAME_RATE);
	initFFmpeg(OUTPUT_URL, OUTPUT_CONTAINER, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_FRAME_RATE);

}

void CaptureFrame(char* buffer, int w, int h, int bytespan)
{
	/* get a frame */
	
	if(!cvGrabFrame(capture)){              // capture a frame 
		printf("Could not grab a frame\n\7");
		//exit(0);
	}
	CVframe =cvRetrieveFrame(capture);           // retrieve the captured frame

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

//	cvReleaseImage(&CVframe);

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
	cvReleaseImage(&redchannel);
	cvReleaseImage(&greenchannel);
	cvReleaseImage(&bluechannel);
	cvReleaseImage(&destination);
	
	
//cvShowImage("HelloVideoEncoding", destination);

//
}

void GenerateSample(short* buffer, int sampleCount)
{
	double amplitude = 20.0 * pow(10, AUDIO_VOLUME / 20.0);
	double angularFrequency =  2 * M_PI * AUDIO_FREQUENCY / AUDIO_SAMPLE_RATE;
	for (int i = 0; i < sampleCount; i++)
		buffer[i] = amplitude * sin(angularFrequency * (soundWaveOffset + i));

	soundWaveOffset += sampleCount;
	soundWaveOffset %= AUDIO_SAMPLE_RATE;
}

char* CaptureSample()
{
	/* Check how much audio data has been captured (note that 'val' is the
	* number of frames, not bytes) */
	alcGetIntegerv(dev[1], ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	// When we would have enough data to fill our BUFFERSIZE byte buffer, will grab the samples, so now we should wait
	while(iSamplesAvailable < (nSampleSize / nBlockAlign))
		alcGetIntegerv(dev[1], ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	// Consume Samples 
	if (iSamplesAvailable >= (nSampleSize / nBlockAlign))
	{
		alcCaptureSamples(dev[1], Buffer, nSampleSize / nBlockAlign);
		return  (char *)Buffer;
	}
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
		CaptureFrame((char *)frame->data[0], VIDEO_WIDTH, VIDEO_HEIGHT, frame->linesize[0]);

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

	int key = 0;
	//double desiredTime = 1000.0f / VIDEO_FRAME_RATE;

	while(key != 'q')
	{	
		if (!encoder.AddFrame(readyFrame, CaptureSample(), nSampleSize))
			printf("Cannot write frame!\n");

		key = cvWaitKey(1);
	}

	close();
	return 0;
}
