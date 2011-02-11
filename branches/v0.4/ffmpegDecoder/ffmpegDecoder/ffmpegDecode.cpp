/*
  FFmpeg decoder
*/

#include "ffmpegDecode.h"

#define MAX_AUDIO_PACKET (2 * 1024 * 1024)

bool FFmpegDecoder::OpenFile (std::string& inputFile)
{
  CloseFile();

  // Register all components
  av_register_all();
	
  // Open media file.
  if (av_open_input_file(&pFormatCtx, inputFile.c_str(), NULL, 0, NULL) != 0)
  {
    CloseFile();
	printf("fuck you av_open_input_file");
    return false;
  }

  // Get format info.
  if (av_find_stream_info(pFormatCtx) < 0)
  {
    CloseFile();
	printf("fuck you av_find_stream_info");
    return false;
  }

  // open video and audio stream.
  bool hasVideo = OpenVideo();
  bool hasAudio = OpenAudio(); 

  if (!hasVideo)
  {
    CloseFile();
    return false;
  }

  isOpen = true;

  // Get file information.
  if (videoStreamIndex != -1)
  {
    videoFramePerSecond = av_q2d(pFormatCtx->streams[videoStreamIndex]->r_frame_rate);
    // Need for convert time to ffmpeg time.
    videoBaseTime       = av_q2d(pFormatCtx->streams[videoStreamIndex]->time_base); 
  }

  if (audioStreamIndex != -1)
  {
    audioBaseTime = av_q2d(pFormatCtx->streams[audioStreamIndex]->time_base);
  }

  return true;
}


bool FFmpegDecoder::CloseFile()
{
	isOpen = false;

  // Close video and audio.
  CloseVideo();
  CloseAudio();

	if (pFormatCtx)
	{
		av_close_input_file(pFormatCtx);
		pFormatCtx = NULL;
	}
  
  return true;
}


AVFrame * FFmpegDecoder::GetNextFrame()
{
	printf("getFrame");
  AVFrame * res = NULL;

  if (videoStreamIndex != -1)
  {
    AVFrame *pVideoYuv = avcodec_alloc_frame();
    AVPacket packet;

    if (isOpen)
    {
      // Read packet.
      while (av_read_frame(pFormatCtx, &packet) >= 0)
      {
        int64_t pts = 0;
        pts = (packet.dts != AV_NOPTS_VALUE) ? packet.dts : 0;

        if(packet.stream_index == videoStreamIndex)
        {
          // Convert ffmpeg frame timestamp to real frame number.
          int64_t numberFrame = (double)((int64_t)pts - 
            pFormatCtx->streams[videoStreamIndex]->start_time) * 
            videoBaseTime * videoFramePerSecond; 

          // Decode frame
          bool isDecodeComplite = DecodeVideo(packet.data, packet.size, pVideoYuv);
          if (isDecodeComplite)
          {
            res = GetRGBAFrame(pVideoYuv);
          }
          break;
        } 
        else if (packet.stream_index == audioStreamIndex)
        {
          if (packet.dts != AV_NOPTS_VALUE)
          {
            int audioFrameSize = MAX_AUDIO_PACKET;
            uint8_t * pFrameAudio = new uint8_t[audioFrameSize];
            if (pFrameAudio)
            {
              double fCurrentTime = (double)(pts - pFormatCtx->streams[videoStreamIndex]->start_time)
                * audioBaseTime;
              double fCurrentDuration = (double)packet.duration * audioBaseTime;

              // Decode the frame.
              int nDecodedSize = DecodeAudio(audioStreamIndex, packet.data, packet.size,
                pFrameAudio, audioFrameSize);

              // decode audio
              delete[] pFrameAudio;
              pFrameAudio = NULL;
            }
          }
        }

        av_free_packet(&packet);
      }

      av_free(pVideoYuv);
    }    
  }

  return res;
}


AVFrame * FFmpegDecoder::GetRGBAFrame(AVFrame *pFrameYuv)
{
  AVFrame * frame = NULL;
  int width  = pVideoCodecCtx->width;
  int height = pVideoCodecCtx->height;
  int bufferImgSize = avpicture_get_size(PIX_FMT_BGR24, width, height);
	frame = avcodec_alloc_frame();
	uint8_t * buffer = (uint8_t*)av_mallocz(bufferImgSize);
  if (buffer && frame)
  {
	  avpicture_fill((AVPicture*)frame, buffer, PIX_FMT_BGR24, width, height);
    sws_scale(pImgConvertCtx, pFrameYuv->data, pFrameYuv->linesize,
          0, height, frame->data, frame->linesize);      
  }  

  return frame;
}


bool FFmpegDecoder::OpenVideo()
{
  bool res = false;

  if (pFormatCtx)
  {
	  videoStreamIndex = -1;

	  for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
	  {
		  if (pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO)
		  {
			  videoStreamIndex = i;
			  pVideoCodecCtx = pFormatCtx->streams[i]->codec;
	      pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);

        if (pVideoCodec)
        {
	        res     = !(avcodec_open(pVideoCodecCtx, pVideoCodec) < 0);
          width   = pVideoCodecCtx->coded_width;
          height  = pVideoCodecCtx->coded_height;
        }

			  break;
		  }
    }

    if (!res)
    {
      CloseVideo();
    }
    else
    {
      pImgConvertCtx = sws_getContext(pVideoCodecCtx->width, pVideoCodecCtx->height,
            pVideoCodecCtx->pix_fmt,
            pVideoCodecCtx->width, pVideoCodecCtx->height,
            PIX_FMT_BGR24,
            SWS_BICUBIC, NULL, NULL, NULL);
    }
  }

  return res;
}

bool FFmpegDecoder::DecodeVideo(const uint8_t* pInBuffer, size_t nInbufferSize, AVFrame * pOutFrame)
{
  bool res = false;

  if (pVideoCodecCtx)
  {
    if (pInBuffer && pOutFrame)
    {
      int videoFrameBytes = 0;
      avcodec_decode_video(pVideoCodecCtx, pOutFrame, &videoFrameBytes, pInBuffer, nInbufferSize);
      res = (videoFrameBytes > 0);
    }
  }

  return res;
}


bool FFmpegDecoder::OpenAudio()
{
  bool res = false;

  if (pFormatCtx)
  {   
    audioStreamIndex = -1;

	  for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
	  {
	    if (pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_AUDIO)
		  {
        audioStreamIndex = i;
        pAudioCodecCtx = pFormatCtx->streams[i]->codec;
        pAudioCodec = avcodec_find_decoder(pAudioCodecCtx->codec_id);
        if (pAudioCodec)
        {
          res = !(avcodec_open(pAudioCodecCtx, pAudioCodec) < 0);       
        }
        break;
		  }
    }

    if (! res)
    {
      CloseAudio();
    }
  }
	
  return res;
}


void FFmpegDecoder::CloseVideo()
{
	if (pVideoCodecCtx)
	{
		avcodec_close(pVideoCodecCtx);
		pVideoCodecCtx = NULL;
		pVideoCodec = NULL;
    videoStreamIndex = 0;
	}
}


void FFmpegDecoder::CloseAudio()
{    
  if (pAudioCodecCtx)
	{
	  avcodec_close(pAudioCodecCtx);
    pAudioCodecCtx   = NULL;
		pAudioCodec      = NULL;
    audioStreamIndex = 0;
	}  
}


int FFmpegDecoder::DecodeAudio(int nStreamIndex, const uint8_t* pInBuffer, size_t nInBufferSize, 
                                    uint8_t* pOutBuffer, size_t nOutBufferSize)
{
  int decodedSize = 0;

  int packetSize = nInBufferSize;
  uint8_t* pPacketData = (uint8_t*) pInBuffer;

  while (packetSize > 0)
  {
    int sizeToDecode = nOutBufferSize;
    uint8_t* pDest = pOutBuffer + decodedSize;

    int packetDecodedSize = avcodec_decode_audio2(pAudioCodecCtx, (int16_t*)pDest, 
      &sizeToDecode, pPacketData, packetSize);

    if (packetDecodedSize < 0)
    {
      decodedSize = 0;
      break;
    }

    packetSize -= packetDecodedSize;
    pPacketData += packetDecodedSize;

    if (sizeToDecode <= 0)
    {
      continue;
    }

    decodedSize += sizeToDecode;
  }

  return decodedSize;
}