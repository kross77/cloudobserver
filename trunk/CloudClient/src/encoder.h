#ifndef ENCODER_H
#define ENCODER_H

// The maximum audio packet size.
#define MAX_AUDIO_PACKET_SIZE (128 * 1024)

// Allow C99 macros.
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/timer.hpp>

// FFmpeg
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

#include "transmitter.h"

class encoder
{
public:
	encoder();
	~encoder();
	void init(int audio_samplerate, int video_bitrate, int video_framerate, int video_width, int video_height);
	void start(std::string& container);
	void add_frame(AVFrame* frame);
	void add_frame(const char* sound_buffer, int sound_buffer_size);
	void stop();

	int audio_samplerate;
	int video_bitrate;
	int video_framerate;
	int video_width;
	int video_height;

	bool has_audio;
	bool has_video;
	transmitter* transmitter_block;
private:
	// format context
	AVFormatContext* pFormatContext;
	// video stream context
	AVStream* pVideoStream;
	// audio stream context
	AVStream* pAudioStream;
	// convert context
	struct SwsContext* pImgConvertCtx;
	// encoded video buffer
	uint8_t* pVideoEncodeBuffer;
	// encoded video buffer size
	int nSizeVideoEncodeBuffer;
	// encoded audio buffer
	uint8_t* pAudioEncodeBuffer;
	// encoded audio buffer size
	int nSizeAudioEncodeBuffer;
	// count of sample
	int audioInputSampleSize;
	// current picture
	AVFrame* pCurrentPicture;
	// audio buffer
	int nAudioBufferSizeCurrent;
	int nAudioBufferSize;
	char* audioBuffer;
	
	// Initialize audio stream.
	void init_audio_stream();
	// Initialize video stream.
	void init_video_stream();

	// Open audio stream.
	void open_audio_stream();
	// Open video stream.
	void open_video_stream();

	// Close audio stream.
	void close_audio_stream();
	// Close video stream.
	void close_video_stream();

	// Add audio frame.
	bool add_audio_frame(AVStream* pStream, const char* soundBuffer, int soundBufferSize);
	// Add video frame.
	bool add_video_frame(AVFrame* pOutputFrame, AVCodecContext* pVideoCodec);
};

#endif // ENCODER_H
