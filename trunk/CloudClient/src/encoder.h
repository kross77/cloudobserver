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
	void add_frame(AVFrame* frame, const char* sound_buffer, int sound_buffer_size);
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
	transmitter* transmitter;
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
	
	// Add audio stream.
	AVStream* add_audio_stream(AVFormatContext* pContext, CodecID codec_id);
	// Add video stream.
	AVStream* add_video_stream(AVFormatContext* pContext, CodecID codec_id);

	// Open audio stream.
	bool open_audio_stream(AVFormatContext* pContext, AVStream* pStream);
	// Open video stream.
	bool open_video_stream(AVFormatContext* oc, AVStream* pStream);

	// Close audio stream.
	void close_audio_stream(AVFormatContext* pContext, AVStream* pStream);
	// Close video stream.
	void close_video_stream(AVFormatContext* pContext, AVStream* pStream);

	// Add audio frame.
	bool add_audio_frame(AVFormatContext* pFormatContext, AVStream* pStream, const char* soundBuffer, int soundBufferSize);
	// Add video frame.
	bool add_video_frame(AVFormatContext* pFormatContext, AVFrame* pOutputFrame, AVCodecContext* pVideoCodec);

	// Allocate memory.
	AVFrame* create_avframe(int pix_fmt, int nWidth, int nHeight);
	// Free resources.
	void free();
	// Check whether to convert pixel format.
	bool need_convert();
};

#endif // ENCODER_H
