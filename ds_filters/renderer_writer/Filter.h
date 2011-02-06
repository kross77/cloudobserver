#pragma once
#include "InputPin.h"
//We must implement 2 functions CheckMediaType and DoRenderSample
class CFilter : public CBaseRenderer, public IFileSinkFilter
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
	
	//Filter Start and Stop control
	HRESULT OnStartStreaming();
	HRESULT OnStopStreaming();

    // Implements the IFileSinkFilter interface
    STDMETHODIMP SetFileName(LPCOLESTR pszFileName,const AM_MEDIA_TYPE *pmt);
    STDMETHODIMP GetCurFile(LPOLESTR * ppszFileName,AM_MEDIA_TYPE *pmt);

private:
	// Overriden to say what interfaces we support where
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);
	
	//Privite constructor. All object must be created from CreateInstance function
	CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
	~CFilter();

	CCritSec m_Lock;                // Main renderer critical section

	CInputPin m_InputPin;          // IPin based interfaces

	HRESULT	FileOpen();
	HRESULT	FileClose();

	HANDLE m_hFile;
	LPOLESTR m_pFileName;           // The filename where we dump
};

