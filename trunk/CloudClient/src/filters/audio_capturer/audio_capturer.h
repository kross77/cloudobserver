#ifndef AUDIO_CAPTURER_H
#define AUDIO_CAPTURER_H

// Boost
#include <boost/thread.hpp>

#include "../audio_player/audio_player.h"
#include "../audio_encoder/audio_encoder.h"

#include "../../3rdparty/openal/openal.h"

#include <iostream>
#include <string>
#include <vector>

#define DEFAULT_SAMPLE_RATE 44100
#define DEFAULT_FORMAT AL_FORMAT_MONO16
#define DEFAULT_CAPTURE_SIZE 1470

class audio_capturer
{
public:
	audio_capturer(int audio_sample_rate = DEFAULT_SAMPLE_RATE, int audio_format = DEFAULT_FORMAT, int capture_size = DEFAULT_CAPTURE_SIZE);
	~audio_capturer();
	void connect(audio_player* audio_player_block);
	void connect(audio_encoder* audio_encoder_block);
	void disconnect();
	void start();
	void stop();
	void set_capture_device(int capture_device_index);
	void set_capture_size(int capture_size);

	static std::vector<std::string> get_capture_devices();

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
	audio_encoder* audio_encoder_block;
};

#endif // AUDIO_CAPTURER_H
