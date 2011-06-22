#include "multiplexer.h"

multiplexer::multiplexer(std::string container)
{
	av_register_all();

	this->format_context = avformat_alloc_context();
	if (this->format_context == NULL)
	{
		std::cout << "Multiplexer: format context is empty." << std::endl;
		throw internal_exception();
	}
	
	this->format_context->oformat = av_guess_format(container.c_str(), NULL, NULL);
	if (this->format_context->oformat == NULL)
	{
		std::cout << "Multiplexer: invalid container format (" << container << ")." << std::endl;
		throw internal_exception();
	}
}

multiplexer::~multiplexer()
{
}

void multiplexer::connect(transmitter* transmitter_block)
{
	this->transmitter_block = transmitter_block;

	// Write a header.
	url_open_dyn_buf(&this->format_context->pb);
	if (av_write_header(this->format_context) != 0)
	{
		std::cout << "Multiplexer: failed to write a haeder." << std::endl;
		throw internal_exception();
	}
	char* buffer;
	int length = url_close_dyn_buf(this->format_context->pb, (uint8_t**)(&buffer));
	this->transmitter_block->send(buffer, length);
	av_free(buffer);
}

void multiplexer::disconnect()
{
	if (this->format_context)
	{
		// Write a trailer.
		url_open_dyn_buf(&this->format_context->pb);
		if (av_write_trailer(this->format_context) != 0)
		{
			std::cout << "Multiplexer: failed to write a trailer." << std::endl;
			throw internal_exception();
		}
		char* buffer;
		int length = url_close_dyn_buf(this->format_context->pb, (uint8_t**)(&buffer));
		this->transmitter_block->send(buffer, length);
		av_free(buffer);

		for (size_t i = 0; i < this->format_context->nb_streams; i++)
		{
			av_free(this->format_context->streams[i]->codec);
			av_free(this->format_context->streams[i]);
		}

		av_free(this->format_context);
		this->format_context = NULL;
	}
}

AVFormatContext* multiplexer::get_format_context()
{
	return this->format_context;
}

void multiplexer::send(AVPacket* packet)
{
	boost::mutex::scoped_lock lock(this->send_mutex);

	url_open_dyn_buf(&this->format_context->pb);
	if (av_interleaved_write_frame(this->format_context, packet) != 0)
	{
		std::cout << "Multiplexer: failed to send a packet." << std::endl;
		throw internal_exception();
	}
	char* buffer;
	int length = url_close_dyn_buf(this->format_context->pb, (uint8_t**)(&buffer));
	this->transmitter_block->send(buffer, length);
	av_free(buffer);
}
