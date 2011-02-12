//only for windows
#include "StdAfx.h"
#include <dshow.h>
#include <comdef.h>
#include "ResourcesList.h"
#pragma comment(lib, "strmiids")

using namespace std;

HRESULT ResourcesList::EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum )
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

int ResourcesList::EnumerateVideoDevices()
{
	IEnumMoniker *pEnum;
	HRESULT hr;

	hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
	if (FAILED(hr))
		return -1;

	
	IMoniker *pMoniker = NULL;
	int idx = 0; //default device
	while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
	{
		IPropertyBag *pPropBag;
		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
		if (FAILED(hr))
		{
			pMoniker->Release();
			continue;  
		}
		CameraDescription *camera = new CameraDescription();
		VARIANT var;
		VariantInit(&var);
		
		// Get description and friendly name.
		hr = pPropBag->Read(L"Description", &var, 0);
		if (SUCCEEDED(hr))
		{
			_bstr_t bstr_t(var.bstrVal);
			camera->description = string(bstr_t);			
		}
		hr = pPropBag->Read(L"FriendlyName", &var, 0);
		if (SUCCEEDED(hr))
		{
			_bstr_t bstr_t(var.bstrVal);
			camera->description = string(bstr_t);	
		}
		camera->idx = idx ++;		

		VariantClear(&var); 
		pPropBag->Release();
		pMoniker->Release();
	}
}