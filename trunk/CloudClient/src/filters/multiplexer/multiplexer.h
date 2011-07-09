#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

// Boost
#include <boost/thread.hpp>

#include "../transmitter/transmitter.h"

#include "../../3rdparty/ffmpeg/ffmpeg.h"

class multiplexer
{
public:
	multiplexer(std::string container);
	~multiplexer();
	void connect(transmitter* transmitter_block);
	void disconnect();
	ffmpeg::AVFormatContext* get_format_context();
	void send(ffmpeg::AVPacket* packet);
	
	class internal_exception: public std::exception { };
private:
	ffmpeg::AVFormatContext* format_context;

	mutable boost::mutex send_mutex;

	transmitter* transmitter_block;
};

#endif // MULTIPLEXER_H
