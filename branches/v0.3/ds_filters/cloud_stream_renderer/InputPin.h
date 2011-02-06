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
	 
// EndOfStream Notification 
STDMETHODIMP	EndOfStream(void);
HRESULT			CheckMediaType(const CMediaType *);
HRESULT			BreakConnect();
STDMETHODIMP	ReceiveCanBlock();

private:
	CFilter *m_pRenderer;
	CCritSec *m_pInterfaceLock;
};
