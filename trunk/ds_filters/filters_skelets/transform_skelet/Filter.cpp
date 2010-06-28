// This is the main DLL file.

#include "stdafx.h"
#include"guids.h"
#include "dll.h"
#include "Filter.h"


CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CTransInPlaceFilter(tszName, punk, CLSID_Filter, phr, true)
{
}
CFilter::~CFilter()
{
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	CFilter *pNewObject = new CFilter(NAME(FILTER_TCHAR_NAME), punk, phr);
    if (pNewObject == NULL) {
        if (phr)
            *phr = E_OUTOFMEMORY;
    }

    return pNewObject;
}


HRESULT CFilter::CheckInputType(const CMediaType* mtIn)
{
	return E_INVALIDARG;
}

STDMETHODIMP CFilter::JoinFilterGraph(IFilterGraph *pGraph, LPCWSTR pName)
{
	return CBaseFilter::JoinFilterGraph(pGraph,pName);
}

HRESULT CFilter::Transform(IMediaSample *pMediaSample)
{
	return NOERROR;
}
