#include "line_segment_detector.h"

line_segment_detector::line_segment_detector(int video_width, int video_height)
{
	this->width = video_width;
	this->height = video_height;

	this->output_frame = avcodec_alloc_frame();
	uint8_t* frame_buffer = (uint8_t*)av_mallocz(avpicture_get_size(PIX_FMT_BGR24, this->width, this->height));
	avpicture_fill((AVPicture*)output_frame, frame_buffer, PIX_FMT_BGR24, this->width, this->height);

	this->video_encoder_block = NULL;
}

line_segment_detector::~line_segment_detector()
{
}

void line_segment_detector::connect(video_encoder* video_encoder_block)
{
	this->video_encoder_block = video_encoder_block;
}

void line_segment_detector::disconnect()
{
	this->video_encoder_block = NULL;
}

void line_segment_detector::send(IplImage* frame)
{
	IplImage* grayscale_frame = cvCreateImage(cvSize(this->width, this->height), IPL_DEPTH_8U, 1);
	cvCvtColor(frame, grayscale_frame, CV_RGB2GRAY);

	image_double lsd_image = new_image_double(this->width, this->height);
	for (int x = 0; x < this->width; ++x)
		for (int y = 0; y < this->height; ++y)
			lsd_image->data[x + y * lsd_image->xsize] = cvGetReal2D(grayscale_frame, y, x);

	ntuple_list lsd_out = lsd(lsd_image);

	for (unsigned int i = 0; i < lsd_out->size; ++i)
	{
		CvPoint pt1 = { (int)lsd_out->values[i * lsd_out->dim + 0], (int)lsd_out->values[i * lsd_out->dim + 1] };
		CvPoint pt2 = { (int)lsd_out->values[i * lsd_out->dim + 2], (int)lsd_out->values[i * lsd_out->dim + 3] };
		cvLine(frame, pt1, pt2, CV_RGB(240, 255, 255), 1, CV_AA, 0);
	}
	cvReleaseImage(&grayscale_frame);
	free_image_double(lsd_image);
	free_ntuple_list(lsd_out);

	char* buffer = (char*)this->output_frame->data[0];
	for (int i = 0; i < frame->imageSize; i += 3)
	{
		buffer[2] = frame->imageData[i];
		buffer[1] = frame->imageData[i + 1];
		buffer[0] = frame->imageData[i + 2];
		buffer += 3;
	}

	this->video_encoder_block->send(this->output_frame);
}
