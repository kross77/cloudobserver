// ToDo: This file should be tested for platform errors and moved into seprete project.
// CamLister.cpp : Defines the entry point for the console application.

#include "VideoEncoder.h"
#include "lsd.h"
#include <boost/random.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
// OpenAL
#ifdef WIN
#include <AL/al.h>
#include <AL/alc.h>
#elif defined MAC
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#elif defined LIN
#include <AL/al.h>
#include <AL/alc.h>
#else
#error "unknown platform"
#endif

// OpenCV
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

using namespace std;
using boost::asio::ip::tcp;
using namespace boost::posix_time;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
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

CvFont font;
IplImage* CVframe;
IplImage* CVframeWithText ;
CvPoint UL;
CvPoint LR;

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
		CvPoint UL = {0,0};
		CvPoint LR = {videoWidth,videoHeight};
		 CVframe = cvCreateImage(cvSize(videoWidth, videoHeight),8, 4 );
		  CVframeWithText = cvCreateImage(cvSize(videoWidth, videoHeight),8, 4 );
		 cvRectangle( CVframe, UL, LR, CV_RGB(0,254,53), CV_FILLED);

		 cvPutText(CVframe, outputUserName.c_str(), cvPoint(0,videoHeight-10), &font , CV_RGB(1,1,1));

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
		boost::this_thread::sleep(boost::posix_time::milliseconds(999999999));
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
	boost::this_thread::sleep(boost::posix_time::milliseconds(999999999));

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
  cvResize(CVframe, CVframeWithText);
		//char timeStr [9];
		ptime now = second_clock::local_time();
			
		cvPutText(CVframeWithText,to_simple_string(now.time_of_day()).c_str(), cvPoint(0,(h/2+10)), &font , CV_RGB(1,1,1));
		for(int i = 0; i < w*4*h; i=i+4)
		{ 

			buffer[0] = CVframeWithText->imageData[i];
			buffer[1] = CVframeWithText->imageData[i+1];
			buffer[2] = CVframeWithText->imageData[i+2];
			buffer+=3;
		}
	}

}



char* CaptureSample()
{

	if(randomSound){
	for (int i = 0; i < nSampleSize / nBlockAlign; i ++)
	{
		// Sound :)
		Buffer [i] = die();
	}}

	return (char *)Buffer;
}

void closeOpenCV()
{	
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
	boost::this_thread::sleep(boost::posix_time::milliseconds(desiredTimeForCaptureFame - spendedTimeForCaptureFame));
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
			boost::this_thread::sleep(boost::posix_time::milliseconds(desiredTimeForMain - spendedTimeForMain));
	}
}
int main(int argc, char* argv[])
{

	rainbow = false;
	randomSound = false;
	videoFrameRate = 15;
	videoWidth = 1280;
	videoHeight =  720;
	audioSampleRate = 44100;
	outputContainer +="flv";
	streamBitRate = 1280000;
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
	boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	boost::thread workerThread2(ThreadSaveFrame);

	string quite;
	while(quite != "exit")
	{
		cout << "\nInput 'exit' to quite" << endl;
		cin >> quite;
		//cout << endl;
		     boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	}
	workerThread2.interrupt();
	workerThread.interrupt();
	boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	close();
	return 0;
}