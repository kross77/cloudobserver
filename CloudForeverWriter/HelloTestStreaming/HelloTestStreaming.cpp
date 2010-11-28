// CamLister.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <windows.h>
#include <iostream>
#include <dshow.h>

#pragma comment(lib, "strmiids")
// FFmpeg
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#include <boost/thread.hpp>
#include <boost/timer.hpp>

#pragma comment(lib, "strmiids")

#include "list.h"

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

#include "VideoEncoder.h"
//#include <iostream>

// LSD - take it for fun
#include "LSD.h"
#include <cstdlib> 
#include <ctime> 

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

ALCdevice		*pDevice;
ALCcontext		*pContext;
ALCdevice		*pCaptureDevice;
const ALCchar	*szDefaultCaptureDevice;



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
	cout << "Please your name (ex. georg )\n";
	cin >> outputUserName;
}
void initOpenCV()
{


	encoder.hasVideo = true;
	

}

void initOpenAL(int fps)
{
	nSampleSize = 2.0f * audioSampleRate / fps;
	nBlockAlign = 1 * 16 / 8;
	//5000
	Buffer = new ALchar[nSampleSize];
	
		 encoder.hasAudio = true;

	 
}

void initFFmpeg(string container, int w, int h, int fps)
{
	if(!encoder.hasAudio && !encoder.hasVideo){
		cout << "\nNo audio, and no video data found.\n Please close application.\nConnect some capturing device.\nRestart application\n";
		cin.get();
		Sleep(999999);
		cin.get();
	}

	//cout << " 1 "<< endl;
	encoder.SetConstants(fps, videoWidth, videoHeight, audioSampleRate, streamBitRate);

	name:
	int encoderName = encoder.ConnectUserToUrl(outputUserName) ;
	if (encoderName == 0)
	{
		//printf("Cannot open stream for selected name\n");
		getName();
		int encoderServer = encoder.ConnectToServer(outputUrl) ;
		  goto name;
	} 

	if(encoder.InitUrl(container, outputUrl, outputUserName) == -10){
	cout << "\nNo audio, and no video data found.\n Please close application.\nConnect some capturing device.\nRestart application\n";
	cin.get();
	Sleep(999999);

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
	
	initOpenCV();
	initOpenAL(videoFrameRate);
	initFFmpeg(outputContainer, videoWidth, videoHeight, videoFrameRate);
	
}

void CaptureFrame(int w, int h, char* buffer, int bytespan)
{
	int wxh = w * h;
	static float seed = 1.0;
	for (int i = 0; i < h; i ++)
	{
		char* line = buffer + i * bytespan;
		for (int j = 0; j < w; j ++)
		{
			// RGB
			line[0] = 255 * sin(((float)i / wxh * seed) * 3.14);
			line[1] = 255 * cos(((float)j / wxh * seed) * 3.14);
			line[2] = 255 * sin(((float)(i + j) / wxh * seed) * 3.14);
			line += 3;
		}
	}
	seed = seed + 2.2;
}



char* CaptureSample()
{
	static float shift = 0.0;
double amplitude = 1000000 * pow(10, 1 / 400.0);
	for (int i = 0; i < nSampleSize / nBlockAlign; i ++)
	{
		// Sound :)
		Buffer [i] = amplitude  * sin((shift + i)) / 100;
	}
	shift = shift + amplitude * nSampleSize / nBlockAlign ;

	return (char *)Buffer;
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
{ if (encoder.hasVideo)
{	while(1){
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

}
void ThreadSaveFrame()
{
	while(1)
	{
		timerForMain.restart();
if (!encoder.hasVideo)
{		if (!encoder.AddFrame( CaptureSample(), nSampleSize))
printf("Cannot write frame!\n");
}

if (!encoder.hasAudio)
{		if (!encoder.AddFrame(readyFrame))
printf("Cannot write frame!\n");
}

if (encoder.hasAudio && encoder.hasVideo)
{	
	if (!encoder.AddFrame(readyFrame, CaptureSample(), nSampleSize))
printf("Cannot write frame!\n");
}
if (!encoder.hasAudio && !encoder.hasVideo)
{
	printf("No data to encode");
break;
}

		spendedTimeForMain = timerForMain.elapsed();

		if(spendedTimeForMain < desiredTimeForMain)
			Sleep(desiredTimeForMain - spendedTimeForMain);
	}
}
int main(int argc, char* argv[])
{
	videoFrameRate = 15;
	videoWidth = 320;
	videoHeight =  240;
	audioSampleRate = 44100;
	outputContainer +="flv";
	streamBitRate = 250000;
	for(int i = 1; i<argc; i=i+2){
	//	cout << "i = " << i << "; argv[i] = " << argv[i] << endl;
if(string(argv[i]) == "-framerate" ){videoFrameRate = atoi(argv[i+1]);} 
if(string(argv[i]) == "-width" ) {videoWidth = atoi(argv[i+1]);} 
if(string(argv[i]) == "-height" ) {videoHeight = atoi(argv[i+1]);} 
if(string(argv[i]) == "-samplerate" ) {audioSampleRate = atoi(argv[i+1]);} 
if(string(argv[i]) == "-server" ) {outputUrl = (argv[i+1]);} 
if(string(argv[i]) == "-container" ) {outputContainer = (argv[i+1]);} 
if(string(argv[i]) == "-nickname" ) {outputUserName = (argv[i+1]);} 
if(string(argv[i]) == "-useLSD" ) {useLSD = atoi(argv[i+1]);} 
if(string(argv[i]) == "-streamBitRate" ) {streamBitRate = atoi(argv[i+1]);} 
	// example -server http://127.0.0.1:4773 -nickname vasia 
		}	
	//Sleep(1000);
	desiredTimeForCaptureFame = 1000.0f / videoFrameRate;
	desiredTimeForMain = 1000.0f / videoFrameRate;

	if(outputUrl == ""){
		cout << "Warning: No Cloud Observer server url found!" << endl ;
		getAdress();
	}else{
		replace_or_merge(outputUrl, "http://", "tcp://");
	}
	server:
	int encoderServer = encoder.ConnectToServer(outputUrl) ;
	if (encoderServer == -1)
	{
		//cout << "Cannot open stream URL\n";
		getAdress();
		goto server;
	}
	if(outputUserName == ""){

outputUserName += "robot";
srand((unsigned)time(0)); 
int random_integer = rand(); 
outputUserName += boost::lexical_cast<string>(random_integer);;
//cout << outputUserName;
	}

	init();

	boost::thread workerThread(ThreadCaptureFrame);
	Sleep(500);
	boost::thread workerThread2(ThreadSaveFrame);

	string quite;
	while(quite != "exit")
	{
		cout << "\nInput 'exit' to quite" << endl;
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