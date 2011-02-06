#include "StdAfx.h"
#include "InputPin.h"

CInputPin::CInputPin(TCHAR *pObjectName, CFilter *pRenderer, 
					 CCritSec *pInterfaceLock, HRESULT *phr, LPCWSTR pPinName):
			CRendererInputPin((CBaseRenderer*)pRenderer,phr,pPinName),
				m_pRenderer(pRenderer),
				m_pInterfaceLock(pInterfaceLock)
{
}
