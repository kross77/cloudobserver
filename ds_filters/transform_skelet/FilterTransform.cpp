// This is the main DLL file.

#include "stdafx.h"
#include"guids.h"
#include "FilterTransform.h"

EXTERN_C const GUID CLSID_TransformSkelet;

//CFilter::CFilter()
//{
//}
CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CTransInPlaceFilter(tszName, punk, CLSID_TransformSkelet, phr, true)
{
}
CFilter::~CFilter()
{
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	//ASSERT(phr);    
	CFilter *pNewObject = new CFilter(NAME("fv Add Graph To ROT Sample Filter"), punk, phr);
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
	//DWORD dwRot;
	//CAutoLock cAutoLock(&m_fvLock);
	//AddToRot(pGraph,&dwRot);

	return CBaseFilter::JoinFilterGraph(pGraph,pName);
}

//HRESULT FilterTransform::AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister)
//{
//	HANDLE g_hEvent=CreateEvent(NULL,TRUE,FALSE,"fvAddToRotEvent001");
//	if (WaitForSingleObject(g_hEvent,0)==WAIT_OBJECT_0) 
//		return S_OK;
//	
//	SetEvent(g_hEvent);
//	
//	IMoniker * pMoniker;
//	IRunningObjectTable *pROT;
//	if (FAILED(GetRunningObjectTable(0, &pROT))) 
//	{
//		return E_FAIL;
//	}
//	WCHAR wsz[256];
//	
//	wsprintfW(wsz, L"FilterGraph %08x pid %08x", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());
//	HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
//	if (SUCCEEDED(hr))
//	{
//		hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, pMoniker, pdwRegister);
//		pMoniker->Release();
//	}
//	pROT->Release();
//	return hr;
//}


HRESULT CFilter::Transform(IMediaSample *pMediaSample)
{
	return NOERROR;
}
