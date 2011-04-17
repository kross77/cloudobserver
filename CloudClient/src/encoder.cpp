#include "encoder.h"

encoder::encoder() 
{
	this->has_audio = false;
	this->has_video = false;

	this->pFormatContext = NULL;
	this->pVideoStream = NULL;
	this->pAudioStream = NULL;
}

encoder::~encoder()
{
	stop();

	delete audio_encoder_block;
	delete video_encoder_block;
	delete multiplexer_block;
	delete transmitter_block;
}

void encoder::init(int audio_samplerate, int video_bitrate, int video_framerate, int video_width, int video_height)
{
	this->audio_samplerate = audio_samplerate;
	this->video_bitrate = video_bitrate;
	this->video_framerate = video_framerate;
	this->video_width = video_width;
	this->video_height = video_height;
}

void encoder::start(std::string& container)
{
	if (!has_audio && !has_video)
		throw std::runtime_error("No audio and no video.");

	multiplexer_block = new multiplexer(container);
	pFormatContext = multiplexer_block->get_format_context();

	if (has_audio)
	{
		audio_encoder_block = new audio_encoder(this->audio_samplerate);
		audio_encoder_block->connect(multiplexer_block);
	}
	
	if (has_video)
	{
		video_encoder_block = new video_encoder(this->video_bitrate, this->video_framerate, this->video_width, this->video_height);
		video_encoder_block->connect(multiplexer_block);
	}
	
	if (av_set_parameters(pFormatContext, NULL) < 0)
		throw std::runtime_error("av_set_parameters failed.");

	multiplexer_block->connect(transmitter_block);
}

void encoder::add_frame(AVFrame* frame)
{
	video_encoder_block->send(frame);
}

void encoder::add_frame(const char* sound_buffer, int sound_buffer_size)
{
	audio_encoder_block->send(sound_buffer, sound_buffer_size);
}

void encoder::stop()
{
	if (pFormatContext)
	{
		multiplexer_block->disconnect();

		// close audio stream.
		if (has_audio)
			audio_encoder_block->disconnect();

		// close video stream
		if (has_video)
			video_encoder_block->disconnect();

		// Free the streams.
		for(size_t i = 0; i < pFormatContext->nb_streams; i++) 
		{
			av_freep(&pFormatContext->streams[i]->codec);
			av_freep(&pFormatContext->streams[i]);
		}

		if (!(pFormatContext->flags & AVFMT_NOFILE) && pFormatContext->pb) 
		{
			//s.close();
		}

		// Free the stream.
		av_free(pFormatContext);
		pFormatContext = NULL;
	}
}
