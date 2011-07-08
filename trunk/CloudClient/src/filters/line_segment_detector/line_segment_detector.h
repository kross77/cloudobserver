#ifndef LINE_SEGMENT_DETECTOR_H
#define LINE_SEGMENT_DETECTOR_H

// Allow C99 macros.
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

// Boost
#include <boost/asio.hpp>

// FFmpeg
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

// OpenCV
#include <opencv2/opencv.hpp>

#include "../video_encoder/video_encoder.h"

#include "../../3rdparty/lsd/lsd.h"

#include <exception>
#include <iostream>

class line_segment_detector
{
public:
	line_segment_detector(int video_width, int video_height);
	~line_segment_detector();
	void connect(video_encoder* video_encoder_block);
	void disconnect();
	void send(IplImage* frame);

	class internal_exception: public std::exception { };
private:
	int width;
	int height;

	AVFrame* output_frame;

	video_encoder* video_encoder_block;
};

#endif // LINE_SEGMENT_DETECTOR_H
