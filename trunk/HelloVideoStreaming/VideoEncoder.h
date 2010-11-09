/*
  FFmpeg simple Encoder
 */


#ifndef __VIDEO_ENCODER_H__
#define __VIDEO_ENCODER_H__
#include "stdafx.h"
#include "ffmpegInclude.h"
#include <Windows.h>
#include <string>
#include <queue>
#include <iostream>

 // Boost
#include <boost/thread.hpp>
#include <boost/timer.hpp>

template<typename Data>
 class concurrent_queue
 {
 private:
	 std::queue<Data> the_queue;
	 mutable boost::mutex the_mutex;
	 boost::condition_variable the_condition_variable;
 public:
	 void push(Data const& data)
	 {
		 boost::mutex::scoped_lock lock(the_mutex);
		 the_queue.push(data);
		 lock.unlock();
		 the_condition_variable.notify_one();
	 }

	 bool empty() const
	 {
		 boost::mutex::scoped_lock lock(the_mutex);
		 return the_queue.empty();
	 }

	 bool try_pop(Data& popped_value)
	 {
		 boost::mutex::scoped_lock lock(the_mutex);
		 if(the_queue.empty())
		 {
			 return false;
		 }

		 popped_value=the_queue.front();
		 the_queue.pop();
		 return true;
	 }

	 void wait_and_pop(Data& popped_value)
	 {
		 boost::mutex::scoped_lock lock(the_mutex);
		 while(the_queue.empty())
		 {
			 the_condition_variable.wait(lock);
		 }

		 popped_value=the_queue.front();
		 the_queue.pop();
	 }
	
	 Data& front()
	 {
		 boost::mutex::scoped_lock lock(the_mutex);
		 return the_queue.front();
	 }



 };


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

		 // const unsigned char * VideoFrameBuffer;
		//  int VideoFrameLen;
	  concurrent_queue<AudioSample * > AudioSamples;
	  concurrent_queue<VideoSample * > VideoSamples;
	 


	  bool sampleSendingFinished;
	  bool frameSendingFinished;
	 
	  URLContext * url_context;
  int fps;
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
  }
  
  virtual ~VideoEncoder() 
  {
    Finish();
  }
  //set fps
  void SetFps(int UserFps);
  // init output stream 
  bool InitUrl(std::string& container, std::string& tcpUrl);
  // Add video and audio data
  bool AddFrame(AVFrame* frame, const char* soundBuffer, int soundBufferSize);
  // end of output
  bool Finish();
   void UrlWriteFrame(URLContext *h, const unsigned char *buf, int size );
     void UrlWriteSample( URLContext *h, const unsigned char *buf, int size );
  private: 
 
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
  void UrlWriteData();
  void AddSampleToQueue(const unsigned char *buf, int size );
  void AddFrameToQueue(const unsigned char *buf, int size );
};


#endif // __VIDEO_ENCODER_H__
