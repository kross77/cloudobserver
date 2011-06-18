#include "audio_capturer.h"

audio_capturer::audio_capturer(ALCuint audio_sample_rate, ALCenum audio_format, int capture_size)
{
	this->sample_rate = audio_sample_rate;
	this->format = audio_format;
	this->capture_size = capture_size;

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
	this->buffer = new ALchar[this->sample_rate * this->format_multiplier];
}

audio_capturer::~audio_capturer()
{
}

void audio_capturer::connect(audio_player* audio_player_block)
{
	this->audio_player_block = audio_player_block;
}

void audio_capturer::disconnect()
{
}

void audio_capturer::start(ALCchar* audio_capture_device)
{
	this->capture_device = alcCaptureOpenDevice(audio_capture_device, this->sample_rate, this->format, this->sample_rate);
	alcCaptureStart(this->capture_device);

	this->capture_thread = new boost::thread(&audio_capturer::capture_loop, this);
}

void audio_capturer::stop()
{
	this->capture_thread->interrupt();

	alcCaptureStop(this->capture_device);
	alcCaptureCloseDevice(this->capture_device);
	this->capture_device = NULL;
}

void audio_capturer::set_capture_size(int capture_size)
{
	this->capture_size = capture_size;

	// clear the internal buffer
	int captured_samples;
	alcGetIntegerv(this->capture_device, ALC_CAPTURE_SAMPLES, 1, &captured_samples);
	alcCaptureSamples(this->capture_device, this->buffer, captured_samples);
}

void audio_capturer::capture_loop()
{
	int captured_samples;
	while (true)
	{
		alcGetIntegerv(this->capture_device, ALC_CAPTURE_SAMPLES, 1, &captured_samples);

		if (captured_samples >= this->capture_size)
		{
			alcCaptureSamples(this->capture_device, this->buffer, this->capture_size);
			this->audio_player_block->send(this->buffer, this->capture_size * this->format_multiplier);
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000 * this->capture_size / this->sample_rate));
	}
}
