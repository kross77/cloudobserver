#pragma once
#include "InputPin.h"
//We must implement 2 functions CheckMediaType and DoRenderSample
class CFilter : public CBaseRenderer
{
public:
	//Function create one more instance for this filter. Specified in Called by system
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

	//Each filter is COM oject and must implement IUnknown interface
	DECLARE_IUNKNOWN;

	//method is called when try to connect input pin and check supporting media type 
	//for it
	HRESULT CheckMediaType(const CMediaType *pmt);
	
	HRESULT DoRenderSample(IMediaSample *pMediaSample);

private:
	//Privite constructor. All object must be created from CreateInstance function
	CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
	~CFilter();

	void SendSample(BYTE *buff, int length);

	CInputPin m_InputPin;          // IPin based interfaces

	HANDLE m_hFile;
};

