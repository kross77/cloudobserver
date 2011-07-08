#include "video_capturer.h"

video_capturer::video_capturer(int video_width, int video_height, int video_frame_rate)
{
	this->width = video_width;
	this->height = video_height;
	this->frame_rate = video_frame_rate;

	this->captured_frame = NULL;
	this->resized_frame = NULL;

	this->frame = avcodec_alloc_frame();
	uint8_t* frame_buffer = (uint8_t*)av_mallocz(avpicture_get_size(PIX_FMT_BGR24, this->width, this->height));
	avpicture_fill((AVPicture*)frame, frame_buffer, PIX_FMT_BGR24, this->width, this->height);

	this->capture_device = NULL;
	this->capture_thread = NULL;

	this->video_encoder_block = NULL;

	this->set_capture_device(0);
}

video_capturer::~video_capturer()
{
	cvReleaseCapture(&this->capture_device);

	av_free(this->frame->data[0]);
	av_free(this->frame);
}

void video_capturer::connect(video_encoder* video_encoder_block)
{
	this->video_encoder_block = video_encoder_block;
}

void video_capturer::disconnect()
{
	this->video_encoder_block = NULL;
}

void video_capturer::start()
{
	this->capture_thread = new boost::thread(&video_capturer::capture_loop, this);
}

void video_capturer::stop()
{
	this->capture_thread->interrupt();
}

void video_capturer::set_capture_device(int capture_device_index)
{
	if (this->capture_device != NULL)
	{
		cvReleaseCapture(&this->capture_device);
		this->capture_device = NULL;
	}

	this->capture_device = cvCreateCameraCapture(capture_device_index);
	if (this->capture_device == NULL)
	{
		std::cout << "Video capturer: cannot initialize video capture device." << std::endl;
		throw internal_exception();
	}

	cvSetCaptureProperty(this->capture_device, CV_CAP_PROP_FRAME_WIDTH, this->width);
	cvSetCaptureProperty(this->capture_device, CV_CAP_PROP_FRAME_HEIGHT, this->height);
	cvSetCaptureProperty(this->capture_device, CV_CAP_PROP_FPS, this->frame_rate);

	this->captured_frame = cvQueryFrame(this->capture_device);
	this->resized_frame = cvCreateImage(cvSize(this->width, this->height), this->captured_frame->depth, this->captured_frame->nChannels);
}

void video_capturer::capture_loop()
{
	while (true)
	{
		this->captured_frame = cvQueryFrame(this->capture_device);
		cvResize(this->captured_frame, this->resized_frame);

		char* buffer = (char*)this->frame->data[0];
		for (int i = 0; i < this->resized_frame->imageSize; i += 3)
		{
			buffer[2] = this->resized_frame->imageData[i];
			buffer[1] = this->resized_frame->imageData[i + 1];
			buffer[0] = this->resized_frame->imageData[i + 2];
			buffer += 3;
		}

		this->video_encoder_block->send(this->frame);

		boost::this_thread::sleep(boost::posix_time::milliseconds(1000 / this->frame_rate));
	}
}
