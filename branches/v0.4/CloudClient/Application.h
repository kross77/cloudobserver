#pragma once

#include <windows.h>
#include <iostream>

class CApplication
{
public:
	CApplication(void);
	~CApplication(void);

	static void CloseApplication();
	static void MainLoop();
	static void Init();
	static void StartDefault();

public:
};
