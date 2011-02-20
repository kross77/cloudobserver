/*
 *  Include ffmpeg files
 */


#pragma once

#ifndef __STDC_CONSTANT_MACROS
  #define __STDC_CONSTANT_MACROS
#endif

//#include "stdint.h"
#ifdef WIN32
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#else
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#endif
