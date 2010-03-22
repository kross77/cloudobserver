// insert comments here

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "COEncoder.h"


int main(int argc, char *argv[])
{	
	// check number of arguments
	if(argc != 2)
	{
		fprintf(stderr,"Usage: %s <filename.wav>\n", argv[0]);
		fprintf(stderr,"Descr: Short demo to show how to use the lame_enc.dll library file\n");
		fprintf(stderr,"Note : WAV file is assumed to to have the following parameters\n");
		fprintf(stderr,"     : 44100 Hz, stereo, 16 Bits per sample\n");
		return -1;
	}


	Encoder WAV;
	char* InFileName = argv[1];
	WAV.Encode(InFileName);

	return 0;
}
