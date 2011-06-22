#include "audio_player.h"

audio_player::audio_player(ALsizei audio_sample_rate, ALenum audio_format)
{
	this->sample_rate = audio_sample_rate;
	this->format = audio_format;

	this->device = alcOpenDevice(NULL);
	this->context = alcCreateContext(this->device, NULL);
	alcMakeContextCurrent(this->context);

	this->sources = new ALuint[1];
	alGenSources(1, this->sources);

	this->buffers = new ALuint[BUFFERS];
	alGenBuffers(BUFFERS, this->buffers);

	for (int i = 0; i < BUFFERS; ++i)
		this->queue.push_back(this->buffers[i]);
}

audio_player::~audio_player()
{
	alSourceStop(this->sources[0]);
	alSourcei(this->sources[0], AL_BUFFER, AL_NONE);

	alDeleteSources(1, this->sources);
	alDeleteBuffers(BUFFERS, this->buffers);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}

void audio_player::send(const char* data, int size)
{
	ALint processed;
	alGetSourcei(this->sources[0], AL_BUFFERS_PROCESSED, &processed);
	if (processed > 0)
	{
		ALuint processed_buffers[BUFFERS];
		alSourceUnqueueBuffers(this->sources[0], processed, processed_buffers);
		for (int i = 0; i < processed; ++i)
			queue.push_back(processed_buffers[i]);
	}

	if (!queue.empty())
	{
		ALuint buffer = queue.front();
		queue.pop_front();

		alBufferData(buffer, this->format, data, size, this->sample_rate);
		alSourceQueueBuffers(this->sources[0], 1, &buffer);

		ALint state = 0;
		alGetSourcei(this->sources[0], AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING)
			alSourcePlay(this->sources[0]);
	}
}
