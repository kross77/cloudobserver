
#ifndef __STDC_CONSTANT_MACROS
  #define __STDC_CONSTANT_MACROS
#endif

// FFmpeg
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

// Boost
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/timer.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <queue>

#ifndef _VIDEO_ENCODER_H__
#define _VIDEO_ENCODER_H__

using namespace std;

class VideoEncoder
{
private:

	// output file name
	std::string     outputFilename;
	// output format.
	AVOutputFormat  *pOutFormat;
	// format context
	AVFormatContext *pFormatContext;
	// video stream context
	AVStream * pVideoStream;
	// audio streams context
	AVStream * pAudioStream;
	// convert context context
	struct SwsContext *pImgConvertCtx;
	// encode buffer and size
	uint8_t * pVideoEncodeBuffer;
	int nSizeVideoEncodeBuffer;

	// audio buffer and size
	uint8_t * pAudioEncodeBuffer;
	int nSizeAudioEncodeBuffer;


	// count of sample
	int audioInputSampleSize;
	// current picture
	AVFrame *pCurrentPicture;

	// audio buffer
	char* audioBuffer;
	int   nAudioBufferSize;
	int   nAudioBufferSizeCurrent;


public:

	struct AudioSample
	{	
		const unsigned char * buffer;
		int len;
	};

	struct VideoSample
	{	
		const unsigned char * buffer;
		int len;
	};



	bool sampleSendingFinished;
	bool frameSendingFinished;

	URLContext * url_context;
	int fps;
	int width;	// pixels
	int height	;	// pixels
	int audioSampleRate	;	// hertz
	int vbr;
	std::string userName;
	bool hasAudio;
	bool hasVideo;
		
	VideoEncoder() 
	{
		//  url_context = NULL;
		pOutFormat = NULL;
		pFormatContext = NULL;
		pVideoStream = NULL;
		pImgConvertCtx = NULL;
		pCurrentPicture = NULL;
		pVideoEncodeBuffer = NULL;
		nSizeVideoEncodeBuffer = 0;
		pAudioEncodeBuffer = NULL;
		nSizeAudioEncodeBuffer = 0;
		nAudioBufferSize = 1024 * 1024 * 4;
		audioBuffer      = new char[nAudioBufferSize];
		nAudioBufferSizeCurrent = 0;
		fps = 7;
		frameSendingFinished = true;
		hasAudio = false;
		hasVideo = false;
	}

	virtual ~VideoEncoder() 
	{
		Finish();
	}
	//set constants
	void SetConstants( int UserFps , int UserWidth, int UserHeight, int UserAudioSampleRate, int videoBitRate);
	// init output stream 	

	int ConnectToServer(std::string& tcpUrl);
	int ConnectUserToUrl(std::string& username);
	int InitUrl(std::string& container, std::string& tcpUrl, std::string& username); // 1 all is ok, 0 not correct user name, -1 not correct URL
	// Add video and audio data

	bool AddFrame(AVFrame* frame, const char* soundBuffer, int soundBufferSize);
		bool AddFrame(AVFrame* frame);
			bool AddFrame(const char* soundBuffer, int soundBufferSize);
	// end of output
	bool Finish();

private: 
	int ReadFromServer();
	void UrlWriteFrame(URLContext *h, const unsigned char *buf, int size );
	void UrlWriteSample( URLContext *h, const unsigned char *buf, int size );
	int TryWriteToUrl(const unsigned char *buf, int size);
	void WriteToUrl(const unsigned char *buf, int size);

	void tcpExtract(std::string const& ip, std::string& address, std::string& service);
	// Add video stream
	AVStream *AddVideoStream(AVFormatContext *pContext, CodecID codec_id);
	// Open Video Stream
	bool OpenVideo(AVFormatContext *oc, AVStream *pStream);
	// Allocate memory
	AVFrame * CreateFFmpegPicture(int pix_fmt, int nWidth, int nHeight);
	// Close video stream
	void CloseVideo(AVFormatContext *pContext, AVStream *pStream);
	// Add audio stream
	AVStream * AddAudioStream(AVFormatContext *pContext, CodecID codec_id);
	// Open audio stream
	bool OpenAudio(AVFormatContext *pContext, AVStream *pStream);
	// close audio stream
	void CloseAudio(AVFormatContext *pContext, AVStream *pStream);
	// Add video frame
	bool AddVideoFrame(AVFormatContext *pFormatContext, AVFrame * pOutputFrame, AVCodecContext *pVideoCodec);
	// Add audio samples
	bool AddAudioSample(AVFormatContext *pFormatContext,  AVStream *pStream, const char* soundBuffer, int soundBufferSize);
	// Free recourses. ToDo: Check, if it all works fine kill it.
	void Free();
	bool NeedConvert();

};

#endif // _VIDEO_ENCODER_H__
