#include "audio_generator.h"

audio_generator::audio_generator(int audio_sample_rate, int audio_format, int generation_size)
{
	this->sample_rate = audio_sample_rate;
	this->format = audio_format;
	this->generation_size = generation_size;

	switch (this->format)
	{
	case AL_FORMAT_MONO8:
		this->format_multiplier = 1;
		break;
	case AL_FORMAT_MONO16:
	case AL_FORMAT_STEREO8:
		this->format_multiplier = 2;
		break;
	case AL_FORMAT_STEREO16:
		this->format_multiplier = 4;
		break;
	}
	this->buffer = new char[this->sample_rate * this->format_multiplier];

	this->generation_thread = NULL;

	this->audio_player_block = NULL;
	this->audio_encoder_block = NULL;
}

audio_generator::~audio_generator()
{
}

void audio_generator::connect(audio_player* audio_player_block)
{
	this->audio_player_block = audio_player_block;
}

void audio_generator::connect(audio_encoder* audio_encoder_block)
{
	this->audio_encoder_block = audio_encoder_block;
}

void audio_generator::disconnect()
{
	this->audio_player_block = NULL;
	this->audio_encoder_block = NULL;
}

void audio_generator::start()
{
	this->generation_thread = new boost::thread(&audio_generator::generation_loop, this);
}

void audio_generator::stop()
{
	this->generation_thread->interrupt();
}

void audio_generator::set_generation_size(int generation_size)
{
	this->generation_size = generation_size;
}

void audio_generator::generation_loop()
{
	int amplitude = 2048;
	int frequency = 440;
	int time = 0;

	double angular_frequency = 2 * M_PI * frequency / (double)this->sample_rate;

	while (true)
	{
		switch (this->format)
		{
		case AL_FORMAT_MONO8:
			for (int i = 0; i < this->generation_size; ++i)
				buffer[i] = (char)(amplitude * sin(angular_frequency * time++));
			break;
		case AL_FORMAT_MONO16:
			for (int i = 0; i < this->generation_size; ++i)
				((short*)buffer)[i] = (short)(amplitude * sin(angular_frequency * time++));
			break;
		case AL_FORMAT_STEREO8:
			for (int i = 0; i < this->generation_size; ++i)
			{
				char value = (char)(amplitude * sin(angular_frequency * time++));
				buffer[2 * i] = value;
				buffer[2 * i + 1] = value;
			}
			break;
		case AL_FORMAT_STEREO16:
			for (int i = 0; i < this->generation_size; ++i)
			{
				short value = (short)(amplitude * sin(angular_frequency * time++));
				((short*)buffer)[2 * i] = value;
				((short*)buffer)[2 * i + 1] = value;
			}
			break;
		}
		
		if (this->audio_player_block != NULL)
			this->audio_player_block->send(this->buffer, this->generation_size * this->format_multiplier);

		if (this->audio_encoder_block != NULL)
			this->audio_encoder_block->send(this->buffer, this->generation_size * this->format_multiplier);

		boost::this_thread::sleep(boost::posix_time::milliseconds(1000 * this->generation_size / this->sample_rate));
	}
}
