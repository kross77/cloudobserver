#include "stdafx.h"
#include "VideoEncoder.h"
#include "Settings.h"
#include <windows.h>
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

// LSD - take it for fun
#include "LSD.h"

using namespace std;

//cmndlVars
int cameraInt;
int microphoneInt;
int frameRate;
int videoWidth;	// pixels
int videoHeight	;	// pixels
int videoFrameRate;	// hertz

int audioSampleRate	;	// hertz

string outputUrl ;
string outputContainer	;

//liveCMDvar
bool useLSD;
//mutable boost::mutex the_mutex;
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

double desiredTimeForCaptureFame;
double spendedTimeForCaptureFame;

double desiredTimeForMain;
double spendedTimeForMain;

boost::timer timerForCaptureFame;
boost::timer timerForMain;

void initOpenCV()
{
	/* initialize camera */
	capture = cvCaptureFromCAM(cameraInt);

	/* always check */
	if (!capture)
	{
		fprintf(stderr, "Cannot initialize webcam!\n");
		cin.get();
	}

}

void initOpenAL(int fps)
{
	nSampleSize = 2.0f * audioSampleRate / fps;
	//5000
	Buffer = new ALchar[nSampleSize];
	dev[0] = alcOpenDevice(NULL);
	ctx = alcCreateContext(dev[0], NULL);
	alcMakeContextCurrent(ctx);

	/* If you don't need 3D spatialization, this should help processing time */
	alDistanceModel(AL_NONE); 

	dev[microphoneInt] = alcCaptureOpenDevice(NULL, audioSampleRate, AL_FORMAT_MONO16, nSampleSize/2);
	alcCaptureStart(dev[microphoneInt]);
	//ToDo: Refactor nBlockAlign == number of channels * Bits per sample / 8 ; btw: why /8?
	nBlockAlign = 1 * 16 / 8;
}

void initFFmpeg(string url ,string container, int w, int h, int fps)
{

	cout << " 1 "<< endl;
	encoder.SetConstants(fps, videoWidth, videoHeight, audioSampleRate);

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
	initOpenAL(videoFrameRate);
	initFFmpeg(outputUrl, outputContainer, videoWidth, videoHeight, videoFrameRate);
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

	// buffer = destination->imageData;
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
}

void CaptureFrameAddLsd(char* buffer, int w, int h, int bytespan)
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

	IplImage *destinationForLSD = cvCreateImage(cvSize(w, h),IPL_DEPTH_8U,1);
	cvCvtColor(destination,destinationForLSD,CV_RGB2GRAY);

	image_double lsdImage;
	ntuple_list lsdOut;
	unsigned int x,y,i,j;
	lsdImage = new_image_double(w,h);


	for(x=0;x<w;x++)
		for(y=0;y<h;y++)
			lsdImage->data[ x + y * lsdImage->xsize ] = cvGetReal2D(destinationForLSD, y, x);/* image(x,y) */



	/* call LSD */
	lsdOut = lsd(lsdImage);



	for(i=0;i<lsdOut->size;i++)
	{
		CvPoint pt1 = { lsdOut->values[ i * lsdOut->dim + 0 ], lsdOut->values[ i * lsdOut->dim + 1]};
		CvPoint pt2 = { lsdOut->values[ i * lsdOut->dim + 2 ], lsdOut->values[ i * lsdOut->dim + 3 ] };
		cvLine(destination, pt1, pt2, CV_RGB(240, 255, 255), 1, CV_AA,0);
	}


	// buffer = destination->imageData;
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

	cvReleaseImage(&destinationForLSD);
	cvReleaseImage(&redchannel);
	cvReleaseImage(&greenchannel);
	cvReleaseImage(&bluechannel);
	cvReleaseImage(&destination);

	free_image_double(lsdImage);
	free_ntuple_list(lsdOut);
}

void GenerateSample(short* buffer, int sampleCount)
{
	double amplitude = 20.0 * pow(10, AUDIO_VOLUME / 20.0);
	double angularFrequency =  2 * M_PI * AUDIO_FREQUENCY / audioSampleRate;
	for (int i = 0; i < sampleCount; i++)
		buffer[i] = amplitude * sin(angularFrequency * (soundWaveOffset + i));

	soundWaveOffset += sampleCount;
	soundWaveOffset %= audioSampleRate;
}

char* CaptureSample()
{
	/* Check how much audio data has been captured (note that 'val' is the
	* number of frames, not bytes) */
	alcGetIntegerv(dev[microphoneInt], ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	// When we would have enough data to fill our BUFFERSIZE byte buffer, will grab the samples, so now we should wait
	while(iSamplesAvailable < (nSampleSize / nBlockAlign))
		alcGetIntegerv(dev[microphoneInt], ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	// Consume Samples 
	if (iSamplesAvailable >= (nSampleSize / nBlockAlign))
	{
		alcCaptureSamples(dev[microphoneInt], Buffer, nSampleSize / nBlockAlign);
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

void ThreadCaptureFrame()
{
	while(1){
		timerForCaptureFame.restart();
		switch(useLSD){
		case false:{
			CaptureFrame((char *)frame->data[0], videoWidth, videoHeight, frame->linesize[0]);
				   } break;
		case true:{
			CaptureFrameAddLsd((char *)frame->data[0], videoWidth, videoHeight, frame->linesize[0]);
				  } break;
		}
		AVFrame* swap = frame;
		frame = readyFrame;
		readyFrame = swap;
		spendedTimeForCaptureFame = timerForCaptureFame.elapsed();
		if(spendedTimeForCaptureFame < desiredTimeForCaptureFame){
			Sleep(desiredTimeForCaptureFame - spendedTimeForCaptureFame);
		}
	}
}
void ThreadSaveFrame()
{
	while(1)
	{
		timerForMain.restart();

		if (!encoder.AddFrame(readyFrame, CaptureSample(), nSampleSize))
			printf("Cannot write frame!\n");

		spendedTimeForMain = timerForMain.elapsed();

		if(spendedTimeForMain < desiredTimeForMain)
			Sleep(desiredTimeForMain - spendedTimeForMain);
	}
}

int main(int argc, char* argv[])
{	

	if(argc >= 8){

		cameraInt = atoi(argv[1]);
		videoFrameRate = atoi(argv[2]);
		videoWidth = atoi(argv[3]);
		videoHeight =  atoi(argv[4]);
		microphoneInt = atoi(argv[5]);
		audioSampleRate = atoi(argv[6]);
		outputUrl += argv[7];
		outputContainer +=argv[8];
		cout<<cameraInt<<  videoFrameRate<< videoWidth<< videoHeight<< microphoneInt<< audioSampleRate<< outputUrl<< outputContainer << endl;

		desiredTimeForCaptureFame = 1000.0f / videoFrameRate;
		desiredTimeForMain = 1000.0f / videoFrameRate;

	}else{
		cout << "Warning: No humans allowed!" << endl << " cameraInt;  videoFrameRate; videoWidth; videoHeight; microphoneInt; audioSampleRate; outputUrl; outputContainer;" << endl << "0 24 640 480 1 44100 tcp://127.0.0.1:4774/ flv" << endl;
		cin.get();
		return 0;
	}
	init();

	boost::thread workerThread(ThreadCaptureFrame);
	boost::thread workerThread2(ThreadSaveFrame);
	while(1)
	{
		int i;
		cin >> i;
		if(i == 1)
		{
			useLSD = true;
		}
		if(i == 0)
		{
			useLSD = false;
		}
		Sleep(250);

	}

	close();
	return 0;
}