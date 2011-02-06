#include "stdafx.h"
#include"guids.h"
#include "dll.h"
#include "Filter.h"



CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CBaseRenderer(CLSID_Filter, tszName, punk, phr),
		m_InputPin(NAME("Input Pin"),this,&m_InterfaceLock,phr,L"Input")
{
}

CFilter::~CFilter()
{
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	ASSERT(phr);    
	CFilter *pNewObject = new CFilter(NAME(FILTER_TCHAR_NAME), punk, phr);
    if (pNewObject == NULL) {
        if (phr)
            *phr = E_OUTOFMEMORY;
    }

    return pNewObject;
}

HRESULT CFilter::CheckMediaType(const CMediaType *pmt)
{
	return NOERROR;
}

HRESULT CFilter::DoRenderSample(IMediaSample *pMediaSample)
{
	//we can get pointer to data is renrered

//	BYTE *buff;
//	pMediaSample->GetPointer(&buff);

	//we can get actual size of data is saved in buffer
	//pMediaSample->GetActualDataLength();
	
	return NOERROR;
}
