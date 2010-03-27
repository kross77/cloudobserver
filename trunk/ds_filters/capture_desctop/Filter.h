#pragma once

extern const WCHAR g_wszName[];

class CFilter : public CSource
{
public:
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);
	DECLARE_IUNKNOWN;

    STDMETHODIMP Notify(IBaseFilter * pSender, Quality q);

	
    IFilterGraph *GetGraph() {return m_pGraph;}

private:
	CFilter(LPUNKNOWN punk, HRESULT *phr);
};

