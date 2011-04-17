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
	this->pAudioEncodeBuffer = NULL;
	this->nSizeAudioEncodeBuffer = 0;
	this->pCurrentPicture = NULL;
	this->nAudioBufferSizeCurrent = 0;
	this->nAudioBufferSize = 1024 * 1024 * 4;
	this->audioBuffer = new char[nAudioBufferSize];
}

encoder::~encoder()
{
	stop();

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

	av_register_all();

	AVOutputFormat* pOutFormat = av_guess_format(container.c_str(), NULL, NULL);
	if (pOutFormat == NULL)
		throw std::runtime_error("av_guess_format failed.");

	pFormatContext = avformat_alloc_context();
	if (pFormatContext == NULL)
		throw std::runtime_error("avformat_alloc_context failed.");

	pFormatContext->oformat = pOutFormat;

	if (has_audio)
	{
		init_audio_stream();
		open_audio_stream();
	}

	if (has_video)
	{
		init_video_stream();
		open_video_stream();
	}

	if (av_set_parameters(pFormatContext, NULL) < 0)
		throw std::runtime_error("av_set_parameters failed.");
	
	if (url_open_dyn_buf(&pFormatContext->pb) != 0)
		throw std::runtime_error("url_open_dyn_buf failed.");

	if (av_write_header(pFormatContext) != 0)
		throw std::runtime_error("av_write_header failed.");

	char* pb_buffer;
	int len = url_close_dyn_buf(pFormatContext->pb, (uint8_t**)(&pb_buffer));
	transmitter_block->send(pb_buffer, len);
	av_free(pb_buffer);
}

void encoder::add_frame(AVFrame* frame, const char* sound_buffer, int sound_buffer_size)
{
	add_frame(sound_buffer, sound_buffer_size);
	add_frame(frame);
}

void encoder::add_frame(AVFrame* frame)
{
	int nOutputSize = 0;
	AVCodecContext *pVideoCodec = NULL;

	if (pVideoStream && frame && frame->data[0])
	{
		pVideoCodec = pVideoStream->codec;

		if (need_convert()) 
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
		
		if (need_convert() && pImgConvertCtx) 
		{
			// Convert RGB to YUV.
			sws_scale(pImgConvertCtx, frame->data, frame->linesize,	0, pVideoCodec->height, pCurrentPicture->data, pCurrentPicture->linesize);
		}

		if(!add_video_frame(pCurrentPicture, pVideoStream->codec))
			throw std::runtime_error("add_video_frame failed.");

		// Free temp frame
		av_free(pCurrentPicture->data[0]);
		av_free(pCurrentPicture);
		pCurrentPicture = NULL;
	}
}

void encoder::add_frame(const char* sound_buffer, int sound_buffer_size)
{
	if (sound_buffer && sound_buffer_size > 0)
		if (!add_audio_frame(pAudioStream, sound_buffer, sound_buffer_size))
			throw std::runtime_error("add_audio_frame failed.");
}

void encoder::stop()
{
	if (pFormatContext)
	{
		if (url_open_dyn_buf(&pFormatContext->pb) != 0)
			throw std::runtime_error("url_open_dyn_buf failed.");
		if (av_write_trailer(pFormatContext) != 0)
			throw std::runtime_error("av_write_trailer failed.");
		char* pb_buffer;
		int len = url_close_dyn_buf(pFormatContext->pb, (uint8_t**)(&pb_buffer));
		transmitter_block->send(pb_buffer, len);
		av_free(pb_buffer);
		free();
	}

	if (audioBuffer)
	{
		delete[] audioBuffer;
		audioBuffer = NULL;
	}
}

void encoder::init_audio_stream()
{
	AVCodecContext *pCodecCxt = NULL;
	AVStream *pStream = NULL;

	// Try create stream.
	pStream = av_new_stream(pFormatContext, 1);
	if (!pStream)
		throw std::runtime_error("Cannot initialize audio stream.");

	// Codec.
	pCodecCxt = pStream->codec;
	pCodecCxt->codec_id = pFormatContext->oformat->audio_codec;
	pCodecCxt->codec_type = CODEC_TYPE_AUDIO;
	// Set format
	pCodecCxt->bit_rate    = MAX_AUDIO_PACKET_SIZE - 1024*10;
	pCodecCxt->sample_rate = audio_samplerate;
	pCodecCxt->channels    = 1;
	pCodecCxt->sample_fmt  = SAMPLE_FMT_S16;

	nSizeAudioEncodeBuffer = 4 * MAX_AUDIO_PACKET_SIZE;
	if (pAudioEncodeBuffer == NULL)
	{      
		pAudioEncodeBuffer = (uint8_t * )av_malloc(nSizeAudioEncodeBuffer);
	}

	// Some formats want stream headers to be separate.
	if(pFormatContext->oformat->flags & AVFMT_GLOBALHEADER)
	{
		pCodecCxt->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}

	pAudioStream = pStream;
}

void encoder::init_video_stream()
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
}

void encoder::open_audio_stream()
{
	AVCodecContext *pCodecCxt = NULL;
	AVCodec *pCodec = NULL;
	pCodecCxt = pAudioStream->codec;

	// Find the audio encoder.
	pCodec = avcodec_find_encoder(pCodecCxt->codec_id);
	if (!pCodec)
		throw std::runtime_error("Cannot find audio encoder.");

	// Open it.
	if (avcodec_open(pCodecCxt, pCodec) < 0)
		throw std::runtime_error("Cannot open audio encoder.");

	if (pCodecCxt->frame_size <= 1) 
	{
		// Ugly hack for PCM codecs (will be removed ASAP with new PCM
		// support to compute the input frame size in samples. 
		audioInputSampleSize = nSizeAudioEncodeBuffer / pCodecCxt->channels;
		switch (pAudioStream->codec->codec_id) 
		{
		case CODEC_ID_PCM_S16LE:
		case CODEC_ID_PCM_S16BE:
		case CODEC_ID_PCM_U16LE:
		case CODEC_ID_PCM_U16BE:
			audioInputSampleSize >>= 1;
			break;
		default:
			break;
		}
		pCodecCxt->frame_size = audioInputSampleSize;
	} 
	else 
	{
		audioInputSampleSize = pCodecCxt->frame_size;
	}
}

void encoder::open_video_stream()
{
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

void encoder::close_audio_stream()
{
	avcodec_close(pAudioStream->codec);
	if (pAudioEncodeBuffer)
	{
		av_free(pAudioEncodeBuffer);
		pAudioEncodeBuffer = NULL;
	}
	nSizeAudioEncodeBuffer = 0;
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

bool encoder::add_audio_frame(AVStream* pStream, const char* soundBuffer, int soundBufferSize)
{
	AVCodecContext *pCodecCxt;    
	bool res = true;  

	pCodecCxt       = pStream->codec;
	memcpy(audioBuffer + nAudioBufferSizeCurrent, soundBuffer, soundBufferSize);
	nAudioBufferSizeCurrent += soundBufferSize;

	char * pSoundBuffer = (char *)audioBuffer;
	int nCurrentSize    = nAudioBufferSizeCurrent;

	// Size of packet on bytes.
	// FORMAT s16
	int  packSizeInSize = 2 * audioInputSampleSize;

	while(nCurrentSize >= packSizeInSize)
	{
		AVPacket pkt;
		av_init_packet(&pkt);

		pkt.size = avcodec_encode_audio(pCodecCxt, pAudioEncodeBuffer, 
			nSizeAudioEncodeBuffer, (const short *)pSoundBuffer);

		if (pCodecCxt->coded_frame && pCodecCxt->coded_frame->pts != AV_NOPTS_VALUE)
		{
			pkt.pts = av_rescale_q(pCodecCxt->coded_frame->pts, pCodecCxt->time_base, pStream->time_base);
		}

		pkt.flags |= PKT_FLAG_KEY;
		pkt.stream_index = pStream->index;
		pkt.data = pAudioEncodeBuffer;

		// Write the compressed frame in the media file.
		url_open_dyn_buf(&pFormatContext -> pb);
		if (av_interleaved_write_frame(pFormatContext, &pkt) != 0) 
		{
			res = false;
			break;
		}
		char* pb_buffer;
		int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));

		transmitter_block->send(pb_buffer, len);
		av_free(pb_buffer) ;
		//av_freep(&pb_buffer);
		av_free_packet( &pkt);	


		nCurrentSize -= packSizeInSize;  
		pSoundBuffer += packSizeInSize;  
	}

	// save excess
	memcpy(audioBuffer, audioBuffer + nAudioBufferSizeCurrent - nCurrentSize, nCurrentSize);
	nAudioBufferSizeCurrent = nCurrentSize; 

	return res;
}

bool encoder::add_video_frame(AVFrame* pOutputFrame, AVCodecContext* pVideoCodec)
{
	bool res = false;

	if (pFormatContext->oformat->flags & AVFMT_RAWPICTURE) 
	{
		// Raw video case. The API will change slightly in the near
		// futur for that.
		AVPacket pkt;
		av_init_packet(&pkt);

		pkt.flags |= PKT_FLAG_KEY;
		pkt.stream_index = pVideoStream->index;
		pkt.data= (uint8_t *) pOutputFrame;
		pkt.size= sizeof(AVPicture);

		url_open_dyn_buf(&pFormatContext -> pb);
		res = av_interleaved_write_frame(pFormatContext, &pkt);
		char* pb_buffer;
		int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));

		transmitter_block->send(pb_buffer, len);
		av_free(pb_buffer) ;
		//av_freep(&pb_buffer);
		av_free_packet( &pkt);
		res = true;
	} 
	else 
	{
		// Encode
		int nOutputSize = avcodec_encode_video(pVideoCodec, pVideoEncodeBuffer, 
			nSizeVideoEncodeBuffer, pOutputFrame);
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

			// Write frame
			url_open_dyn_buf(&pFormatContext -> pb);
			res = (av_interleaved_write_frame(pFormatContext, &pkt) == 0);
			char* pb_buffer;
			int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));

			transmitter_block->send(pb_buffer, len);
			av_free(pb_buffer) ;
			//av_freep(&pb_buffer);
			av_free_packet( &pkt);
		}
		else 
		{
			res = false;
		}
	}

	return res;
}

void encoder::free()
{
	bool res = true;

	if (pFormatContext)
	{
		// close audio stream.
		if (pAudioStream)
			close_audio_stream();

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

bool encoder::need_convert()
{
	bool res = false;
	if (pVideoStream && pVideoStream->codec)
	{
		res = (pVideoStream->codec->pix_fmt != PIX_FMT_RGB24);
	}
	return res;
}
