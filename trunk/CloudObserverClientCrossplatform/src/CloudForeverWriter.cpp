// Boost
#include <boost/asio.hpp>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>

// OpenCV
#include <opencv2/opencv.hpp>

#include "list.h"
#include "LSD.h"
#include "VideoEncoder.h"

using namespace std;
using boost::asio::ip::tcp;

//cmndlVars
int cameraInt;
int microphoneInt;
int frameRate;
int videoWidth;
int videoHeight;
int videoFrameRate;
int audioSampleRate;
bool noAudio;
string outputUrl;
string outputContainer;
string outputUserName;
int streamBitRate;
bool useLSD;

// FFmpeg
VideoEncoder encoder;
AVFrame* frame;
AVFrame* readyFrame;
int nSampleSize;
char* sample;
URLContext* StreamToUrl;

// OpenAL
ALCdevice* dev[2];
ALCcontext* ctx;
ALuint source, buffers[3];
ALchar* Buffer;
ALuint buf;
ALint val;
ALint iSamplesAvailable;
int nBlockAlign;
ALCdevice* pDevice;
ALCcontext* pContext;
ALCdevice* pCaptureDevice;
const ALCchar* szDefaultCaptureDevice;

// OpenCV
CvCapture* capture;
IplImage* CVframe;
IplImage* destination;
IplImage* redchannel;
IplImage* greenchannel;
IplImage* bluechannel;

int64_t desiredTimeForCaptureFame;
int64_t spendedTimeForCaptureFame;

int64_t desiredTimeForMain;
int64_t spendedTimeForMain;

boost::timer timerForCaptureFame;
boost::timer timerForMain;

struct limited_cmp
{
	int limit;

	limited_cmp(int a_limit) : limit(a_limit) {}

	bool operator()(int left, int right) const
	{
		if (left <= limit && limit < right)
			return false;
		return (left < right);
	}
};

int GetEvan(int number)
{
	while (number % 4 != 0)
		++number;
	return number;
}

void replace_or_merge(std::string &a, const std::string &b, const std::string &c)
{
	const std::string::size_type pos_b_in_a = a.find(b);
	if (pos_b_in_a == std::string::npos)
		a.insert(0, c);
	else
		a.replace(pos_b_in_a, b.length(), c);
}

void extract(std::string const& ip, std::string& address, std::string& service)
{
	boost::regex e("tcp://(.+):(\\d+)/");
	boost::smatch what;
	if (boost::regex_match(ip, what, e, boost::match_extra))
	{
		boost::smatch::iterator it = what.begin();
		++it;
		address = *it;
		++it;
		service = *it;
	}
}

void getAdress()
{
	cout << "Please input stream URL (ex. http://127.0.0.1:4773/ )\n";
	cin >> outputUrl;
	replace_or_merge(outputUrl, "http://", "tcp://");
}

void getName()
{
	cout << "Please your name (ex. georg )\n";
	cin >> outputUserName;
}

void initOpenCV()
{
	CamerasListNamespace::CamerasList* CamList = new CamerasListNamespace::CamerasList();
	cameraInt = CamList->SelectFromList();

	if (cameraInt == 999)
	{
		encoder.hasVideo = false;
	}
	else
	{
		/* initialize camera */
		capture = cvCaptureFromCAM(cameraInt);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, videoFrameRate);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, (double)videoWidth);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, (double)videoHeight);
	}

	if (!capture)
	{
		encoder.hasVideo = false;
		fprintf(stderr, "Cannot initialize selected webcam!\n");
		cout << endl;
		return;
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
	if (!noAudio)
	{
		nSampleSize = (int)(2.0f * audioSampleRate / fps);

		Buffer = new ALchar[nSampleSize];
		dev[0] = alcOpenDevice(NULL);
		if (NULL == dev[0])
		{
			fprintf(stderr, "No microphone found, please restart application , or continue streaming with out sound\n");
			boost::this_thread::sleep(boost::posix_time::seconds(9999999));
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

		//Get the name of the 'default' capture device
		//szDefaultCaptureDevice = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
		//printf("\nDefault Capture Device is '%s'\n\n", szDefaultCaptureDevice);

		int SelectedIndex = 999;
		if (i <= 0)
		{
			cout <<"No devices found. \n " << endl;
			//cout <<"Please restart application." << endl;
			//cin.get();
			//Sleep(999999);
			SelectedIndex = 999;
		}
		else
			if (i == 1)
			{
				cout <<"Default device will be used" << std::endl;
				SelectedIndex = 0;
				encoder.hasAudio = true;
			}
			else
			{
				while(SelectedIndex > i-1 || SelectedIndex < 0)
				{
					try
					{
						std::cout << "please input index from 0 to " << i - 1 << std::endl;
						std::string s;
						std::getline(cin, s, '\n');
						SelectedIndex = boost::lexical_cast<int>(s);
					}
					catch(std::exception&)
					{
						SelectedIndex = 999;
					}
				}
			}

		if (SelectedIndex == 999)
		{
			encoder.hasAudio = false;
		}
		else
		{
			encoder.hasAudio = true;
			alDistanceModel(AL_NONE);
			dev[0] = alcCaptureOpenDevice(bufferList[SelectedIndex], audioSampleRate, AL_FORMAT_MONO16, nSampleSize/2);
			alcCaptureStart(dev[0]);
			//ToDo: Refactor nBlockAlign == number of channels * Bits per sample / 8 ; btw: why /8?
			nBlockAlign = 1 * 16 / 8;
		}
	}
	else
	{
		encoder.hasAudio = false;
	}
}

void initFFmpeg(string container, int w, int h, int fps)
{
	if (!encoder.hasAudio && !encoder.hasVideo)
	{
		cout << "\nNo audio, and no video data found.\n Please close application.\nConnect some capturing device.\nRestart application\n";
		cin.get();
		boost::this_thread::sleep(boost::posix_time::seconds(9999999));
		cin.get();
	}
	encoder.SetConstants(fps, videoWidth, videoHeight, audioSampleRate, streamBitRate);

name:
	int encoderName = encoder.ConnectUserToUrl(outputUserName);
	if (encoderName == 0)
	{
		//printf("Cannot open stream for selected name\n");
		getName();
		int encoderServer = encoder.ConnectToServer(outputUrl) ;
		goto name;
	}

	if (encoder.InitUrl(container, outputUrl, outputUserName) == -10)
	{
		cout << "\nNo audio, and no video data found.\n Please close application.\nConnect some capturing device.\nRestart application\n";
		cin.get();
		boost::this_thread::sleep(boost::posix_time::seconds(9999999));
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
	CVframe = cvQueryFrame(capture);
	if (!CVframe)
	{
		printf("No CV frame captured!\n");
		cin.get();
	}

	cvResize(CVframe, destination);
	if (useLSD)
	{
		IplImage *destinationForLSD = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
		cvCvtColor(destination, destinationForLSD, CV_RGB2GRAY);

		image_double lsdImage;
		ntuple_list lsdOut;
		lsdImage = new_image_double(w, h);

		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++)
				lsdImage->data[x + y * lsdImage->xsize] = cvGetReal2D(destinationForLSD, y, x);

		// call LSD
		lsdOut = lsd(lsdImage);

		for (unsigned int i = 0; i < lsdOut->size; i++)
		{
			CvPoint pt1 = { (int)lsdOut->values[i * lsdOut->dim + 0], (int)lsdOut->values[i * lsdOut->dim + 1] };
			CvPoint pt2 = { (int)lsdOut->values[i * lsdOut->dim + 2], (int)lsdOut->values[i * lsdOut->dim + 3] };
			cvLine(destination, pt1, pt2, CV_RGB(240, 255, 255), 1, CV_AA, 0);
		}
		cvReleaseImage(&destinationForLSD);
		free_image_double(lsdImage);
		free_ntuple_list(lsdOut);
	}

	for (int i = 0; i < destination->imageSize; i = i + 3)
	{
		buffer[2] = destination->imageData[i];
		buffer[1] = destination->imageData[i + 1];
		buffer[0] = destination->imageData[i + 2];
		buffer += 3;
	}

	//cvSplit(destination, bluechannel, greenchannel, redchannel, NULL);
	//for(int y = 0; y < destination->height; y++)
	//{
	//	char* line = buffer + y * bytespan;
	//	for(int x = 0; x < destination->width; x++)
	//	{
	// 		line[0] = cvGetReal2D(redchannel, y, x);
	// 		line[1] = cvGetReal2D(greenchannel, y, x);
	// 		line[2] = cvGetReal2D(bluechannel, y, x);
	// 		line += 3;
	//	}
	//}

	//for (int i = 0; i < w * h * 3; ++i) {
	// 		buffer[i] = destination->imageData;
	//}
}

char* CaptureSample()
{
	// Check how much audio data has been captured (note that 'val' is the number of frames, not bytes)
	alcGetIntegerv(dev[0], ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	// When we would have enough data to fill our BUFFERSIZE byte buffer, will grab the samples, so now we should wait
	while (iSamplesAvailable < (nSampleSize / nBlockAlign) - 1) // -1 was added to make code run on Mac OS X, potential bug
		alcGetIntegerv(dev[0], ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	// Consume Samples
	alcCaptureSamples(dev[0], Buffer, (nSampleSize / nBlockAlign) - 1);
	return (char*)Buffer;
}

void closeOpenCV()
{
	cvReleaseCapture(&capture);
	//cvReleaseImage(&destination);
	//cvReleaseImage(&CVframe);
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
		while (true)
		{
			timerForCaptureFame.restart();
			CaptureFrame(videoWidth, videoHeight, (char*)frame->data[0], frame->linesize[0]);
			AVFrame* swap = frame;
			frame = readyFrame;
			readyFrame = swap;
			spendedTimeForCaptureFame = (int64_t)timerForCaptureFame.elapsed();
			if (spendedTimeForCaptureFame < desiredTimeForCaptureFame)
				boost::this_thread::sleep(boost::posix_time::milliseconds(desiredTimeForCaptureFame - spendedTimeForCaptureFame));
		}
	}
}

void ThreadSaveFrame()
{
	while (true)
	{
		timerForMain.restart();
		if (!encoder.hasVideo)
			if (!encoder.AddFrame(CaptureSample(), nSampleSize))
				printf("Cannot write frame!\n");

		if (!encoder.hasAudio)
			if (!encoder.AddFrame(readyFrame))
				printf("Cannot write frame!\n");
		
		if (encoder.hasAudio && encoder.hasVideo)
			if (!encoder.AddFrame(readyFrame, CaptureSample(), nSampleSize))
				printf("Cannot write frame!\n");
		
		if (!encoder.hasAudio && !encoder.hasVideo)
		{
			printf("No data to encode");
			break;
		}

		spendedTimeForMain = (int64_t)timerForMain.elapsed();
		if(spendedTimeForMain < desiredTimeForMain)
			boost::this_thread::sleep(boost::posix_time::milliseconds(desiredTimeForMain - spendedTimeForMain));
	}
}

int main(int argc, char* argv[])
{
	cameraInt = 0;
	videoFrameRate = 15;
	videoWidth = 1024;
	videoHeight =  768;
	microphoneInt = 1;
	audioSampleRate = 44100;
	outputContainer +="flv";
	streamBitRate = (int)(1.5 * videoWidth * 1024);
	noAudio = false;
	for (int i = 1; i < argc; i = i + 2)
	{
		if (string(argv[i]) == "-camera")
			cameraInt = atoi(argv[i + 1]);
		if (string(argv[i]) == "-framerate")
			videoFrameRate = atoi(argv[i + 1]);
		if (string(argv[i]) == "-width")
			videoWidth = atoi(argv[i + 1]);
		if (string(argv[i]) == "-height")
			videoHeight = atoi(argv[i + 1]);
		if (string(argv[i]) == "-microphone")
			microphoneInt = atoi(argv[i + 1]);
		if (string(argv[i]) == "-samplerate")
			audioSampleRate = atoi(argv[i + 1]);
		if (string(argv[i]) == "-server")
			outputUrl = argv[i + 1];
		if (string(argv[i]) == "-container")
			outputContainer = argv[i + 1];
		if (string(argv[i]) == "-nickname")
			outputUserName = argv[i + 1];
		if (string(argv[i]) == "-useLSD")
			useLSD = atoi(argv[i + 1]);
		if (string(argv[i]) == "-streamBitRate")
			streamBitRate = atoi(argv[i + 1]);
		if (string(argv[i]) == "-noAudio")
			noAudio = atoi(argv[i + 1]);
	}

	videoHeight = GetEvan(videoHeight);
	videoWidth = GetEvan(videoWidth);

	desiredTimeForCaptureFame = (int64_t)(1000.0f / videoFrameRate);
	desiredTimeForMain = (int64_t)(1000.0f / videoFrameRate);

	if(outputUrl == "")
	{
		cout << "Warning: No Cloud Observer server url found!" << endl;
		getAdress();
	}
	else
	{
		replace_or_merge(outputUrl, "http://", "tcp://");
	}

server:
	int encoderServer = encoder.ConnectToServer(outputUrl);
	if (encoderServer == -1)
	{
		//cout << "Cannot open stream URL\n";
		getAdress();
		goto server;
	}

	if (outputUserName == "")
	{
		cout << "Please provide us with your user name" << endl;
		getName();
	}

	init();

	boost::thread workerThread(ThreadCaptureFrame);
	boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	boost::thread workerThread2(ThreadSaveFrame);

	string quite;
	while (quite != "exit")
	{
		cout << "\nInput 'exit' to quite" << endl;
		cin >> quite;
		//cout << endl;
		boost::this_thread::sleep(boost::posix_time::milliseconds(250));
	}

	workerThread2.interrupt();
	workerThread.interrupt();
	boost::this_thread::sleep(boost::posix_time::milliseconds(250));
	close();
	return 0;
}
