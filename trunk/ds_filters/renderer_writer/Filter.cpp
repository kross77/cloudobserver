#include "stdafx.h"
#include"guids.h"
#include "Filter.h"

EXTERN_C const GUID CLSID_RendererSkelet;

CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CBaseRenderer(CLSID_RendererSkelet, tszName, punk, phr),
		m_InputPin(NAME("Input Pin"),this,&m_InterfaceLock,phr,L"Input")
{
	m_hFile = CreateFile("c:/br_br.avi",       // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_NEW,             // create new file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template
	if (m_hFile == INVALID_HANDLE_VALUE) 
    { 
	m_hFile = CreateFile("c:/br_br_br.avi",       // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_NEW,             // create new file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template
    }


}
CFilter::~CFilter()
{
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	ASSERT(phr);    
	CFilter *pNewObject = new CFilter(NAME("fv Add Graph To ROT Sample Filter"), punk, phr);
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
	DWORD lpCount;
	BYTE *buff;
	pMediaSample->GetPointer(&buff);
	if (FALSE == WriteFile(m_hFile, buff, pMediaSample->GetActualDataLength(), &lpCount, NULL))
	{
		return NOERROR;
	}

	return NOERROR;
}

STDMETHODIMP CFilter::NonDelegatingQueryInterface(REFIID riid, void ** ppv)
{
    CheckPointer(ppv,E_POINTER);
 //   CAutoLock lock(&m_Lock);

    // Do we have this interface


	if (riid == IID_IBaseFilter)
	{
		return GetInterface((IBaseFilter *) this, ppv);
	}
	/*we must return the same way || riid == IID_IMediaFilter || riid == IID_IMediaPosition */
	/*if (riid == IID_IBaseFilter)
	{
		return GetInterface((IBaseFilter *) this, ppv);
	}
	*/
	/* return all not support interfaces */
	return CBaseRenderer::NonDelegatingQueryInterface(riid,ppv);
}
