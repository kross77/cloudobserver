#include "encoder.h"

boost::asio::io_service io_service;
boost::asio::ip::tcp::resolver resolver(io_service);
boost::asio::ip::tcp::socket s(io_service);

encoder::encoder() 
{
	this->has_audio = false;
	this->has_video = false;

	this->pOutFormat = NULL;
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
}

void encoder::init(int audio_samplerate, int video_bitrate, int video_framerate, int video_width, int video_height)
{
	this->audio_samplerate = audio_samplerate;
	this->video_bitrate = video_bitrate;
	this->video_framerate = video_framerate;
	this->video_width = video_width;
	this->video_height = video_height;
}

bool encoder::connect(std::string url)
{
	// Parse the URL.
	std::vector<std::string> url_parts;
	boost::regex url_expression(
		// protocol            host               port
		"^(\?:([^:/\?#]+)://)\?(\\w+[^/\?#:]*)(\?::(\\d+))\?"
		// path                file       parameters
		"(/\?(\?:[^\?#/]*/)*)\?([^\?#]*)\?(\\\?(.*))\?"
		);
	boost::regex_split(std::back_inserter(url_parts), url, url_expression);
	std::string protocol = url_parts[0];
	std::string host = url_parts[1];
	std::string port = url_parts[2];

	// Use the default protocol if no protocol is specified.
	if (protocol.empty())
		protocol = DEFAULT_PROTOCOL;

	// Use the default port if no port is specified.
	if (port.empty())
		port = DEFAULT_PORT;

	// Get the list of all supported protocols.
	std::vector<std::string> protocols;
	boost::split(protocols, SUPPORTED_PROTOCOLS, boost::is_any_of(", "));

	// Check if the given protocol is supported.
	boost::to_upper(protocol);
	if (std::find(protocols.begin(), protocols.end(), protocol) == protocols.end())
	{
		// The protocol is not supported. Report a failure.
		std::cout << protocol <<
			" protocol is not valid. Use one of the following protocols: "
			<< SUPPORTED_PROTOCOLS << "." << std::endl;
		return false;
	}

	// Resolve the hostname.
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), host, port);
	boost::asio::ip::tcp::resolver::iterator iterator;
	try
	{
		iterator = resolver.resolve(query);
	}
	catch (std::exception)
	{
		// Failed to resolve the hostname. Report a failure.
		std::cout << "Cannot resolve the hostname." << std::endl;
		return false;
	}
	
	// Try to connect to the server using one of the endpoints.
	for (iterator; iterator != boost::asio::ip::tcp::resolver::iterator(); ++iterator)
	{
		boost::asio::ip::tcp::endpoint endpoint = *iterator;
		std::cout << "Trying to connect to the server at " << endpoint.address().to_string() << ":" << port << "...";
		try
		{
			s.connect(endpoint);

			// Connection succeeded. Report a success.
			std::cout << " OK." << std::endl;
			return true;
		}
		catch (std::exception)
		{
			// Failed to connect to the endpoint. Try the next one if any.
			std::cout << " failed." << std::endl;
		}
	}

	// Unable to connect to all the endpoints. Report a failure.
	return false;
}

int encoder::set_username(std::string& username)
{
	std::string http_header = "GET /" + username + "?action=write HTTP/1.1\r\n\r\n";
	send_data(http_header.c_str(), http_header.length());

	http_response_parser parser;
	http_response response = parser.parse(s);

	if (response.status == 200)
		return 10;

	s.close();
	return 0;
}

int encoder::start(std::string& container)
{
	if (!has_audio && !has_video)
	{
		return -10;
	}
	int intConnection;
	bool res = false;


	// Initialize libavcodec
	av_register_all();


	// use contanier
	pOutFormat = guess_format(container.c_str(), NULL, NULL);


	if (pOutFormat) 
	{
		// allocate context
		pFormatContext = avformat_alloc_context();
		if (pFormatContext) 
		{    
			pFormatContext->oformat = pOutFormat;
			//memcpy(pFormatContext->filename, inputUrlContext->filename, min(strlen(inputUrlContext->filename), 
			//	sizeof(pFormatContext->filename))); 

			// Add video and audio stream
			if (has_video)
			{
				pVideoStream   = add_video_stream(pFormatContext, pOutFormat->video_codec);
			}
			if (has_audio)
			{	
				pAudioStream   = add_audio_stream(pFormatContext, pOutFormat->audio_codec);
			}


			// Set the output parameters (must be done even if no
			// parameters).
			if (av_set_parameters(pFormatContext, NULL) >=0) 
			{
				//dump_format(pFormatContext, 0, filename, 1);

				// Open Video and Audio stream
				res = false;
				if (has_video)
				{	
					if (pVideoStream)
					{
						res = open_video_stream(pFormatContext, pVideoStream);
					}
				}

				if (has_audio)
				{	
					res = open_audio_stream(pFormatContext, pAudioStream);
				}
			}


		}    
	}   

	//printf("1.7\n");
	if (!res)
	{
		//	printf("1.8\n");
		free();
		//	printf("Cannot init stream\n");

	}
	if (res)
	{
		url_open_dyn_buf(&pFormatContext -> pb);
		av_write_header(pFormatContext);
		char* pb_buffer;
		int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));
		send_data(pb_buffer, len);
	}
	if(res == true){
		return 1;
	}
	if(res == false){
		return intConnection;
	}
}

bool encoder::add_frame(AVFrame* frame, const char* sound_buffer, int sound_buffer_size)
{
	bool res = true;
	int nOutputSize = 0;
	AVCodecContext *pVideoCodec = NULL;

	// Add sound
	if (sound_buffer && sound_buffer_size > 0)
	{
		res = add_audio_frame(pFormatContext, pAudioStream, sound_buffer, sound_buffer_size);
	}

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
		pCurrentPicture = create_avframe(pVideoCodec->pix_fmt, pVideoCodec->width, 
			pVideoCodec->height);

		if (need_convert() && pImgConvertCtx) 
		{
			// Convert RGB to YUV.
			sws_scale(pImgConvertCtx, frame->data, frame->linesize,
				0, pVideoCodec->height, pCurrentPicture->data, pCurrentPicture->linesize);      
		}

		res = add_video_frame(pFormatContext, pCurrentPicture, pVideoStream->codec);

		// Free temp frame
		av_free(pCurrentPicture->data[0]);
		av_free(pCurrentPicture);
		pCurrentPicture = NULL;
	}
	return res;
}

bool encoder::add_frame(AVFrame* frame)
{
	bool res = true;
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
		pCurrentPicture = create_avframe(pVideoCodec->pix_fmt, pVideoCodec->width, 
			pVideoCodec->height);

		if (need_convert() && pImgConvertCtx) 
		{
			// Convert RGB to YUV.
			sws_scale(pImgConvertCtx, frame->data, frame->linesize,	0, pVideoCodec->height, pCurrentPicture->data, pCurrentPicture->linesize);
		}

		res = add_video_frame(pFormatContext, pCurrentPicture, pVideoStream->codec);

		// Free temp frame
		av_free(pCurrentPicture->data[0]);
		av_free(pCurrentPicture);
		pCurrentPicture = NULL;
	}
	return res;
}

bool encoder::add_frame(const char* sound_buffer, int sound_buffer_size)
{
	bool res = true;
	int nOutputSize = 0;


	// Add sound
	if (sound_buffer && sound_buffer_size > 0)
	{
		res = add_audio_frame(pFormatContext, pAudioStream, sound_buffer, sound_buffer_size);
	}

	return res;
}

bool encoder::stop()
{
	bool res = true;

	if (pFormatContext)
	{
		url_open_dyn_buf(&pFormatContext -> pb);
		av_write_trailer(pFormatContext);
		char* pb_buffer;
		int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));
		send_data(pb_buffer, len);
		free();
	}

	if (audioBuffer)
	{
		delete[] audioBuffer;
		audioBuffer = NULL;
	}

	return res;
}

AVStream* encoder::add_audio_stream(AVFormatContext* pContext, CodecID codec_id)
{
	AVCodecContext *pCodecCxt = NULL;
	AVStream *pStream = NULL;

	// Try create stream.
	pStream = av_new_stream(pContext, 1);
	if (!pStream) 
	{
		printf("Cannot add new audio stream\n");
		return NULL;
	}
	//	printf("added new audio stream\n");
	// Codec.
	pCodecCxt = pStream->codec;
	pCodecCxt->codec_id = codec_id;
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
	if(pContext->oformat->flags & AVFMT_GLOBALHEADER)
	{
		pCodecCxt->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}

	return pStream;
}

AVStream* encoder::add_video_stream(AVFormatContext* pContext, CodecID codec_id)
{
	AVCodecContext *pCodecCxt = NULL;
	AVStream *st    = NULL;

	st = av_new_stream(pContext, 0);
	if (!st) 
	{
		printf("Cannot add new vidoe stream\n");
		return NULL;
	}

	pCodecCxt = st->codec;
	pCodecCxt->codec_id = (CodecID)codec_id;
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
	if(pContext->oformat->flags & AVFMT_GLOBALHEADER)
	{
		pCodecCxt->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}

	return st;
}

bool encoder::open_audio_stream(AVFormatContext* pContext, AVStream* pStream)
{
	AVCodecContext *pCodecCxt = NULL;
	AVCodec *pCodec = NULL;
	pCodecCxt = pStream->codec;

	// Find the audio encoder.
	pCodec = avcodec_find_encoder(pCodecCxt->codec_id);
	if (!pCodec) 
	{
		printf("Cannot open audio codec\n");
		return false;
	}

	// Open it.
	if (avcodec_open(pCodecCxt, pCodec) < 0) 
	{
		printf("Cannot open audio codec\n");
		return false;
	}

	if (pCodecCxt->frame_size <= 1) 
	{
		// Ugly hack for PCM codecs (will be removed ASAP with new PCM
		// support to compute the input frame size in samples. 
		audioInputSampleSize = nSizeAudioEncodeBuffer / pCodecCxt->channels;
		switch (pStream->codec->codec_id) 
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

	return true;
}

bool encoder::open_video_stream(AVFormatContext* oc, AVStream* pStream)
{
	AVCodec *pCodec;
	AVCodecContext *pContext;

	pContext = pStream->codec;

	// Find the video encoder.
	pCodec = avcodec_find_encoder(pContext->codec_id);
	if (!pCodec) 
	{
		printf("Cannot found video codec\n");
		return false;
	}

	// Open the codec.
	if (avcodec_open(pContext, pCodec) < 0) 
	{
		printf("Cannot open video codec\n");
		return false;
	}

	pVideoEncodeBuffer = NULL;      
	if (!(pFormatContext->oformat->flags & AVFMT_RAWPICTURE)) 
	{
		/* allocate output buffer */
		nSizeVideoEncodeBuffer = 10000000;
		pVideoEncodeBuffer = (uint8_t *)av_malloc(nSizeVideoEncodeBuffer);
	}

	return true;
}

void encoder::close_audio_stream(AVFormatContext* pContext, AVStream* pStream)
{
	avcodec_close(pStream->codec);
	if (pAudioEncodeBuffer)
	{
		av_free(pAudioEncodeBuffer);
		pAudioEncodeBuffer = NULL;
	}
	nSizeAudioEncodeBuffer = 0;
}

void encoder::close_video_stream(AVFormatContext* pContext, AVStream* pStream)
{
	avcodec_close(pStream->codec);
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

bool encoder::add_audio_frame(AVFormatContext* pFormatContext, AVStream* pStream, const char* soundBuffer, int soundBufferSize)
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

		send_data(pb_buffer, len);
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

bool encoder::add_video_frame(AVFormatContext* pFormatContext, AVFrame* pOutputFrame, AVCodecContext* pVideoCodec)
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

		send_data(pb_buffer, len);
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

			send_data(pb_buffer, len);
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

AVFrame* encoder::create_avframe(int pix_fmt, int nWidth, int nHeight)
{
	AVFrame *picture     = NULL;
	uint8_t *picture_buf = NULL;
	int size;

	picture = avcodec_alloc_frame();
	if ( !picture)
	{
		printf("Cannot create frame\n");
		return NULL;
	}

	size = avpicture_get_size((PixelFormat)pix_fmt, nWidth, nHeight);
	picture_buf = (uint8_t *) av_malloc(size);

	if (!picture_buf) 
	{
		av_free(picture);
		printf("Cannot allocate buffer\n");
		return NULL;
	}

	avpicture_fill((AVPicture *)picture, picture_buf, (PixelFormat)pix_fmt, nWidth, nHeight);

	return picture;
}

void encoder::free()
{
	bool res = true;

	if (pFormatContext)
	{
		// close video stream
		if (pVideoStream)
		{
			close_video_stream(pFormatContext, pVideoStream);
		}

		// close audio stream.
		if (pAudioStream)
		{
			close_audio_stream(pFormatContext, pAudioStream);
		}

		// Free the streams.
		for(size_t i = 0; i < pFormatContext->nb_streams; i++) 
		{
			av_freep(&pFormatContext->streams[i]->codec);
			av_freep(&pFormatContext->streams[i]);
		}

		if (!(pFormatContext->flags & AVFMT_NOFILE) && pFormatContext->pb) 
		{
			s.close();
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

void encoder::send_data(const char* data, int size)
{
	try
	{
		boost::asio::write(s, boost::asio::buffer(data, size));
	}
	catch (std::exception& e)
	{
		printf("Internal Error happened, please restart application");
		std::cin.get();
	}
}
