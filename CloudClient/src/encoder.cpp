#include "encoder.h"

encoder::encoder() 
{
	this->has_audio = false;
	this->has_video = false;

	this->pFormatContext = NULL;
	this->pVideoStream = NULL;
	this->pAudioStream = NULL;
	this->pImgConvertCtx = NULL;
	this->pVideoEncodeBuffer = NULL;
	this->nSizeVideoEncodeBuffer = 0;
	this->pCurrentPicture = NULL;
}

encoder::~encoder()
{
	stop();

	delete audio_encoder_block;
	delete multiplexer_block;
	delete transmitter_block;
}

void encoder::init(int audio_samplerate, int video_bitrate, int video_framerate, int video_width, int video_height)
{
	this->audio_samplerate = audio_samplerate;
	this->video_bitrate = video_bitrate;
	this->video_framerate = video_framerate;
	this->video_width = video_width;
	this->video_height = video_height;
}

void encoder::start(std::string& container)
{
	if (!has_audio && !has_video)
		throw std::runtime_error("No audio and no video.");

	multiplexer_block = new multiplexer(container);
	pFormatContext = multiplexer_block->get_format_context();

	if (has_audio)
	{
		audio_encoder_block = new audio_encoder(this->audio_samplerate);
		audio_encoder_block->connect(multiplexer_block);
	}
	
	if (has_video)
		open_video_stream();
	
	if (av_set_parameters(pFormatContext, NULL) < 0)
		throw std::runtime_error("av_set_parameters failed.");

	multiplexer_block->connect(transmitter_block);
}

void encoder::add_frame(AVFrame* frame)
{
	int nOutputSize = 0;
	AVCodecContext *pVideoCodec = NULL;

	if (pVideoStream && frame && frame->data[0])
	{
		pVideoCodec = pVideoStream->codec;

		bool need_convert = (pVideoStream->codec->pix_fmt != PIX_FMT_RGB24);
		if (need_convert) 
		{
			// RGB to YUV420P.
			if (!pImgConvertCtx) 
			{
				pImgConvertCtx = sws_getContext(pVideoCodec->width, pVideoCodec->height,
					PIX_FMT_RGB24,
					pVideoCodec->width, pVideoCodec->height,
					pVideoCodec->pix_fmt,
					SWS_BICUBLIN, NULL, NULL, NULL);
			}
		}

		// Allocate picture.
		pCurrentPicture = avcodec_alloc_frame();
		if (!pCurrentPicture)
			throw std::runtime_error("Cannot allocate frame.");

		
		int size = avpicture_get_size(pVideoCodec->pix_fmt, pVideoCodec->width, pVideoCodec->height);
		uint8_t* frame_buffer = (uint8_t*)av_malloc(size);
		if (!frame_buffer)
			throw std::runtime_error("Cannot allocate frame buffer.");

		avpicture_fill((AVPicture*)pCurrentPicture, frame_buffer, pVideoCodec->pix_fmt, pVideoCodec->width, pVideoCodec->height);
		
		if (need_convert && pImgConvertCtx) 
		{
			// Convert RGB to YUV.
			sws_scale(pImgConvertCtx, frame->data, frame->linesize,	0, pVideoCodec->height, pCurrentPicture->data, pCurrentPicture->linesize);
		}

		if (pFormatContext->oformat->flags & AVFMT_RAWPICTURE) 
		{
			// Raw video case. The API will change slightly in the near
			// futur for that.
			AVPacket pkt;
			av_init_packet(&pkt);

			pkt.flags |= PKT_FLAG_KEY;
			pkt.stream_index = pVideoStream->index;
			pkt.data= (uint8_t *) pCurrentPicture;
			pkt.size= sizeof(AVPicture);
			multiplexer_block->send(&pkt);
			av_free_packet(&pkt);
		} 
		else 
		{
			// Encode
			int nOutputSize = avcodec_encode_video(pVideoCodec, pVideoEncodeBuffer, 
				nSizeVideoEncodeBuffer, pCurrentPicture);
			if (nOutputSize > 0) 
			{
				AVPacket pkt;
				av_init_packet(&pkt);

				if (pVideoCodec->coded_frame->pts != AV_NOPTS_VALUE)
				{
					pkt.pts = av_rescale_q(pVideoCodec->coded_frame->pts, 
						pVideoCodec->time_base, pVideoStream->time_base);
				}

				if(pVideoCodec->coded_frame->key_frame)
				{
					pkt.flags |= PKT_FLAG_KEY;
				}
				pkt.stream_index = pVideoStream->index;
				pkt.data         = pVideoEncodeBuffer;
				pkt.size         = nOutputSize;
				multiplexer_block->send(&pkt);
				av_free_packet(&pkt);
			}
		}

		// Free temp frame
		av_free(pCurrentPicture->data[0]);
		av_free(pCurrentPicture);
		pCurrentPicture = NULL;
	}
}

void encoder::add_frame(const char* sound_buffer, int sound_buffer_size)
{
	audio_encoder_block->send(sound_buffer, sound_buffer_size);
}

void encoder::stop()
{
	if (pFormatContext)
	{
		multiplexer_block->disconnect();

		// close audio stream.
		if (has_audio)
			audio_encoder_block->disconnect();

		// close video stream
		if (pVideoStream)
			close_video_stream();

		// Free the streams.
		for(size_t i = 0; i < pFormatContext->nb_streams; i++) 
		{
			av_freep(&pFormatContext->streams[i]->codec);
			av_freep(&pFormatContext->streams[i]);
		}

		if (!(pFormatContext->flags & AVFMT_NOFILE) && pFormatContext->pb) 
		{
			//s.close();
		}

		// Free the stream.
		av_free(pFormatContext);
		pFormatContext = NULL;
	}
}

void encoder::open_video_stream()
{
	AVCodecContext *pCodecCxt = NULL;
	AVStream *st    = NULL;

	st = av_new_stream(pFormatContext, 0);
	if (!st)
		throw std::runtime_error("Cannot initialize video stream.");

	pCodecCxt = st->codec;
	pCodecCxt->codec_id = pFormatContext->oformat->video_codec;
	pCodecCxt->codec_type = CODEC_TYPE_VIDEO;
	pCodecCxt->frame_number = 0;
	// Put sample parameters.
	pCodecCxt->bit_rate = video_bitrate;
	// Resolution must be a multiple of two.
	pCodecCxt->width  = video_width;
	pCodecCxt->height = video_height;
	/* time base: this is the fundamental unit of time (in seconds) in terms
	of which frame timestamps are represented. for fixed-fps content,
	timebase should be 1/framerate and timestamp increments should be
	identically 1. */
	pCodecCxt->time_base.den = video_framerate;
	pCodecCxt->time_base.num = 1;
	pCodecCxt->gop_size = 10; // emit one intra frame every twelve frames at most
	pCodecCxt->pix_fmt = PIX_FMT_YUV420P;
	if (pCodecCxt->codec_id == CODEC_ID_MPEG2VIDEO) 
	{
		// Just for testing, we also add B frames 
		pCodecCxt->max_b_frames = 2;
	}
	if (pCodecCxt->codec_id == CODEC_ID_MPEG1VIDEO)
	{
		/* Needed to avoid using macroblocks in which some coeffs overflow.
		This does not happen with normal video, it just happens here as
		the motion of the chroma plane does not match the luma plane. */
		pCodecCxt->mb_decision = 2;
	}

	// Some formats want stream headers to be separate.
	if(pFormatContext->oformat->flags & AVFMT_GLOBALHEADER)
	{
		pCodecCxt->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}

	pVideoStream = st;


	AVCodec *pCodec;
	AVCodecContext *pContext;

	pContext = pVideoStream->codec;

	// Find the video encoder.
	pCodec = avcodec_find_encoder(pContext->codec_id);
	if (!pCodec)
		throw std::runtime_error("Cannot find video encoder.");

	// Open the codec.
	if (avcodec_open(pContext, pCodec) < 0)
		throw std::runtime_error("Cannot open video encoder.");

	pVideoEncodeBuffer = NULL;      
	if (!(pFormatContext->oformat->flags & AVFMT_RAWPICTURE)) 
	{
		/* allocate output buffer */
		nSizeVideoEncodeBuffer = 10000000;
		pVideoEncodeBuffer = (uint8_t *)av_malloc(nSizeVideoEncodeBuffer);
	}
}

void encoder::close_video_stream()
{
	avcodec_close(pVideoStream->codec);
	if (pCurrentPicture)
	{
		if (pCurrentPicture->data)
		{
			av_free(pCurrentPicture->data[0]);
			pCurrentPicture->data[0] = NULL;
		}
		av_free(pCurrentPicture);
		pCurrentPicture = NULL;
	}

	if (pVideoEncodeBuffer)
	{
		av_free(pVideoEncodeBuffer);
		pVideoEncodeBuffer = NULL;
	}
	nSizeVideoEncodeBuffer = 0;
}
