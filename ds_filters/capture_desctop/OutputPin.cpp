#include "StdAfx.h"
#include "Filter.h"
#include "OutputPin.h"


#define DECLARE_PTR(type, ptr, expr) type* ptr = (type*)(expr);

COutputPin::COutputPin(HRESULT *phr, CFilter *pParent, LPCWSTR pPinName) :
    CSourceStream(NAME((LPCTSTR)g_wszName),phr, pParent, pPinName), m_pParent(pParent)
{
	m_hDeskDC = GetDC(GetDesktopWindow());
    m_hDC = CreateCompatibleDC(0);
	RECT rc;
	GetWindowRect(GetDesktopWindow(),&rc);
	SetCaptureRect(0, 0, rc.right, rc.bottom, 30);
}


COutputPin::~COutputPin(void)
{
	if(m_hDIB) DeleteObject(m_hDIB);
}

HRESULT COutputPin::FillBuffer(IMediaSample *pms)
{
	REFERENCE_TIME rtNow;
    REFERENCE_TIME avgFrameTime = ((VIDEOINFOHEADER*)m_mt.pbFormat)->AvgTimePerFrame;

    BYTE *pData;
    long lDataLen;
    pms->GetPointer(&pData);
    lDataLen = pms->GetSize();

    DWORD tick = GetTickCount();
	BitBlt(m_hDC, 0, 0, m_CaptureRect.right - m_CaptureRect.left, m_CaptureRect.bottom - m_CaptureRect.top, m_hDeskDC, m_CaptureRect.left, m_CaptureRect.top, SRCCOPY);
    memcpy(pData, m_pDIBData, lDataLen);
    tick = GetTickCount() - tick;

    m_rtLastTime += tick * UNITS / 1000;
    pms->SetTime(&rtNow, &m_rtLastTime);
    pms->SetSyncPoint(TRUE);
    return NOERROR;
}

//CBaseOutputPin::DecideBufferSize Method
//The DecideBufferSize method sets the buffer requirements.
HRESULT COutputPin::DecideBufferSize(IMemAllocator *pIMemAlloc, ALLOCATOR_PROPERTIES *pProperties)
{
	CAutoLock cAutoLock(m_pFilter->pStateLock());
    HRESULT hr = NOERROR;

    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) m_mt.Format();
    pProperties->cBuffers = 1;
    pProperties->cbBuffer = pvi->bmiHeader.biSizeImage;

    ALLOCATOR_PROPERTIES Actual;
    hr = pIMemAlloc->SetProperties(pProperties,&Actual);

    if(FAILED(hr)) return hr;
    if(Actual.cbBuffer < pProperties->cbBuffer) return E_FAIL;

    return NOERROR;
}

HRESULT COutputPin::CheckMediaType(const CMediaType *pMediaType)
{
    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *)(pMediaType->Format());
    if(*pMediaType != m_mt) 
        return E_INVALIDARG;
    return S_OK;
}

HRESULT COutputPin::SetMediaType(const CMediaType *pmt)
{
    DECLARE_PTR(VIDEOINFOHEADER, pvi, pmt->Format());
    HRESULT hr = CSourceStream::SetMediaType(pmt);
    MakeDIB();
    return hr;
}

HRESULT COutputPin::GetMediaType(int iPosition, CMediaType *pmt)
{
//	*pmt = m_mt;
//    return S_OK;

	if(iPosition < 0) return E_INVALIDARG;
    if(iPosition > 8) return VFW_S_NO_MORE_ITEMS;

    if(iPosition == 0) 
    {
        *pmt = m_mt;
        return S_OK;
    }

    DECLARE_PTR(VIDEOINFOHEADER, pvi, pmt->AllocFormatBuffer(sizeof(VIDEOINFOHEADER)));
    ZeroMemory(pvi, sizeof(VIDEOINFOHEADER));

 	
	pvi->bmiHeader.biCompression = BI_RGB;
    pvi->bmiHeader.biBitCount    = GetDeviceCaps(m_hDeskDC, BITSPIXEL);
    pvi->bmiHeader.biSize       = sizeof(BITMAPINFOHEADER);
    pvi->bmiHeader.biWidth      = m_CaptureRect.right - m_CaptureRect.left;
    pvi->bmiHeader.biHeight     = m_CaptureRect.bottom - m_CaptureRect.top;
    pvi->bmiHeader.biPlanes     = 1;
    pvi->bmiHeader.biSizeImage  = GetBitmapSize(&pvi->bmiHeader);
    pvi->bmiHeader.biClrImportant = 0;

    pvi->AvgTimePerFrame = 1000000;

    SetRectEmpty(&(pvi->rcSource)); // we want the whole image area rendered.
    SetRectEmpty(&(pvi->rcTarget)); // no particular destination rectangle

    pmt->SetType(&MEDIATYPE_Video);
    pmt->SetFormatType(&FORMAT_VideoInfo);
    pmt->SetTemporalCompression(FALSE);

    // Work out the GUID for the subtype from the header info.
    const GUID SubTypeGUID = GetBitmapSubtype(&pvi->bmiHeader);
    pmt->SetSubtype(&SubTypeGUID);
    pmt->SetSampleSize(pvi->bmiHeader.biSizeImage);
    
    return NOERROR;

}

//
// Notify
// Ignore quality management messages sent from the downstream filter
STDMETHODIMP COutputPin::Notify(IBaseFilter * pSender, Quality q)
{
    return E_NOTIMPL;
} // Notify

//////////////////////////////////////////////////////////////////////////
//  IAMStreamConfig
//////////////////////////////////////////////////////////////////////////
HRESULT STDMETHODCALLTYPE COutputPin::SetFormat(AM_MEDIA_TYPE *pmt)
{
    DECLARE_PTR(VIDEOINFOHEADER, pvi, m_mt.pbFormat);
    m_mt = *pmt;
    IPin* pin; 
    ConnectedTo(&pin);
    if(pin)
    {
        IFilterGraph *pGraph = m_pParent->GetGraph();
        pGraph->Reconnect(this);
    }
    return S_OK;
}

HRESULT STDMETHODCALLTYPE COutputPin::GetFormat(AM_MEDIA_TYPE **ppmt)
{
    *ppmt = CreateMediaType(&m_mt);
    return S_OK;
}

HRESULT STDMETHODCALLTYPE COutputPin::GetNumberOfCapabilities(int *piCount, int *piSize)
{
    *piCount = 8;
    *piSize = sizeof(VIDEO_STREAM_CONFIG_CAPS);
    return S_OK;
}

//TODo i don't undastend this function enough
HRESULT STDMETHODCALLTYPE COutputPin::GetStreamCaps(int iIndex, AM_MEDIA_TYPE **pmt, BYTE *pSCC)
{
    *pmt = CreateMediaType(&m_mt);
    DECLARE_PTR(VIDEOINFOHEADER, pvi, (*pmt)->pbFormat);

    if (iIndex == 0) iIndex = 4;
	
	pvi->bmiHeader.biCompression = BI_RGB;
    pvi->bmiHeader.biBitCount    = GetDeviceCaps(m_hDeskDC, BITSPIXEL);
    pvi->bmiHeader.biSize       = sizeof(BITMAPINFOHEADER);
    pvi->bmiHeader.biWidth      = m_CaptureRect.right - m_CaptureRect.left;
    pvi->bmiHeader.biHeight     = m_CaptureRect.bottom - m_CaptureRect.top;
    pvi->bmiHeader.biPlanes     = 1;
    pvi->bmiHeader.biSizeImage  = GetBitmapSize(&pvi->bmiHeader);
    pvi->bmiHeader.biClrImportant = 0;

    SetRectEmpty(&(pvi->rcSource)); // we want the whole image area rendered.
    SetRectEmpty(&(pvi->rcTarget)); // no particular destination rectangle

    (*pmt)->majortype = MEDIATYPE_Video;
    (*pmt)->subtype = MEDIASUBTYPE_RGB24;
    (*pmt)->formattype = FORMAT_VideoInfo;
    (*pmt)->bTemporalCompression = FALSE;
    (*pmt)->bFixedSizeSamples= FALSE;
    (*pmt)->lSampleSize = pvi->bmiHeader.biSizeImage;
    (*pmt)->cbFormat = sizeof(VIDEOINFOHEADER);
    
    DECLARE_PTR(VIDEO_STREAM_CONFIG_CAPS, pvscc, pSCC);
    
    pvscc->guid = FORMAT_VideoInfo;
    pvscc->VideoStandard = AnalogVideo_None;
    pvscc->InputSize.cx = 640;
    pvscc->InputSize.cy = 480;
    pvscc->MinCroppingSize.cx = 80;
    pvscc->MinCroppingSize.cy = 60;
    pvscc->MaxCroppingSize.cx = 640;
    pvscc->MaxCroppingSize.cy = 480;
    pvscc->CropGranularityX = 80;
    pvscc->CropGranularityY = 60;
    pvscc->CropAlignX = 0;
    pvscc->CropAlignY = 0;

    pvscc->MinOutputSize.cx = 80;
    pvscc->MinOutputSize.cy = 60;
    pvscc->MaxOutputSize.cx = 640;
    pvscc->MaxOutputSize.cy = 480;
    pvscc->OutputGranularityX = 0;
    pvscc->OutputGranularityY = 0;
    pvscc->StretchTapsX = 0;
    pvscc->StretchTapsY = 0;
    pvscc->ShrinkTapsX = 0;
    pvscc->ShrinkTapsY = 0;
    pvscc->MinFrameInterval = 200000;   //50 fps
    pvscc->MaxFrameInterval = 50000000; // 0.2 fps
    pvscc->MinBitsPerSecond = (80 * 60 * 3 * 8) / 5;
    pvscc->MaxBitsPerSecond = 2048 * 1536 * 3 * 8 * 50;

    return S_OK;
}

void COutputPin::SetCaptureRect(int left, int top, int right, int bottom, int fps)
{
	//TODO we must check bounds of rect before setting
	//    RECT rc;
	//	GetWindowRect(GetDesktopWindow(),&rc);
	m_CaptureRect.left = left;
    m_CaptureRect.top = top;
    m_CaptureRect.right = right;
	m_CaptureRect.bottom = bottom;

    // Measure capture rate
    DWORD tick = GetTickCount();
    for(int i = 0; i < 5; ++i)
    {
        BitBlt(m_hDC, 0, 0, m_CaptureRect.right - m_CaptureRect.left, m_CaptureRect.bottom - m_CaptureRect.top, m_hDeskDC, m_CaptureRect.left, m_CaptureRect.top, SRCCOPY);
    }
    tick = GetTickCount() - tick;
    tick /= 5;
    tick += 10;

    double actualFPS = 1000.0 / (double)tick;
    if(fps < actualFPS) 
        actualFPS = fps;

    DECLARE_PTR(VIDEOINFOHEADER, pvi, m_mt.AllocFormatBuffer(sizeof(VIDEOINFOHEADER)));
    ZeroMemory(pvi, sizeof(VIDEOINFOHEADER));

    pvi->bmiHeader.biCompression = BI_RGB;
    pvi->bmiHeader.biBitCount    = GetDeviceCaps(m_hDeskDC, BITSPIXEL);
    pvi->bmiHeader.biSize       = sizeof(BITMAPINFOHEADER);
    pvi->bmiHeader.biWidth      = m_CaptureRect.right - m_CaptureRect.left;
    pvi->bmiHeader.biHeight     = m_CaptureRect.bottom - m_CaptureRect.top;
    pvi->bmiHeader.biPlanes     = 1;
    pvi->bmiHeader.biSizeImage  = GetBitmapSize(&pvi->bmiHeader);
    pvi->bmiHeader.biClrImportant = 0;

	pvi->AvgTimePerFrame = (REFERENCE_TIME)(10000000 / actualFPS);

    SetRectEmpty(&(pvi->rcSource)); // we want the whole image area rendered.
    SetRectEmpty(&(pvi->rcTarget)); // no particular destination rectangle

    m_mt.SetType(&MEDIATYPE_Video);
    m_mt.SetFormatType(&FORMAT_VideoInfo);
    m_mt.SetTemporalCompression(FALSE);

    // Work out the GUID for the subtype from the header info.
    const GUID SubTypeGUID = GetBitmapSubtype(&pvi->bmiHeader);
    m_mt.SetSubtype(&SubTypeGUID);
    m_mt.SetSampleSize(pvi->bmiHeader.biSizeImage);
}

void COutputPin::MakeDIB()
{
    if(m_hDIB) DeleteObject(m_hDIB);
    BITMAPINFO bi;
    DECLARE_PTR(VIDEOINFOHEADER, pvi, m_mt.Format());
    bi.bmiHeader = pvi->bmiHeader;
    m_hDIB = CreateDIBSection(0, &bi, DIB_RGB_COLORS, (void**)&m_pDIBData, 0, 0);
    SelectObject(m_hDC, m_hDIB);
}