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
	Connect();

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
	send ( Socket,(const char *) buff, pMediaSample->GetActualDataLength(), 0 ) ;

	return NOERROR;
}

void CFilter::Connect()
{
	WSAStartup ( 0x202, &WSAInformation );
	Socket = socket (AF_INET, SOCK_STREAM, 0);

	ConnectionInfo.sin_family			= AF_INET;
	ConnectionInfo.sin_port				= htons (PORT);
	ConnectionInfo.sin_addr.S_un.S_addr = inet_addr(WBADDRESS) ;

	connect (Socket, (sockaddr *) &ConnectionInfo , sizeof (ConnectionInfo));
}

void CFilter::Disconnect()
{
	closesocket (Socket);
	WSACleanup ();	
}

HRESULT CFilter::SetAddress( LPCOLESTR pszAddress) {
	return NOERROR;
}