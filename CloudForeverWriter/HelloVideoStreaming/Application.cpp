#include "StdAfx.h"
#include "Application.h"

using namespace std;

boost::thread *CApplication::captureThread = NULL;

CApplication::CApplication(void)
{
}

CApplication::~CApplication(void)
{
}

void CApplication::Init()
{
	CApplication::captureThread = &boost::thread(CaptureLoop);
}

void CApplication::CaptureLoop(void) 
{
	while(true)
	{
		boost::xtime xt;
		boost::xtime_get(&xt, boost::TIME_UTC);
		xt.sec +=1;
		boost::thread::sleep(xt);
	}
}

void CApplication::CloseApplication()
{
	CApplication::captureThread->interrupt();
	CApplication::captureThread->join();
	exit(0);
}

void CApplication::MainLoop() 
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
