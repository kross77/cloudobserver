#include "stdafx.h"
#include"guids.h"
#include "dll.h"
#include "Filter.h"

EXTERN_C const GUID CLSID_RendererSkelet;

CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CBaseRenderer(CLSID_RendererSkelet, tszName, punk, phr),
		m_InputPin(NAME("Input Pin"),this,&m_InterfaceLock,phr,L"Input")
{
	m_hFile = NULL;

}

CFilter::~CFilter()
{
	FileClose();

    //delete m_pFileName;
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
	CAutoLock lock(&m_Lock);

	if (riid == IID_IFileSinkFilter) {
        return GetInterface((IFileSinkFilter *) this, ppv);
    }

	if (riid == IID_IBaseFilter)
	{
		return GetInterface((IBaseFilter *) this, ppv);
	}

	if (riid == IID_IMediaFilter) 
	{
		return GetInterface((IMediaFilter *) this, ppv);
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


HRESULT CFilter::OnStopStreaming()
{
	FileClose();
	return NOERROR;
}

HRESULT	CFilter::OnStartStreaming()
{
 //ResetStreamingTimes();
	
	return FileOpen();
}

HRESULT	CFilter::FileOpen()
{
    TCHAR *pFileName = NULL;

   // Is the file already opened
    if (m_hFile != NULL) {
        return NOERROR;
    }

    // Has a filename been set yet
   if (m_pFileName == NULL) {
        return ERROR_INVALID_NAME;
    }

    // Convert the UNICODE filename if necessary
#if 0
#if defined(WIN32) && !defined(UNICODE)
    char convert[MAX_PATH];

    if(!WideCharToMultiByte(CP_ACP,0,m_pFileName,-1,convert,MAX_PATH,0,0))
        return ERROR_INVALID_NAME;

    pFileName = convert;
#else
    pFileName = m_pFileName;
#endif
#endif
	pFileName = m_pFileName;
    // Try to open the file
    m_hFile = CreateFile((LPCTSTR) pFileName,   // The filename
                         GENERIC_WRITE,         // File access
                         0,       // Share access
                         NULL,                  // Security
                         CREATE_ALWAYS,         // Open flags
                         (DWORD) 0,             // More flags
                         NULL);                 // Template

    if (m_hFile == NULL) 
    {
        DWORD dwErr = GetLastError();
        return HRESULT_FROM_WIN32(dwErr);
    }

    return S_OK;
	}
HRESULT	CFilter::FileClose()
{
    // Must lock this section to prevent problems related to
    // closing the file while still receiving data in Receive()
    CAutoLock lock(&m_Lock);

    if (m_hFile == NULL) {
        return NOERROR;
    }

    CloseHandle(m_hFile);
    m_hFile = NULL; // Invalidate the file 

    return NOERROR;
}

//
// SetFileName
//
// Implemented for IFileSinkFilter support
//
STDMETHODIMP CFilter::SetFileName(LPCOLESTR pszFileName,const AM_MEDIA_TYPE *pmt)
{
    // Is this a valid filename supplied

CheckPointer(pszFileName,E_POINTER);
    if(wcslen(pszFileName) > MAX_PATH)
        return ERROR_FILENAME_EXCED_RANGE;

    // Take a copy of the filename

    size_t len = 1+lstrlenW(pszFileName);
    m_pFileName = new WCHAR[len];
    if (m_pFileName == 0)
        return E_OUTOFMEMORY;

    HRESULT hr = StringCchCopyW(m_pFileName, len, pszFileName);

    // Clear the global 'write error' flag that would be set
    // if we had encountered a problem writing the previous dump file.
    // (eg. running out of disk space).
//    m_fWriteError = FALSE;

    // Create the file then close it

    hr = FileOpen();
    FileClose();


	return hr;

} // SetFileName


//
// GetCurFile
//
// Implemented for IFileSinkFilter support
//
STDMETHODIMP CFilter::GetCurFile(LPOLESTR * ppszFileName,AM_MEDIA_TYPE *pmt)
{
    CheckPointer(ppszFileName, E_POINTER);
    *ppszFileName = NULL;

    if (m_pFileName != NULL) 
    {
        size_t len = 1+lstrlenW(m_pFileName);
        *ppszFileName = (LPOLESTR)
        QzTaskMemAlloc(sizeof(WCHAR) * (len));

        if (*ppszFileName != NULL) 
        {
            HRESULT hr = StringCchCopyW(*ppszFileName, len, m_pFileName);
        }
    }

    if(pmt) 
    {
        ZeroMemory(pmt, sizeof(*pmt));
        pmt->majortype = MEDIATYPE_NULL;
        pmt->subtype = MEDIASUBTYPE_NULL;
    }

    return S_OK;

} // GetCurFile
