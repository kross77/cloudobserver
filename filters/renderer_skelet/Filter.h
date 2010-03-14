#pragma once

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
};

