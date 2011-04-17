#ifndef AUDIO_ENCODER_H
#define AUDIO_ENCODER_H

// The maximum audio packet size.
#define MAX_AUDIO_PACKET_SIZE (128 * 1024)

// The buffer size.
#define BUFFER_SIZE (1024 * 1024 * 4)

// The encode buffer size.
#define ENCODE_BUFFER_SIZE (4 * MAX_AUDIO_PACKET_SIZE)

// FFmpeg
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include "multiplexer.h"

class audio_encoder
{
public:
	audio_encoder(int samplerate);
	~audio_encoder();
	void connect(multiplexer* multiplexer_block);
	void disconnect();
	void send(const char* data, int size);

	class internal_exception: public std::exception { };
private:
	int samplerate;

	AVStream* stream;

	char* buffer;
	int buffer_position;

	uint8_t* encode_buffer;

	multiplexer* multiplexer_block;
};

#endif // AUDIO_ENCODER_H
