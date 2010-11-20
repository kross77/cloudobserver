#include "stdafx.h"
#include <boost/asio.hpp>
#include <boost/regex.hpp>
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

#include <Windows.h>
// LSD - take it for fun
#include "LSD.h"

using namespace std;
using boost::asio::ip::tcp;
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
string outputUserName	;
int streamBitRate;
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
void replace_or_merge(std::string &a, const std::string &b, const std::string &c)
{
	const std::string::size_type pos_b_in_a = a.find(b);
	if(pos_b_in_a == std::string::npos) {
		a.insert(0, c);
	}
	else {
		a.replace(pos_b_in_a, b.length(), c);
	}
}
void extract(std::string const& ip, std::string& address, std::string& service)
{
	boost::regex e("tcp://(.+):(\\d+)/");
	boost::smatch what;
	if(boost::regex_match(ip, what, e, boost::match_extra))
	{
		boost::smatch::iterator it = what.begin();
		++it; // skip the first entry..
		address = *it;
		++it;
		service = *it;
	}
}
void getAdress(){
	cout << "Please input stream URL (ex. http://127.0.0.1:4773/ )\n";
	cin >> outputUrl;
	replace_or_merge(outputUrl, "http://", "tcp://");
}

void getName(){
	cout << "Please your name (ex. georg.vasiliev )\n";
	cin >> outputUserName;
}
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

void initFFmpeg(string container, int w, int h, int fps)
{

	//cout << " 1 "<< endl;
	encoder.SetConstants(fps, videoWidth, videoHeight, audioSampleRate, streamBitRate);
	top:
int encoderIU = encoder.InitUrl(container, outputUrl, outputUserName);
	if (encoderIU == -1)
	{
		cout << "Cannot open stream URL\n";
		getAdress();
		  goto top;
	} 
	if (encoderIU == 0)
	{
		printf("Cannot open stream for selected name\n");
		getName();
		  goto top;
	} 
//	cout << " 2 "<< endl;
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
	initFFmpeg(outputContainer, videoWidth, videoHeight, videoFrameRate);
	initOpenCV();
	initOpenAL(videoFrameRate);
	
}

void CaptureFrame(int w, int h, char* buffer, int bytespan)
{
	/* get a frame */
	CVframe = cvQueryFrame(capture);

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

	switch(useLSD){
		case false:{} break;
		case true:{
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
			cvReleaseImage(&destinationForLSD);
			free_image_double(lsdImage);
			free_ntuple_list(lsdOut);
				  } break;
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
	cvReleaseImage(&redchannel);
	cvReleaseImage(&greenchannel);
	cvReleaseImage(&bluechannel);
	cvReleaseImage(&destination);
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
	//cvDestroyWindow("HelloVideoEncoding");
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
		CaptureFrame( videoWidth, videoHeight, (char *)frame->data[0],frame->linesize[0]);
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
void tryUrl(){
	top2:
//cout << "77" ;
	try
	{

		std::string addr;
		std::string port;
		extract(outputUrl, addr, port);
//cout << "87" ;
//cout << addr.c_str() << port.c_str();
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(tcp::v4(), addr.c_str(), port.c_str());
		tcp::resolver::iterator iterator = resolver.resolve(query);

		tcp::socket s(io_service);
		s.connect(*iterator);
		Sleep(250);
		s.close();
	}
	  catch (std::exception& e)
	{
		getAdress();
		goto top2;
	}
}
int main(int argc, char* argv[])
{
	cameraInt = 0;
	videoFrameRate = 15;
	videoWidth = 320;
	videoHeight =  240;
	microphoneInt = 1;
	audioSampleRate = 44100;
	outputContainer +="flv";
	streamBitRate = 250000;
	for(int i = 1; i<argc; i=i+2){
	//	cout << "i = " << i << "; argv[i] = " << argv[i] << endl;
if(string(argv[i]) == "-camera") {cameraInt = atoi(argv[i+1]);} 
if(string(argv[i]) == "-framerate" ){videoFrameRate = atoi(argv[i+1]);} 
if(string(argv[i]) == "-width" ) {videoWidth = atoi(argv[i+1]);} 
if(string(argv[i]) == "-height" ) {videoHeight = atoi(argv[i+1]);} 
if(string(argv[i]) == "-microphone" ) {microphoneInt = atoi(argv[i+1]);} 
if(string(argv[i]) == "-samplerate" ) {audioSampleRate = atoi(argv[i+1]);} 
if(string(argv[i]) == "-server" ) {outputUrl = (argv[i+1]);} 
if(string(argv[i]) == "-container" ) {outputContainer = (argv[i+1]);} 
if(string(argv[i]) == "-nickname" ) {outputUserName = (argv[i+1]);} 
if(string(argv[i]) == "-useLSD" ) {useLSD = atoi(argv[i+1]);} 
if(string(argv[i]) == "-streamBitRate" ) {streamBitRate = atoi(argv[i+1]);} 
	// example -server http://127.0.0.1:4773 -nickname vasia 
		}	
	Sleep(1000);
	desiredTimeForCaptureFame = 1000.0f / videoFrameRate;
	desiredTimeForMain = 1000.0f / videoFrameRate;

	if(outputUrl == ""){
		cout << "Warning: No Colud Observer server url found!" << endl ;
		getAdress();
	}else{
		replace_or_merge(outputUrl, "http://", "tcp://");
	}
	tryUrl();
	if(outputUserName == ""){
		cout << "Please provide us with your user name" << endl ;
		getName();
	}

	init();

	boost::thread workerThread(ThreadCaptureFrame);
	Sleep(500);
	boost::thread workerThread2(ThreadSaveFrame);

	string quite;
	while(quite != "exit")
	{
		cout << "Input 'exit' to quite" << endl;
		cin >> quite;
		//cout << endl;
		Sleep(250);
	}
	workerThread2.interrupt();
	workerThread.interrupt();
	Sleep(250);
	close();
	return 0;
}