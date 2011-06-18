#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#define BUFFERS 16

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>

#include <list>

class audio_player
{
public:
	audio_player(ALsizei audio_sample_rate, ALenum audio_format);
	~audio_player();

	void send(const char* data, int size);

	class internal_exception: public std::exception { };
private:
	ALsizei sample_rate;
	ALenum format;

	ALCdevice* device;
	ALCcontext* context;
	ALuint* sources;
	ALuint* buffers;

	std::list<ALuint> queue;
};

#endif // AUDIO_PLAYER_H
