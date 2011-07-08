#ifndef VIDEO_GENERATOR_H
#define VIDEO_GENERATOR_H

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

// OpenCV
#include <opencv2/opencv.hpp>

#include "../video_encoder/video_encoder.h"

#include <exception>
#include <iostream>

class video_generator
{
public:
	video_generator(int video_width, int video_height, int video_frame_rate, std::string username);
	~video_generator();
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

	CvFont font;

	IplImage* blank_frame;
	IplImage* resized_frame;

	AVFrame* frame;

	boost::thread* generation_thread;

	video_encoder* video_encoder_block;
};

#endif // VIDEO_GENERATOR_H
