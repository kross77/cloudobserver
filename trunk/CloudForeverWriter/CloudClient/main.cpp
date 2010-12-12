#include "stdafx.h"
#include "Application.h"
#include <windows.h>


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
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler,TRUE);

	CApplication::Init();
	CApplication::StartDefault();
	CApplication::MainLoop();

	return 0;
}