#include "video_generator_rainbow.h"

using namespace ffmpeg;

video_generator_rainbow::video_generator_rainbow(int video_width, int video_height, int video_frame_rate)
{
	this->width = video_width;
	this->height = video_height;
	this->frame_rate = video_frame_rate;

	this->frame = avcodec_alloc_frame();
	uint8_t* frame_buffer = (uint8_t*)av_mallocz(avpicture_get_size(PIX_FMT_BGR24, this->width, this->height));
	avpicture_fill((AVPicture*)frame, frame_buffer, PIX_FMT_BGR24, this->width, this->height);

	this->generation_thread = NULL;

	this->video_encoder_block = NULL;
}

video_generator_rainbow::~video_generator_rainbow()
{
	av_free(this->frame->data[0]);
	av_free(this->frame);
}

void video_generator_rainbow::connect(video_encoder* video_encoder_block)
{
	this->video_encoder_block = video_encoder_block;
}

void video_generator_rainbow::disconnect()
{
	this->video_encoder_block = NULL;
}

void video_generator_rainbow::start()
{
	this->generation_thread = new boost::thread(&video_generator_rainbow::generation_loop, this);
}

void video_generator_rainbow::stop()
{
	this->generation_thread->interrupt();
}

void video_generator_rainbow::generation_loop()
{
	int wxh = this->width * this->height;
	while (true)
	{
		static float seed = 1.0;
		for (int i = 0; i < this->height; ++i)
		{
			char* line = (char*)this->frame->data[0] + i * this->frame->linesize[0];
			for (int j = 0; j < this->width; ++j)
			{
				line[0] = (char)(255 * sin(((float)i / wxh * seed) * M_PI));
				line[1] = (char)(255 * cos(((float)j / wxh * seed) * M_PI));
				line[2] = (char)(255 * sin(((float)(i + j) / wxh * seed) * M_PI));
				line += 3;
			}
		}
		seed = seed + 2.2f;

		this->video_encoder_block->send(this->frame);

		boost::this_thread::sleep(boost::posix_time::milliseconds(1000 / this->frame_rate));
	}
}
