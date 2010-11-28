#include "stdafx.h"
#include "Application.h"
#include <windows.h>
#include <iostream>
#include <boost/thread.hpp>

using namespace std;


int ParseServerName()
{
#if 0
		if(outputUrl == ""){
		cout << "Warning: No Cloud Observer server url found!" << endl ;
		getAdress();
	}else{
		replace_or_merge(outputUrl, "http://", "tcp://");
	}
	
	int encoderServer = encoder.ConnectToServer(outputUrl) ;
	if (encoderServer == -1)
	{
		getAdress();
	goto server;
}
if(outputUserName == ""){
	cout << "Please provide us with your user name" << endl ;
	getName();
}
#endif
	return 0;
}


BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
    switch(CEvent)
    {
    case CTRL_C_EVENT:
        break;
    case CTRL_BREAK_EVENT:
        break;
    case CTRL_CLOSE_EVENT:
        break;
    case CTRL_LOGOFF_EVENT:
        break;
    case CTRL_SHUTDOWN_EVENT:
        break;
    }
	CApplication::CloseApplication();
    return TRUE;
}




int main(int argc, char* argv[])
{
	//TODO getopt
	for(int i = 1; i<argc; i=i+2){
#if 0
		if(string(argv[i]) == "-camera") {cameraInt = atoi(argv[i+1]);} 
		if(string(argv[i]) == "-framerate" ){videoFrameRate = atoi(argv[i+1]);} 
		if(string(argv[i]) == "-width" ) {videoWidth = atoi(argv[i+1]);} 
		if(string(argv[i]) == "-height" ) {videoHeight = atoi(argv[i+1]);} 
		if(string(argv[i]) == "-microphone" ) {microphoneInt = atoi(argv[i+1]);} 
		if(string(argv[i]) == "-samplerate" ) {audioSampleRate = atoi(argv[i+1]);} 
		if(string(argv[i]) == "-server" ) {outputUrl = (argv[i+1]);} 
		if(string(argv[i]) == "-container" ) {outputContainer = (argv[i+1]);} 
		if(string(argv[i]) == "-nickname" ) {outputUserName = (argv[i+1]);} 
		if(string(argv[i]) == "-useLSD" ) {useLSD = atoi(argv[i+1]);} 
		if(string(argv[i]) == "-streamBitRate" ) {streamBitRate = atoi(argv[i+1]);} 
		if(string(argv[i]) == "-noMic" ) {noMic = atoi(argv[i+1]);} 
#endif
	}	
	Sleep(1000);

	CApplication::Init();
//	captureThread = boost::thread(&CaptureLoop);

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler,TRUE);

	CApplication::MainLoop();

	return 0;
}