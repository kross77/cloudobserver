#pragma once

#include <windows.h>
#include <iostream>
#include <boost/thread.hpp>

class CApplication
{
public:
	CApplication(void);
	~CApplication(void);

	static void CloseApplication();
	static void MainLoop();
	static void Init();
	static void CaptureLoop();

public:
	static boost::thread *captureThread;
};
