#pragma once
#include "source.h"

class COutputPin :
	public CSourceStream//, public IAMStreamConfig
{
public:
    //////////////////////////////////////////////////////////////////////////
    //  CSourceStream
    //////////////////////////////////////////////////////////////////////////
    COutputPin(HRESULT *phr, CFilter *pParent, LPCWSTR pPinName);
    ~COutputPin();

    HRESULT FillBuffer(IMediaSample *pms);
    HRESULT DecideBufferSize(IMemAllocator *pIMemAlloc, ALLOCATOR_PROPERTIES *pProperties);
    HRESULT CheckMediaType(const CMediaType *pMediaType);
    HRESULT GetMediaType(int iPosition, CMediaType *pmt);

	//////////////////////////////////////////////////////////////////////////
    //  IQualityControl
    //////////////////////////////////////////////////////////////////////////
	//We must overwrite this function from CBasePin class
    STDMETHODIMP Notify(IBaseFilter * pSender, Quality q);

    //HRESULT SetMediaType(const CMediaType *pmt);
    //HRESULT OnThreadCreate(void);

	//////////////////////////////////////////////////////////////////////////
    //  IAMStreamConfig
    //////////////////////////////////////////////////////////////////////////
	//we must implement IAMStreamConfig interface if we want change parameters of output filter 
	//output dimensions and frame rate
    HRESULT STDMETHODCALLTYPE SetFormat(AM_MEDIA_TYPE *pmt);
    HRESULT STDMETHODCALLTYPE GetFormat(AM_MEDIA_TYPE **ppmt);
    HRESULT STDMETHODCALLTYPE GetNumberOfCapabilities(int *piCount, int *piSize);
    HRESULT STDMETHODCALLTYPE GetStreamCaps(int iIndex, AM_MEDIA_TYPE **pmt, BYTE *pSCC);
	
private:
    REFERENCE_TIME m_rtLastTime;
	CFilter *m_pParent;
};