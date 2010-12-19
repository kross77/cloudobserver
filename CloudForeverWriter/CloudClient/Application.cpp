#include "StdAfx.h"
#include <boost/thread.hpp>

#include "Application.h"
#include "SourceStream.h"


using namespace std;

CApplication::CApplication(void)
{
}

CApplication::~CApplication(void)
{
}

void CApplication::Init()
{
	//create camera's list
}

void CApplication::CloseApplication()
{
	SourceStream::stopAll();
	exit(0);
}

void CApplication::StartDefault()
{
}

void CApplication::MainLoop() 
{
	string quite;
	while(quite != "exit")
	{
		cout << "Input 'exit' to quite" << endl;
		cin >> quite;
		if (quite == "add") {
			int videoId = SourceStream::startStream();
		}


		Sleep(250);
	}
	CloseApplication();
}
