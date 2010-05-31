#pragma once
class CFilter;

class CInputPin :
	public CRendererInputPin
{
public:
	CInputPin(
		TCHAR *pObjectName,             // Object string description
		CFilter *pRenderer,      // Used to delegate locking
		CCritSec *pInterfaceLock,       // Main critical section
		HRESULT *phr,                   // OLE failure return code
		LPCWSTR pPinName);              // This pins identification
private:
	CFilter *m_pRenderer;
	CCritSec *m_pInterfaceLock;
};
