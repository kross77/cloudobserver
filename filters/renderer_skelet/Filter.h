#pragma once
#include "InputPin.h"
class CFilter : public CBaseRenderer
{
public:
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

	DECLARE_IUNKNOWN;

	HRESULT CheckMediaType(const CMediaType *pmt);
	HRESULT DoRenderSample(IMediaSample *pMediaSample);

private:
	CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
	~CFilter();

	CInputPin m_InputPin;          // IPin based interfaces

};

