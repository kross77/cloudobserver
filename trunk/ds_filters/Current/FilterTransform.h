#pragma once
//We must implement 2 methods CheckInputType and Transform for using filters of this type
class CFilter : public CTransInPlaceFilter
{
public:
	//Function create one more instance for this filter. Specified in Called by system
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

	//Each filter is COM oject and must implement IUnknown interface
	DECLARE_IUNKNOWN;

	//method is called when try to connect input pin and check supporting media type 
	//for it
	HRESULT CheckInputType(const CMediaType* mtIn);

	STDMETHODIMP JoinFilterGraph(IFilterGraph *pGraph, LPCWSTR pName);

	//method is called evry time one media samples is ready for transform
	HRESULT Transform(IMediaSample *pMediaSample);
	
	//method for sending data via socket
	HRESULT SendData(IMediaSample *pMediaSample);

private:
	//Privite constructor. All objects must be created from CreateInstance function
	CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
	~CFilter();
};

