#ifndef FFMPEG_H
#define FFMPEG_H

// Allow C99 macros.
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

namespace ffmpeg
{

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

}

#endif // FFMPEG_H
