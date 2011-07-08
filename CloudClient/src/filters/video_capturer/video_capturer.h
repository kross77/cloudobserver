#ifndef VIDEO_CAPTURER_H
#define VIDEO_CAPTURER_H

// Allow C99 macros.
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

// Boost
#include <boost/asio.hpp>
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
#include <string>
#include <vector>

class video_capturer
{
public:
	video_capturer(int video_width, int video_height, int video_frame_rate);
	~video_capturer();
	void connect(video_encoder* video_encoder_block);
	void disconnect();
	void start();
	void stop();
	void set_capture_device(int capture_device_index);

	class internal_exception: public std::exception { };
private:
	void capture_loop();

	int width;
	int height;
	int frame_rate;

	IplImage* captured_frame;
	IplImage* resized_frame;

	AVFrame* frame;

	CvCapture* capture_device;
	boost::thread* capture_thread;

	video_encoder* video_encoder_block;
};

#endif // VIDEO_CAPTURER_H
