#include "stdafx.h"
#include "guids.h"
#include "Filter.h"
#include "dll.h"
#include <winsock.h>

CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CBaseRenderer(CLSID_Filter, tszName, punk, phr),
		m_InputPin(NAME("Input Pin"),this,&m_InterfaceLock,phr,L"Input")
{
	// Class Constructor makes all routines for 
	// preparation to samples sendings via sockets
	WBADDRESS = OLESTR("127.0.0.1");
	PORT = 8001;

	    WORD wVersionRequested;

		WSADATA wsaData;
		wVersionRequested = MAKEWORD(2, 2);

	WSAStartup(wVersionRequested, &wsaData);

//	Connect(WBADDRESS,PORT);

}
CFilter::~CFilter()
{
	Disconnect();
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	ASSERT(phr); 


	CFilter *pNewObject = new CFilter(FILTER_TCHAR_NAME, punk, phr);
    if (pNewObject == NULL) 
	{
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
	BYTE *buff;
	pMediaSample->GetPointer(&buff);
/*
hr = pAsfWriter->QueryInterface(IID_ICoudInetControl, (void **)
&m_FileSink);
m_FileSink->SetFileName(tfilename, NULL)
*/
	//send ( Socket,(const char *) buff, pMediaSample->GetActualDataLength(), 0 ) ;

	return NOERROR;
}

int CFilter::Connect(LPCOLESTR addr, int port)
{
	int sock;
	struct sockaddr_in socketaddr;
	memset((char *)&socketaddr, NULL, sizeof(socketaddr));
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	socketaddr.sin_port = htons(port);
	sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		return -1;
	}

	int size=sizeof(socketaddr);

	sock = connect(sock,(LPSOCKADDR)&socketaddr,size);
}

void CFilter::Disconnect()
{
	closesocket (Socket);
	WSACleanup ();	
}


HRESULT CFilter::SetAddress( LPCOLESTR pszAddress, int port) 
{
	//PORT = port;
	//WBADDRESS = pszAddress;
	Connect(WBADDRESS,PORT);
	return NOERROR;
}

//STDMETHODIMP CInputPin::EndOfStream(void)
//{
//	return CRendererInputPin::EndOfStream();
//}

#include "cloud_ctrl_h.h"
//
// NonDelegatingQueryInterface
//
// Override this to say what interfaces we support where
//
STDMETHODIMP CFilter::NonDelegatingQueryInterface(REFIID riid, void ** ppv)
{
    CheckPointer(ppv,E_POINTER);
 //   CAutoLock lock(&m_Lock);

    // Do we have this interface

	if (riid == IID_IFileSinkFilter) {
        return GetInterface((IFileSinkFilter *) this, ppv);
    } 
    if (riid == IID_ICloudInetControl) {
        return GetInterface((ICloudInetControl *) this, ppv);
    }
	return CBaseRenderer::NonDelegatingQueryInterface(riid,ppv);
}