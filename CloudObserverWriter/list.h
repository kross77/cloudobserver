#pragma once
#ifdef WIN32
#include <windows.h>
#include <dshow.h>
#else
typedef int HRESULT;
typedef int REFGUID;
typedef int IEnumMoniker;
#endif
#include <iostream>
class CamerasList
{
public:
	CamerasList(void);
	~CamerasList(void);
#ifdef WIN32
	HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
#endif
	int SelectFromList();

};
