#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

// Allow C99 macros.
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

// FFmpeg
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include "transmitter.h"

class multiplexer
{
public:
	multiplexer(std::string container);
	~multiplexer();
	void connect(transmitter* transmitter_block);
	void disconnect();
	AVFormatContext* get_format_context();
	void send(AVPacket* packet);
	
	class internal_exception: public std::exception { };
private:
	AVFormatContext* format_context;
	transmitter* transmitter_block;
};

#endif // MULTIPLEXER_H
