#include "StdAfx.h"
#include "InputPin.h"

CInputPin::CInputPin(TCHAR *pObjectName, CFilter *pRenderer, 
					 CCritSec *pInterfaceLock, HRESULT *phr, LPCWSTR pPinName):
			CRendererInputPin((CBaseRenderer*)pRenderer,phr,pPinName),
				m_pRenderer(pRenderer),
				m_pInterfaceLock(pInterfaceLock)
{
}

STDMETHODIMP CInputPin::EndOfStream(void)
{
	return CRendererInputPin::EndOfStream();
}

//
// CheckMediaType
//
// Check if the pin can support this specific proposed type and format
//
HRESULT CInputPin::CheckMediaType(const CMediaType *)
{
    return S_OK;
}



// Break a filter connection
HRESULT CInputPin::BreakConnect()
{
//    if (m_pDump->m_pPosition != NULL) {
//        m_pDump->m_pPosition->ForceRefresh();
//    }

    return CRendererInputPin::BreakConnect();
}


//
// ReceiveCanBlock
//
STDMETHODIMP CInputPin::ReceiveCanBlock()
{
    return S_FALSE;
}