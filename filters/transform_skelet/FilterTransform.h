#pragma once

class CFilter : public CTransInPlaceFilter
{
public:
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

	DECLARE_IUNKNOWN;
	HRESULT CheckInputType(const CMediaType* mtIn);

	STDMETHODIMP JoinFilterGraph(IFilterGraph *pGraph, LPCWSTR pName);

	HRESULT Transform(IMediaSample *pMediaSample);

private:

	CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
	~CFilter();


	//HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);
};

