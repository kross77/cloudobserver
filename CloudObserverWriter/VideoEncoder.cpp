/*
FFmpeg simple Encoder
*/
#include "stdafx.h"
#include "VideoEncoder.h"
#include <boost/asio.hpp>
#include <boost/regex.hpp>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "ffmpegInclude.h"
#include <math.h>

#include "Settings.h"
// Boost#include <boost/asio.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <boost/thread.hpp>
#include <boost/timer.hpp>
#include <queue>

using namespace std;
using boost::asio::ip::tcp;

boost::asio::io_service io_service;
tcp::resolver resolver(io_service);
tcp::socket s(io_service);

#define MAX_AUDIO_PACKET_SIZE (128 * 1024)


void VideoEncoder::SetConstants( int UserFps , int UserWidth, int UserHeight, int UserAudioSampleRate, int videoBitRate)
{
	vbr = videoBitRate;
	fps = UserFps;
	width = UserWidth;
	height = UserHeight;
	audioSampleRate = UserAudioSampleRate;
	vbr = videoBitRate;
}
int VideoEncoder::ReadFromServer()
{
	char reply[100];
	size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, 13));
	//std::cout << "Reply is: ";
	std::cout.write(reply, reply_length);
    std::cout << "\n";
	string str (reply);
	string key ("200");
	size_t found;

	found=str.rfind(key);
	if (found!=string::npos)
	{return 10;}
	else{s.close(); return 0;}
}

int VideoEncoder::ConnectToServer(std::string& tcpUrl)
{	try
{
	std::string addr;
	std::string port;
	tcpExtract(tcpUrl, addr, port);

	tcp::resolver::query query(tcp::v4(), addr.c_str(), port.c_str());
	tcp::resolver::iterator iterator = resolver.resolve(query);

	s.connect(*iterator);
return 10;
}
	catch (std::exception& e)
	{
		return -1;
	}
}
int VideoEncoder::ConnectUserToUrl( std::string& username)
{
	try
	{
		std::string header = "STREAM /";
		header += username;
		header += "?action=write HTTP/1.1\r\n\r\n";
		WriteToUrl((unsigned char *)header.c_str(),header.length() );
		return ReadFromServer();
	}
	catch (std::exception& e)
	{
return -1;
	}
}
int VideoEncoder::TryWriteToUrl(const unsigned char *buf, int size)
{
	try
	{
		boost::asio::write(s, boost::asio::buffer(buf, size));
	}
	catch (std::exception& e)
	{
		return -1;
	}
}
void VideoEncoder::WriteToUrl(const unsigned char *buf, int size)
{
try
{
boost::asio::write(s, boost::asio::buffer(buf, size));
}
catch (std::exception& e)
{
	printf("Internal Error happened, please restart application");
	cin.get();
}
}
int VideoEncoder::InitUrl(std::string& container, std::string& tcpUrl, std::string& username)
{
	
	if (!hasAudio && !hasVideo)
	{
		return -10;
	}
	int intConnection;
	bool res = false;
	userName = username;


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
			if (hasVideo)
			{
				pVideoStream   = AddVideoStream(pFormatContext, pOutFormat->video_codec);
			}
			if (hasAudio)
			{	
				pAudioStream   = AddAudioStream(pFormatContext, pOutFormat->audio_codec);
			}


			// Set the output parameters (must be done even if no
			// parameters).
			if (av_set_parameters(pFormatContext, NULL) >=0) 
			{
				//dump_format(pFormatContext, 0, filename, 1);

				// Open Video and Audio stream
				res = false;
				if (hasVideo)
				{	
					if (pVideoStream)
				{
					res = OpenVideo(pFormatContext, pVideoStream);
				//	printf("OpenVideo \n");
				}
				}

				if (hasAudio)
				{	
					res = OpenAudio(pFormatContext, pAudioStream);
				}


				if (res && !(pOutFormat->flags & AVFMT_NOFILE)) 
				{	
				if(url_open( &url_context, tcpUrl.c_str(), URL_WRONLY)  < 0) 
					{ 
						printf("Cannot open stream URL\n");
						intConnection = -1; 
						}
					}
				}


			}    
		}   
	
	//printf("1.7\n");
	if (!res)
	{
	//	printf("1.8\n");
		Free();
	//	printf("Cannot init stream\n");

	}
	if (res)
	{
		url_open_dyn_buf(&pFormatContext -> pb);
		av_write_header(pFormatContext);
		unsigned char *pb_buffer;
		int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));
		WriteToUrl((unsigned char *)pb_buffer, len);
	}
	if(res == true){
		return 1;
	}
	if(res == false){
		return intConnection;
	}

}

bool VideoEncoder::AddFrame(AVFrame* frame, const char* soundBuffer, int soundBufferSize)
{
	bool res = true;
	int nOutputSize = 0;
	AVCodecContext *pVideoCodec = NULL;

	// Add sound
	if (soundBuffer && soundBufferSize > 0)
	{
		res = AddAudioSample(pFormatContext, pAudioStream, soundBuffer, soundBufferSize);
	}

	if (pVideoStream && frame && frame->data[0])
	{
		pVideoCodec = pVideoStream->codec;

		if (NeedConvert()) 
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
		pCurrentPicture = CreateFFmpegPicture(pVideoCodec->pix_fmt, pVideoCodec->width, 
			pVideoCodec->height);

		if (NeedConvert() && pImgConvertCtx) 
		{
			// Convert RGB to YUV.
			sws_scale(pImgConvertCtx, frame->data, frame->linesize,
				0, pVideoCodec->height, pCurrentPicture->data, pCurrentPicture->linesize);      
		}

		res = AddVideoFrame(pFormatContext, pCurrentPicture, pVideoStream->codec);

		// Free temp frame
		av_free(pCurrentPicture->data[0]);
		av_free(pCurrentPicture);
		pCurrentPicture = NULL;
	}
	return res;
}

bool VideoEncoder::AddFrame(const char* soundBuffer, int soundBufferSize)
{
	bool res = true;
	int nOutputSize = 0;


	// Add sound
	if (soundBuffer && soundBufferSize > 0)
	{
		res = AddAudioSample(pFormatContext, pAudioStream, soundBuffer, soundBufferSize);
	}

	return res;
}

bool VideoEncoder::AddFrame(AVFrame* frame)
{
	bool res = true;
	int nOutputSize = 0;
	AVCodecContext *pVideoCodec = NULL;

	if (pVideoStream && frame && frame->data[0])
	{
		pVideoCodec = pVideoStream->codec;

		if (NeedConvert()) 
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
		pCurrentPicture = CreateFFmpegPicture(pVideoCodec->pix_fmt, pVideoCodec->width, 
			pVideoCodec->height);

		if (NeedConvert() && pImgConvertCtx) 
		{
			// Convert RGB to YUV.
			sws_scale(pImgConvertCtx, frame->data, frame->linesize,
				0, pVideoCodec->height, pCurrentPicture->data, pCurrentPicture->linesize);      
		}

		res = AddVideoFrame(pFormatContext, pCurrentPicture, pVideoStream->codec);

		// Free temp frame
		av_free(pCurrentPicture->data[0]);
		av_free(pCurrentPicture);
		pCurrentPicture = NULL;
	}
	return res;
}


bool VideoEncoder::Finish()
{
	bool res = true;

	if (pFormatContext)
	{
		url_open_dyn_buf(&pFormatContext -> pb);
		av_write_trailer(pFormatContext);
		unsigned char *pb_buffer;
		int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));
		WriteToUrl( (unsigned char *)pb_buffer, len);
		Free();
	}

	if (audioBuffer)
	{
		delete[] audioBuffer;
		audioBuffer = NULL;
	}

	return res;
}


void VideoEncoder::Free()
{
	bool res = true;

	if (pFormatContext)
	{
		// close video stream
		if (pVideoStream)
		{
			CloseVideo(pFormatContext, pVideoStream);
		}

		// close audio stream.
		if (pAudioStream)
		{
			CloseAudio(pFormatContext, pAudioStream);
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
			 url_close(url_context);
		}

		// Free the stream.
		av_free(pFormatContext);
		pFormatContext = NULL;
	}
}

AVFrame * VideoEncoder::CreateFFmpegPicture(int pix_fmt, int nWidth, int nHeight)
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

	size = avpicture_get_size(pix_fmt, nWidth, nHeight);
	picture_buf = (uint8_t *) av_malloc(size);

	if (!picture_buf) 
	{
		av_free(picture);
		printf("Cannot allocate buffer\n");
		return NULL;
	}

	avpicture_fill((AVPicture *)picture, picture_buf,
		pix_fmt, nWidth, nHeight);

	return picture;
}


bool VideoEncoder::OpenVideo(AVFormatContext *oc, AVStream *pStream)
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


void VideoEncoder::CloseVideo(AVFormatContext *pContext, AVStream *pStream)
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


bool VideoEncoder::NeedConvert()
{
	bool res = false;
	if (pVideoStream && pVideoStream->codec)
	{
		res = (pVideoStream->codec->pix_fmt != PIX_FMT_RGB24);
	}
	return res;
}


AVStream *VideoEncoder::AddVideoStream(AVFormatContext *pContext, CodecID codec_id)
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
	pCodecCxt->bit_rate = vbr;
	// Resolution must be a multiple of two.
	pCodecCxt->width  = width;
	pCodecCxt->height = height;
	/* time base: this is the fundamental unit of time (in seconds) in terms
	of which frame timestamps are represented. for fixed-fps content,
	timebase should be 1/framerate and timestamp increments should be
	identically 1. */
	pCodecCxt->time_base.den = fps;
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


AVStream * VideoEncoder::AddAudioStream(AVFormatContext *pContext, CodecID codec_id)
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
	pCodecCxt->sample_rate = audioSampleRate;
	pCodecCxt->channels    = 1;
	pCodecCxt->sample_fmt  = SAMPLE_FMT_S16;

	nSizeAudioEncodeBuffer = 4 * MAX_AUDIO_PACKET_SIZE; // ÈÇÇÀ ÝÒÎÎ ÀÓÄÈÎ Ê ÕÓßÌ ÌÎÆÅÒ ËÅÒÅÒÜ
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


bool VideoEncoder::OpenAudio(AVFormatContext *pContext, AVStream *pStream)
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


void VideoEncoder::CloseAudio(AVFormatContext *pContext, AVStream *pStream)
{
	avcodec_close(pStream->codec);
	if (pAudioEncodeBuffer)
	{
		av_free(pAudioEncodeBuffer);
		pAudioEncodeBuffer = NULL;
	}
	nSizeAudioEncodeBuffer = 0;
}


bool VideoEncoder::AddVideoFrame(AVFormatContext *pFormatContext, AVFrame * pOutputFrame, AVCodecContext *pVideoCodec)
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
		unsigned char *pb_buffer;
		int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));

		WriteToUrl((unsigned char *)pb_buffer, len);
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
			unsigned char *pb_buffer;
			int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));

			WriteToUrl((unsigned char *)pb_buffer, len);
			av_free_packet( &pkt);
		}
		else 
		{
			res = false;
		}
	}

	return res;
}


bool VideoEncoder::AddAudioSample(AVFormatContext *pFormatContext, AVStream *pStream, 
								  const char* soundBuffer, int soundBufferSize)
{
	AVCodecContext *pCodecCxt;    
	bool res = true;  

	pCodecCxt       = pStream->codec;
	memcpy(audioBuffer + nAudioBufferSizeCurrent, soundBuffer, soundBufferSize);
	nAudioBufferSizeCurrent += soundBufferSize;

	BYTE * pSoundBuffer = (BYTE *)audioBuffer;
	int nCurrentSize    = nAudioBufferSizeCurrent;

	// Size of packet on bytes.
	// FORMAT s16
	DWORD packSizeInSize = 2 * audioInputSampleSize;

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
		unsigned char *pb_buffer;
		int len = url_close_dyn_buf(pFormatContext -> pb, (unsigned char **)(&pb_buffer));

		WriteToUrl((unsigned char *)pb_buffer, len);
		av_free_packet( &pkt);

		nCurrentSize -= packSizeInSize;  
		pSoundBuffer += packSizeInSize;  
	}

	// save excess
	memcpy(audioBuffer, audioBuffer + nAudioBufferSizeCurrent - nCurrentSize, nCurrentSize);
	nAudioBufferSizeCurrent = nCurrentSize; 

	return res;
}

void VideoEncoder::tcpExtract(std::string const& ip, std::string& address, std::string& service)
{
	boost::regex e("tcp://(.+):(\\d+)/");
	boost::smatch what;
	if(boost::regex_match(ip, what, e, boost::match_extra))
	{
		boost::smatch::iterator it = what.begin();
		++it; // skip the first entry..
		address = *it;
		++it;
		service = *it;
	}
}
