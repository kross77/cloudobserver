#include "stdafx.h"
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

#pragma comment(lib, "strmiids")
// FFmpeg
#ifdef __WIN32__
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#else
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#endif

#include <boost/thread.hpp>
#include <boost/timer.hpp>

#pragma comment(lib, "strmiids")

#include "list.h"

// OpenCV
#ifdef __WIN32__
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#else
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#endif

// OpenAL
#ifdef __WIN32__
#include <al.h>
#include <alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
// Boost
#include <boost/thread.hpp>
#include <boost/timer.hpp>

#include "VideoEncoder.h"
//#include <iostream>

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
IplImage* destination;
IplImage* redchannel;
IplImage* greenchannel ;
IplImage* bluechannel ;
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

struct limited_cmp {
	int limit;
	limited_cmp(int a_limit) : limit(a_limit) {
	}
	bool operator()(int left, int right) const {
		if (left <= limit && limit < right) {
			return false;
		}
		return (left < right);
	}
};

int GetEvan(int number){
	while ( number % 4 != 0)
	{
		++number;
	}
	return number;
}

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
selectCamera:
	CamerasList  * CamList  = new CamerasList();
	cameraInt = CamList->SelectFromList();
	if (cameraInt == 999)
	{
		encoder.hasVideo = false;
	}else{

		/* initialize camera */
		capture = cvCaptureFromCAM(cameraInt);

		cvSetCaptureProperty(capture, CV_CAP_PROP_FPS   , videoFrameRate );
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH , (double)  videoWidth);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT  , (double) videoHeight);

	}
	/* always check */
	if (!capture)
	{
		fprintf(stderr, "Cannot initialize selected webcam!\n");
		goto selectCamera;
	}

	CVframe = cvQueryFrame(capture);
	destination = cvCreateImage(cvSize(videoWidth, videoHeight), CVframe->depth, CVframe->nChannels);
	redchannel = cvCreateImage(cvGetSize(destination), 8, 1);
	greenchannel = cvCreateImage(cvGetSize(destination), 8, 1);
	bluechannel = cvCreateImage(cvGetSize(destination), 8, 1);
	encoder.hasVideo = true;
}


void initOpenAL(int fps)
{
	nSampleSize = 2.0f * audioSampleRate / fps;
	Buffer = new ALchar[nSampleSize];
	dev[0] = alcOpenDevice(NULL);
	if (NULL == dev[0])
	{
		fprintf(stderr, "No microphone found, please restart application , or continue streaming with out sound\n");
		Sleep(999999);
		cin.get();
		return;
	}

	ctx = alcCreateContext(dev[0], NULL);
	alcMakeContextCurrent(ctx);
	int i = -1;
	string bufferString[99];
	const ALchar *pDeviceList = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
	const ALCchar *bufferList[99];
	if (pDeviceList)
	{
		printf("\nLet us select audio device\n");
		printf("Available Capture Devices are:\n");
		i = 0;
		while (*pDeviceList)
		{
			bufferList[i] = pDeviceList;
			bufferString[i] += pDeviceList;
			cout << i <<") " << bufferString[i] << endl;
			pDeviceList += strlen(pDeviceList) + 1;
			i++;
		}
	}

	int SelectedIndex = 999;
	if(i <= 0)
	{
		cout <<"No devices found. \n " << endl;
		SelectedIndex = 999;
	}
	else if(i == 1){
		cout <<"Default device will be used" << std::endl;
		SelectedIndex = 0;
		encoder.hasAudio = true;
	}else{	
		while(SelectedIndex > i-1 || SelectedIndex < 0)
		{
			try{
				std::cout <<"please input index from 0 to " << i-1 << std::endl;		
				std::string s;
				std::getline( cin, s, '\n' );
				SelectedIndex =  boost::lexical_cast<int>(s);
			}
			catch(std::exception& e){
				SelectedIndex = 999;
			}
		}
	}

	if (SelectedIndex == 999)
	{
		encoder.hasAudio = false;
	}else{
		encoder.hasAudio = true;
		alDistanceModel(AL_NONE); 

		dev[0] = alcCaptureOpenDevice(bufferList[SelectedIndex], audioSampleRate, AL_FORMAT_MONO16, nSampleSize/2);
		alcCaptureStart(dev[0]);
		nBlockAlign = 1 * 16 / 8;
	}
}

void initFFmpeg(string container, int w, int h, int fps)
{
	if(!encoder.hasAudio && !encoder.hasVideo){
		cout << "\nNo audio, and no video data found.\n Please close application.\nConnect some capturing device.\nRestart application\n";
		cin.get();
		Sleep(999999);
		cin.get();
	}
	encoder.SetConstants(fps, videoWidth, videoHeight, audioSampleRate, streamBitRate);

name:
	int encoderName = encoder.ConnectUserToUrl(outputUserName) ;
	if (encoderName == 0)
	{
		getName();
		int encoderServer = encoder.ConnectToServer(outputUrl) ;
		goto name;
	} 

	if(encoder.InitUrl(container, outputUrl, outputUserName) == -10){
		cout << "\nNo audio, and no video data found.\n Please close application.\nConnect some capturing device.\nRestart application\n";
		cin.get();
		Sleep(999999);

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
	initOpenAL(videoFrameRate);
	initFFmpeg(outputContainer, videoWidth, videoHeight, videoFrameRate);
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

	for(int i = 0; i < destination->imageSize; i=i+3)
	{ 

		buffer[2] = destination->imageData[i];
		buffer[1] = destination->imageData[i+1];
		buffer[0] = destination->imageData[i+2];
		buffer+=3;
	}

}

char* CaptureSample()
{
	/* Check how much audio data has been captured (note that 'val' is the
	* number of frames, not bytes) */
	alcGetIntegerv(dev[0], ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	// When we would have enough data to fill our BUFFERSIZE byte buffer, will grab the samples, so now we should wait
	while(iSamplesAvailable < (nSampleSize / nBlockAlign))
		alcGetIntegerv(dev[0], ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	// Consume Samples 
	if (iSamplesAvailable >= (nSampleSize / nBlockAlign))
	{
		alcCaptureSamples(dev[0], Buffer, nSampleSize / nBlockAlign);
		return  (char *)Buffer;
	}
}

void closeOpenCV()
{
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
	if (encoder.hasVideo)
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
	cameraInt = 0;
	videoFrameRate = 15;
	videoWidth = 400; // default for WSVGA and XGA // use at least 640  to get full super HD Qualyty
	videoHeight =  320; // default for XGA // use at least 480 to get full super HD Qualyty
	microphoneInt = 1;
	audioSampleRate = 44100;
	outputContainer +="flv";
	streamBitRate = 1.5 * videoWidth * 1024;  /*videoWidth * 150*/; // use at least 700000 to get full super HD Qualyty
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
		// example -server http://127.0.0.1:4773 -nickname vasia  // if you change w and h do not forget about stream bit rate!!!
	}	

	videoHeight = GetEvan(videoHeight);
	videoWidth = GetEvan(videoWidth);
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
