#include "stdafx.h"
#include "guids.h"
#include "Filter.h"
#include "OutputPin.h"

EXTERN_C const GUID CLSID_SourceSkelet;


CFilter::CFilter(LPUNKNOWN lpunk, HRESULT *phr) :
CSource(NAME((LPCTSTR)g_wszName), lpunk, CLSID_SourceSkelet)    
{
	CAutoLock cAutoLock(&m_cStateLock);

	//create output pins
	m_paStreams = (CSourceStream **) new CSourceStream *[1];
    m_paStreams[0] = new COutputPin(phr, this, (LPWSTR)g_wszName);
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	CFilter *pNewObject = new CFilter(punk, phr);
    if (pNewObject == NULL) {
        if (phr)
            *phr = E_OUTOFMEMORY;
    }

    return pNewObject;
}

STDMETHODIMP CFilter::Notify(IBaseFilter * pSender, Quality q)
{
    return E_NOTIMPL;
}
