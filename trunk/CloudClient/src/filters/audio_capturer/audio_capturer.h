#ifndef AUDIO_CAPTURER_H
#define AUDIO_CAPTURER_H

// Boost
#include <boost/thread.hpp>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>

#include "../audio_player/audio_player.h"

#include "../../utils/selector/selector.h"

#include <iostream>
#include <windows.h>

class audio_capturer
{
public:
	audio_capturer(ALCuint audio_sample_rate, ALCenum audio_format, int capture_size);
	~audio_capturer();
	void connect(audio_player* audio_player_block);
	void disconnect();
	void start(ALCchar* audio_capture_device);
	void stop();
	void set_capture_size(int capture_size);

	class internal_exception: public std::exception { };
private:
	void capture_loop();

	ALCuint sample_rate;
	ALCenum format;
	int capture_size;

	int format_multiplier;
	ALchar* buffer;

	ALCdevice* capture_device;
	boost::thread* capture_thread;

	audio_player* audio_player_block;
};

#endif // AUDIO_CAPTURER_H
