#ifndef VIDEO_GENERATOR_RAINBOW_H
#define VIDEO_GENERATOR_RAINBOW_H

#define _USE_MATH_DEFINES

// Allow C99 macros.
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

// Boost
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>

// FFmpeg
extern "C"
{
#include <libavcodec/avcodec.h>
}

#include "../video_encoder/video_encoder.h"

#include <cmath>
#include <exception>
#include <iostream>

class video_generator_rainbow
{
public:
	video_generator_rainbow(int video_width, int video_height, int video_frame_rate);
	~video_generator_rainbow();
	void connect(video_encoder* video_encoder_block);
	void disconnect();
	void start();
	void stop();

	class internal_exception: public std::exception { };
private:
	void generation_loop();

	int width;
	int height;
	int frame_rate;

	AVFrame* frame;

	boost::thread* generation_thread;

	video_encoder* video_encoder_block;
};

#endif // VIDEO_GENERATOR_RAINBOW_H
