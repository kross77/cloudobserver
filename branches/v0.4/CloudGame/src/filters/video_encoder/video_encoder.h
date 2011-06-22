#ifndef VIDEO_ENCODER_H
#define VIDEO_ENCODER_H

// The encode buffer size.
#define ENCODE_BUFFER_SIZE (1024 * 1024 * 10)

// Allow C99 macros.
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

// FFmpeg
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include "../multiplexer/multiplexer.h"

class video_encoder
{
public:
	video_encoder(int bitrate, int framerate, int width, int height);
	~video_encoder();
	void connect(multiplexer* multiplexer_block);
	void disconnect();
	void send(AVFrame* frame);

	class internal_exception: public std::exception { };
private:
	int bitrate;
	int framerate;
	int width;
	int height;

	AVStream* stream;

	bool raw_data;
	bool need_convert;

	uint8_t* encode_buffer;
	struct SwsContext* convert_context;

	multiplexer* multiplexer_block;
};

#endif // VIDEO_ENCODER_H
