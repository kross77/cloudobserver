#include "video_encoder.h"

using namespace ffmpeg;

video_encoder::video_encoder(int bitrate, int framerate, int width, int height)
{
	this->bitrate = bitrate;
	this->framerate = framerate;
	this->width = width;
	this->height = height;

	this->raw_data = false;
	this->need_convert = false;
	
	this->encode_buffer = (uint8_t*)av_malloc(ENCODE_BUFFER_SIZE);
	this->convert_context = NULL;

	this->multiplexer_block = NULL;
}

video_encoder::~video_encoder()
{
	this->disconnect();

	av_free(this->encode_buffer);
}

void video_encoder::connect(multiplexer* multiplexer_block)
{
	this->multiplexer_block = multiplexer_block;
	AVFormatContext* format_context = this->multiplexer_block->get_format_context();

	this->stream = av_new_stream(format_context, 0);
	if (this->stream == NULL)
	{
		std::cout << "Video encoder: cannot initialize video stream." << std::endl;
		throw internal_exception();
	}

	this->stream->codec->codec_id = format_context->oformat->video_codec;
	this->stream->codec->codec_type = CODEC_TYPE_VIDEO;
	this->stream->codec->frame_number = 0;
	this->stream->codec->bit_rate = this->bitrate;
	this->stream->codec->width = this->width;
	this->stream->codec->height = this->height;
	this->stream->codec->time_base.den = this->framerate;
	this->stream->codec->time_base.num = 1;
	this->stream->codec->gop_size = 10;
	this->stream->codec->pix_fmt = PIX_FMT_YUV420P;

	if (this->stream->codec->codec_id == CODEC_ID_MPEG2VIDEO)
		this->stream->codec->max_b_frames = 2;
	
	// Needed to avoid using macroblocks in which some coeffs overflow.
	// This does not happen with normal video, it just happens here as
	// the motion of the chroma plane does not match the luma plane.
	if (this->stream->codec->codec_id == CODEC_ID_MPEG1VIDEO)
		this->stream->codec->mb_decision = 2;

	// Some formats want stream headers to be separate.
	if (format_context->oformat->flags & AVFMT_GLOBALHEADER)
		this->stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;

	// Find the video encoder.
	AVCodec* codec = avcodec_find_encoder(this->stream->codec->codec_id);
	if (codec == NULL)
	{
		std::cout << "Video encoder: cannot find the encoder." << std::endl;
		throw internal_exception();
	}

	// Open the video encoder.
	if (avcodec_open(this->stream->codec, codec) < 0)
	{
		std::cout << "Video encoder: cannot open the encoder." << std::endl;
		throw internal_exception();
	}

	this->raw_data = format_context->oformat->flags & AVFMT_RAWPICTURE;
	this->need_convert = (this->stream->codec->pix_fmt != PIX_FMT_RGB24);
	if (this->need_convert)
		this->convert_context = sws_getContext(this->stream->codec->width, this->stream->codec->height, PIX_FMT_RGB24,
			this->stream->codec->width, this->stream->codec->height, this->stream->codec->pix_fmt, SWS_BICUBLIN, NULL, NULL, NULL);
}

void video_encoder::disconnect()
{
	if (this->stream)
		avcodec_close(this->stream->codec);
}

void video_encoder::send(AVFrame* frame)
{
	if (frame && frame->data[0])
	{
		AVFrame* picture = avcodec_alloc_frame();
		if (!picture)
		{
			std::cout << "Video encoder: cannot allocate frame." << std::endl;
			throw internal_exception();
		}

		int size = avpicture_get_size(this->stream->codec->pix_fmt, this->stream->codec->width, this->stream->codec->height);
		uint8_t* frame_buffer = (uint8_t*)av_malloc(size);
		if (!frame_buffer)
		{
			std::cout << "Video encoder: cannot allocate frame buffer." << std::endl;
			throw internal_exception();
		}

		avpicture_fill((AVPicture*)picture, frame_buffer, this->stream->codec->pix_fmt, this->stream->codec->width, this->stream->codec->height);

		if (this->need_convert)
			sws_scale(this->convert_context, frame->data, frame->linesize, 0, this->stream->codec->height, picture->data, picture->linesize);

		if (this->raw_data)
		{
			AVPacket* packet = new AVPacket();
			av_init_packet(packet);
			packet->flags |= PKT_FLAG_KEY;
			packet->stream_index = this->stream->index;
			packet->data = (uint8_t*)picture;
			packet->size = sizeof(AVPicture);
			this->multiplexer_block->send(packet);
			av_free_packet(packet);
		}
		else
		{
			int output_size = avcodec_encode_video(this->stream->codec, this->encode_buffer, ENCODE_BUFFER_SIZE, picture);
			if (output_size > 0)
			{
				AVPacket* packet = new AVPacket();
				av_init_packet(packet);

				if (this->stream->codec->coded_frame->pts != AV_NOPTS_VALUE)
					packet->pts = av_rescale_q(this->stream->codec->coded_frame->pts, this->stream->codec->time_base, this->stream->time_base);

				if (this->stream->codec->coded_frame->key_frame)
					packet->flags |= PKT_FLAG_KEY;

				packet->stream_index = this->stream->index;
				packet->data = this->encode_buffer;
				packet->size = output_size;
				this->multiplexer_block->send(packet);
				av_free_packet(packet);
			}
		}

		av_free(picture->data[0]);
		av_free(picture);
	}
}
