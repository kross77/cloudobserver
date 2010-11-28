#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>

//#include <unistd.h>
//#include <stdlib.h>
//#include <Pthread.h>

#include <boost/thread.hpp>
#include <signal.h>

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

static boost::thread captureThread;
void CloseApplication()
{
	captureThread.interrupt();
	captureThread.join();
	exit(0);
}

void WaitingForExitProgram() 
{
	string quite;
	while(quite != "exit")
	{
		cout << "Input 'exit' to quite" << endl;
		cin >> quite;
		Sleep(250);
	}
	CloseApplication();
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
	CloseApplication();
    return TRUE;
}

void CaptureLoop(void) 
{
	//printf("thread_function started. Arg was %s\n", (char *)arg);
	// pause for 3 seconds
	// sleep(3);
	// exit and  return a message to another thread
	// that may be waiting for us to finish
	//pthread_exit ("thread one all done”);
	while(true)
	{
		boost::xtime xt;
		boost::xtime_get(&xt, boost::TIME_UTC);


		xt.sec +=1;

		boost::thread::sleep(xt);
	}
}



int main(int argc, char* argv[])
{
	//	pthread_t capture_thread;

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

	captureThread = boost::thread(&CaptureLoop);

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler,TRUE);

	WaitingForExitProgram();

	return 0;
}