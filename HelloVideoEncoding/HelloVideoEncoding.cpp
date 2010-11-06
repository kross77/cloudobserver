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

using namespace std;

// FFmpeg
VideoEncoder encoder;
AVFrame* frame;
AVFrame* readyFrame;
int nSampleSize;
char* sample;

// OpenCV
CvCapture* capture;

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

	sample = new char[nSampleSize];
}

void init()
{
	initOpenCV();
	initOpenAL(VIDEO_FRAME_RATE);
	initFFmpeg(OUTPUT_FILE_NAME, OUTPUT_CONTAINER, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_FRAME_RATE);
	
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

void GenerateSample(short* buffer, int sampleCount)
{
	double amplitude = 20.0 * pow(10, AUDIO_VOLUME / 20.0);
	double angularFrequency =  2 * M_PI * AUDIO_FREQUENCY / AUDIO_SAMPLE_RATE;
	for (int i = 0; i < sampleCount; i++)
		buffer[i] = amplitude * sin(angularFrequency * (soundWaveOffset + i));

	soundWaveOffset += sampleCount;
	soundWaveOffset %= AUDIO_SAMPLE_RATE;
}
void cpystr(char *instr, char *outstr)
{
	while( *outstr++ = *instr++);
}
void CaptureSample(char* buffer, int sampleCount)
{
			// Release some CPU time ...
			//Sleep(1);

        /* Check if any queued buffers are finished */
        alGetSourcei(source, AL_BUFFERS_PROCESSED, &val);
      
		//		if(val <= 0)
		//         continue;

        /* Check how much audio data has been captured (note that 'val' is the
        * number of frames, not bytes) */
        alcGetIntegerv(dev[1], ALC_CAPTURE_SAMPLES, 1, &val);

			// When we have enough data to fill our BUFFERSIZE byte buffer, grab the samples
			if (iSamplesAvailable > (sampleCount / nBlockAlign))
			{
				// Consume Samples
				alcCaptureSamples(dev[1], Buffer, nSampleSize / nBlockAlign);
		
				// Write the audio data to a file
				//fwrite(Buffer, BUFFERSIZE, 1, pFile);

				// Write the audio data to a given buffer
				cpystr(Buffer, buffer);
				
				// Record total amount of data recorded
				//iDataSize += BUFFERSIZE;
				
				val = nSampleSize / nBlockAlign;

				/* Pop the oldest finished buffer, fill it with the new capture data,
				then re-queue it to play on the source */
			// ÂÎÑÏÐÎÈÇÂÅÄÅÍÈÅ ÍÈÆÅ
				//	alSourceUnqueueBuffers(source, 1, &buf);
				//	alBufferData(buf, AL_FORMAT_MONO16, dev[1], val*2 /* bytes here, not
//																frames */, AUDIO_SAMPLE_RATE);
				//alSourceQueueBuffers(source, 1, &buf);

				/* Make sure the source is still playing */


				//alGetSourcei(source, AL_SOURCE_STATE, &val);

				//if(val != AL_PLAYING)
				//{

				//	alSourcePlay(source);
				//}

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

	boost::timer t;
	int key = 0;
	double desiredTime = 1000.0f / VIDEO_FRAME_RATE;

	while(key != 'q')
	{
		t.restart();

		GenerateSample((short *)sample, nSampleSize / 2);
		//CaptureSample(sample, nSampleSize);
		if (!encoder.AddFrame(readyFrame, sample, nSampleSize))
			printf("Cannot write frame!\n");

		double sleepTime = desiredTime - t.elapsed();
		cout << sleepTime;
		if (sleepTime>=0){
			boost::this_thread::sleep(boost::posix_time::milliseconds(sleepTime));
		}
			
		if (sleepTime<0)
			cout << " delayed";
		cout << endl;

		key = cvWaitKey(1);
	}

	close();
	return 0;
}
