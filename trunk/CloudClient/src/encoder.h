#ifndef ENCODER_H
#define ENCODER_H

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

#include "audio_encoder.h"
#include "video_encoder.h"
#include "multiplexer.h"
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
	audio_encoder* audio_encoder_block;
	video_encoder* video_encoder_block;
	multiplexer* multiplexer_block;
	transmitter* transmitter_block;
private:
	// format context
	AVFormatContext* pFormatContext;
	// video stream context
	AVStream* pVideoStream;
	// audio stream context
	AVStream* pAudioStream;
};

#endif // ENCODER_H
