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
#include <boost/date_time.hpp>


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
#include <boost/random.hpp>
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
IplImage* CVframe;
CvFont font;
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

 boost::mt19937 rng;
 	 boost::uniform_int<> six(-128,127); 
	 	 boost::variate_generator<boost::mt19937&, boost::uniform_int<> >die(rng, six); 

double desiredTimeForCaptureFame;
double spendedTimeForCaptureFame;

double desiredTimeForMain;
double spendedTimeForMain;

boost::timer timerForCaptureFame;
boost::timer timerForMain;

bool rainbow; 
bool randomSound;
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
	    cvInitFont( &font, CV_FONT_HERSHEY_DUPLEX  , 2, 1, 0.0, 3, CV_AA );

}

void initOpenAL(int fps)
{
	nSampleSize = 2.0f * audioSampleRate / fps;
	nBlockAlign = 1 * 16 / 8;
	//5000
	Buffer = new ALchar[nSampleSize];
	
		
		 if (randomSound)
		 { 
			 encoder.hasAudio = true;
		 }
		                 // produces randomness out of thin air
		 // see pseudo-random number generators
	     // distribution that maps to 1..6
		 // see random number distributions
	         
	 
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
int drawRect(IplImage* image, int x1, int y1, int x2, int y2,
			  CvScalar color)
{
	CvPoint UL = {x1,y1};
	CvPoint LR = {x2,y2};
	cvRectangle( image, UL, LR, color);
	return 0;
}
void CaptureFrame(int w, int h, char* buffer, int bytespan)
{
	if(rainbow){
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
	}else{
			CVframe = cvCreateImage(cvSize(videoWidth, videoHeight),8, 4 );

		drawRect(CVframe, 0, 0, w, h, CV_RGB(100, 100, 100));

		cvPutText(CVframe, outputUserName.c_str(), cvPoint(0,h-10), &font , CV_RGB(0,0,0));
		std::ostringstream msg;
		const boost::posix_time::ptime now=
			boost::posix_time::second_clock::local_time();
		boost::posix_time::time_facet*const f=
			new boost::posix_time::time_facet("%H:%M:%S");
		msg.imbue(std::locale(msg.getloc(),f));
		msg << now;
	string cvtext;
		cvtext += msg.str();
		cvPutText(CVframe, cvtext.c_str(), cvPoint(0,(h/2+10)), &font , CV_RGB(0,0,0));

IplImage* redchannel = cvCreateImage(cvGetSize(CVframe), 8, 1);
IplImage* greenchannel = cvCreateImage(cvGetSize(CVframe), 8, 1);
IplImage* bluechannel = cvCreateImage(cvGetSize(CVframe), 8, 1);

cvSplit(CVframe, bluechannel, greenchannel, redchannel, NULL);

for(int y = 0; y < CVframe->height; y++)
{
	char* line = buffer + y * bytespan;
	for(int x = 0; x < CVframe->width; x++)
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
cvReleaseImage(&CVframe);

	}

}



char* CaptureSample()
{

	if(randomSound){
	                     // simulate rolling a die
	for (int i = 0; i < nSampleSize / nBlockAlign; i ++)
	{
		// Sound :)
		Buffer [i] = die();
	}}

	return (char *)Buffer;
}

void closeOpenCV()
{
	//cvDestroyWindow("HelloVideoEncoding");
	
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
	rainbow = false;
	for(int i = 1; i<argc; i=i+2){
	//	cout << "i = " << i << "; argv[i] = " << argv[i] << endl;
if(string(argv[i]) == "-framerate" ){videoFrameRate = atoi(argv[i+1]);} 
if(string(argv[i]) == "-width" ) {videoWidth = atoi(argv[i+1]);} 
if(string(argv[i]) == "-height" ) {videoHeight = atoi(argv[i+1]);} 
if(string(argv[i]) == "-samplerate" ) {audioSampleRate = atoi(argv[i+1]);} 
if(string(argv[i]) == "-server" ) {outputUrl = (argv[i+1]);} 
if(string(argv[i]) == "-container" ) {outputContainer = (argv[i+1]);} 
if(string(argv[i]) == "-nickname" ) {outputUserName = (argv[i+1]);} 
if(string(argv[i]) == "-streamBitRate" ) {streamBitRate = atoi(argv[i+1]);} 
if(string(argv[i]) == "-rainbow" ) {rainbow = atoi(argv[i+1]);} 
if(string(argv[i]) == "-randomSound" ) {randomSound = atoi(argv[i+1]);} 
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