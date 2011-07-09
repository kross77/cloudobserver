#ifndef VIDEO_CAPTURER_H
#define VIDEO_CAPTURER_H

// Boost
#include <boost/asio.hpp>
#include <boost/thread.hpp>

// OpenCV
#include <opencv2/opencv.hpp>

#include "../line_segment_detector/line_segment_detector.h"
#include "../video_encoder/video_encoder.h"

#include "../../3rdparty/ffmpeg/ffmpeg.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#ifdef WIN
#pragma comment(lib, "strmiids")
#include <comdef.h>
#include <dshow.h>
#include <windows.h>
#endif

#ifdef LIN
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#endif

#ifdef MAC
#include <QuickTime/QuickTime.h>
#endif

class video_capturer
{
public:
	video_capturer(int video_width, int video_height, int video_frame_rate);
	~video_capturer();
	void connect(line_segment_detector* line_segment_detector_block);
	void connect(video_encoder* video_encoder_block);
	void disconnect();
	void start();
	void stop();
	void set_capture_device(int capture_device_index);

	static std::vector<std::string> get_capture_devices();

	class internal_exception: public std::exception { };
private:
	void capture_loop();

	int width;
	int height;
	int frame_rate;

	IplImage* captured_frame;
	IplImage* resized_frame;

	ffmpeg::AVFrame* frame;

	CvCapture* capture_device;
	boost::thread* capture_thread;

	line_segment_detector* line_segment_detector_block;
	video_encoder* video_encoder_block;
};

#endif // VIDEO_CAPTURER_H
