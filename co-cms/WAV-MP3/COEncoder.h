// insert comments here

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "BladeMP3EncDLL.h"




class Encoder   // Encoding Class 
   {
       private:

		    BEINITSTREAM		beInitStream;
			BEENCODECHUNK		beEncodeChunk;
			BEDEINITSTREAM		beDeinitStream;
			BECLOSESTREAM		beCloseStream;
			BEVERSION			beVersion;
			BEWRITEVBRHEADER	beWriteVBRHeader;
			BEWRITEINFOTAG		beWriteInfoTag;

			HINSTANCE	hDLL;
			FILE*		pFileIn;
			FILE*		pFileOut;
			BE_VERSION	Version;
			BE_CONFIG	beConfig;

			CHAR		strFileIn[255];	
			CHAR		strFileOut[255];

			DWORD		dwSamples;
			DWORD		dwMP3Buffer;
			HBE_STREAM	hbeStream;
			BE_ERR		err	;
	
			PBYTE		pMP3Buffer;
			PSHORT		pWAVBuffer;
       public: 
			Encoder(); //Constructor for the C++ tutorial 
        
		   ~Encoder(); //destructor for the C++ Tutorial 
        
			int Encode (char* InputFile);
			
};

