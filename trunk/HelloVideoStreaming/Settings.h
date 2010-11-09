/*
  Settings of sample
 */

#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#define VIDEO_WIDTH			640		// pixels
#define VIDEO_HEIGHT		480		// pixels
#define VIDEO_FRAME_RATE	15		// hertz

#define AUDIO_SAMPLE_RATE	44100	// hertz
#define AUDIO_FREQUENCY		440		// hertz
#define AUDIO_VOLUME		40		// decibels

#define AUDIO_BUFFERSIZE    4410 // size of audio char array

#define OUTPUT_URL	"tcp://127.0.0.1:4774/" 
#define OUTPUT_CONTAINER	"flv"



#endif // __SETTINGS_H_
