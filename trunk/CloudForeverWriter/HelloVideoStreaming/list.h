#pragma once

#include <windows.h>
#include <dshow.h>
#include <iostream>
class CamerasList
{
public:
	CamerasList(void);
	~CamerasList(void);
	HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void DisplayDeviceInformation(IEnumMoniker *pEnum);
	void PrintList();
};
