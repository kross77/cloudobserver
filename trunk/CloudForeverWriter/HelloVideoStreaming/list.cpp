#include "StdAfx.h"
#include "list.h"
#include <windows.h>
#include <dshow.h>
#pragma comment(lib, "strmiids")
CamerasList::CamerasList(void)
{
}

CamerasList::~CamerasList(void)
{
}

HRESULT CamerasList::EnumerateDevices( REFGUID category, IEnumMoniker **ppEnum )
{
	// Create the System Device Enumerator.
	ICreateDevEnum *pDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,  
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

	if (SUCCEEDED(hr))
	{
		// Create an enumerator for the category.
		hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
		if (hr == S_FALSE)
		{
			hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
		}
		pDevEnum->Release();
	}
	return hr;
}

void CamerasList::DisplayDeviceInformation( IEnumMoniker *pEnum )
{
	IMoniker *pMoniker = NULL;
	int i = 1;
	while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
	{
		IPropertyBag *pPropBag;
		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
		if (FAILED(hr))
		{
			pMoniker->Release();
			continue;  
		} 

		VARIANT var;
		VariantInit(&var);

		// Get description or friendly name.
		hr = pPropBag->Read(L"Description", &var, 0);
		if (FAILED(hr))
		{
			hr = pPropBag->Read(L"FriendlyName", &var, 0);
		}
		if (SUCCEEDED(hr))
		{
			std::cout << i;
			printf(") %S\n", var.bstrVal);
			i++;
			VariantClear(&var); 
		}

		hr = pPropBag->Write(L"FriendlyName", &var);

		pPropBag->Release();
		pMoniker->Release();
	}
}

void CamerasList::PrintList()
{
	IEnumMoniker *pEnum;

	HRESULT hr;
	hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
	if (SUCCEEDED(hr))
	{
		DisplayDeviceInformation(pEnum);
		pEnum->Release();
	}

}
