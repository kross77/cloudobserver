#include "StdAfx.h"
#include "list.h"
#include <windows.h>
#include <dshow.h>
#include <boost/lexical_cast.hpp>
#pragma comment(lib, "strmiids")
using namespace std;
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

int CamerasList::SelectFromList()
{	int i = 0;
    int SelectedIndex;
	IEnumMoniker *pEnum;
	printf("\nLet us select video device\n");
	printf("Available Capture Devices are:\n");
	HRESULT hr;
	hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
	if (SUCCEEDED(hr))
	{
		IMoniker *pMoniker = NULL;
		
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
 		SelectedIndex = 999;
	if (i <= 0)
	{
		cout <<"No devices found. \n " << endl;
		cout <<"Please restart application."  << endl;
		cin.get();
		Sleep(999999);

	}else if(i == 1){
			cout <<"Default device will be used" << std::endl;
			SelectedIndex = 0;
		}else{
		while(SelectedIndex > i-1 || SelectedIndex < 0)
		{
			try{		
			std::string s;
			std::getline( cin, s, '\n' );
			SelectedIndex =  boost::lexical_cast<int>(s);
			}
			catch(std::exception& e){
				std::cout <<"please input index from 0 to " << i-1 << std::endl;
				SelectedIndex = 999;
			}
		}}
		pEnum->Release();
	}else
	{
		printf("no Video Devices found. \n") ;
		cout <<"Please restart application."  << endl;
		cin.get();
		Sleep(999999);
		return 999;
	}
	return SelectedIndex;
}
