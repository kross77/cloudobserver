#pragma once
class CFilter;

class CInputPin :
	public CRendererInputPin
{
public:
	CInputPin(
		TCHAR *pObjectName,             // Object string description
		CFilter *pRenderer,			    // Used to delegate locking
		CCritSec *pInterfaceLock,       // Main critical section
		HRESULT *phr,                   // OLE failure return code
		LPCWSTR pPinName);              // This pins identification

	STDMETHODIMP EndOfStream(void);
private:
	CFilter *m_pRenderer;
	CCritSec *m_pInterfaceLock;
};

/////////////////////////////////////

//#pragma once
//#include "InputPin.h"
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
	HANDLE m_hFile;

private:
	//Privite constructor. All object must be created from CreateInstance function
	CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
	~CFilter();

	CInputPin m_InputPin;          // IPin based interfaces

	//HANDLE m_hFile;
};

