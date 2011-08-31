#include "video_player.h"

video_player::video_player(std::string window_name, int width, int height)
{
	this->window_name = window_name;
	this->width = width;
	this->height = height;

	this->created = false;
}

video_player::~video_player()
{
	cvDestroyWindow(this->window_name.c_str());
}

void video_player::send(IplImage* frame)
{
	if (!this->created)
	{
		cvNamedWindow(this->window_name.c_str(), CV_WINDOW_AUTOSIZE);
		this->created = true;
	}

	IplImage* resized_frame = cvCreateImage(cvSize(this->width, this->height), frame->depth, frame->nChannels);
	cvResize(frame, resized_frame);
	cvShowImage(this->window_name.c_str(), resized_frame);
	cvReleaseImage(&resized_frame);
	cvWaitKey(1);
}
