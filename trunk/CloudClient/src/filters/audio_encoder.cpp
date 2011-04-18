#include "audio_encoder.h"

audio_encoder::audio_encoder(int samplerate)
{
	this->samplerate = samplerate;

	this->stream = NULL;

	this->buffer = new char[BUFFER_SIZE];
	this->buffer_position = 0;

	this->encode_buffer = (uint8_t*)av_malloc(ENCODE_BUFFER_SIZE);
	
	this->multiplexer_block = NULL;
}

audio_encoder::~audio_encoder()
{
	this->disconnect();

	delete this->buffer;
	av_free(this->encode_buffer);
}

void audio_encoder::connect(multiplexer* multiplexer_block)
{
	this->multiplexer_block = multiplexer_block;
	AVFormatContext* format_context = this->multiplexer_block->get_format_context();

	this->stream = av_new_stream(format_context, 1);
	if (this->stream == NULL)
	{
		std::cout << "Audio encoder: cannot initialize audio stream." << std::endl;
		throw internal_exception();
	}
	
	this->stream->codec->codec_id = format_context->oformat->audio_codec;
	this->stream->codec->codec_type = CODEC_TYPE_AUDIO;
	this->stream->codec->bit_rate = MAX_AUDIO_PACKET_SIZE;
	this->stream->codec->sample_rate = this->samplerate;
	this->stream->codec->channels = 1;
	this->stream->codec->sample_fmt = SAMPLE_FMT_S16;

	// Some formats want stream headers to be separate.
	if (format_context->oformat->flags & AVFMT_GLOBALHEADER)
		this->stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;

	// Find the audio encoder.
	AVCodec* codec = avcodec_find_encoder(this->stream->codec->codec_id);
	if (codec == NULL)
	{
		std::cout << "Audio encoder: cannot find the encoder." << std::endl;
		throw internal_exception();
	}

	// Open the audio encoder.
	if (avcodec_open(this->stream->codec, codec) < 0)
	{
		std::cout << "Audio encoder: cannot open the encoder." << std::endl;
		throw internal_exception();
	}
}

void audio_encoder::disconnect()
{
	if (this->stream)
		avcodec_close(this->stream->codec);
}

void audio_encoder::send(const char* data, int size)
{
	if (data && size > 0)
	{
		memcpy(this->buffer + this->buffer_position, data, size);
		this->buffer_position += size;

		// The audio packet size (16 bits per sample).
		int packet_size = 2 * this->stream->codec->frame_size;

		char* position = this->buffer;
		int bytes_available = this->buffer_position;
		while (bytes_available >= packet_size)
		{
			AVPacket* packet = new AVPacket();
			av_init_packet(packet);

			packet->size = avcodec_encode_audio(this->stream->codec, this->encode_buffer, ENCODE_BUFFER_SIZE, (const short*)position);

			if (this->stream->codec->coded_frame && this->stream->codec->coded_frame->pts != AV_NOPTS_VALUE)
				packet->pts = av_rescale_q(this->stream->codec->coded_frame->pts, this->stream->codec->time_base, this->stream->time_base);

			packet->flags |= PKT_FLAG_KEY;
			packet->stream_index = this->stream->index;
			packet->data = this->encode_buffer;
			this->multiplexer_block->send(packet);
			av_free_packet(packet);

			position += packet_size;
			bytes_available -= packet_size;
		}

		memcpy(this->buffer, this->buffer + this->buffer_position - bytes_available, bytes_available);
		this->buffer_position = bytes_available;
	}
}
