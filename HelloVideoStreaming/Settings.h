/*
  Settings of sample
 */

#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#define VIDEO_WIDTH			320		// pixels
#define VIDEO_HEIGHT		240		// pixels
#define VIDEO_FRAME_RATE	23		// hertz

#define AUDIO_SAMPLE_RATE	44100	// hertz
#define AUDIO_FREQUENCY		440		// hertz
#define AUDIO_VOLUME		40		// decibels

#define AUDIO_BUFFERSIZE    4410 // size of audio char array

#define OUTPUT_URL	"tcp://127.0.0.1:4778/"
#define OUTPUT_CONTAINER	"flv"



#endif // __SETTINGS_H_
