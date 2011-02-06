#pragma once

extern const WCHAR g_wszName[];

class CFilter : public CSource
{
public:
	//Function create one more instance for this filter. Specified in Called by system
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

	//Each filter is COM oject and must implement IUnknown interface
	DECLARE_IUNKNOWN;

    STDMETHODIMP Notify(IBaseFilter * pSender, Quality q);
	
    IFilterGraph *GetGraph() {return m_pGraph;}

private:
	//Privite constructor. All object must be created from CreateInstance function
	CFilter(LPUNKNOWN punk, HRESULT *phr);
};

