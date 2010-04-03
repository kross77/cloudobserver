#include "stdafx.h"
#include"guids.h"
#include "Filter.h"
#include "dll.h"
#include  <winsock.h>

CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CBaseRenderer(CLSID_Filter, tszName, punk, phr),
		m_InputPin(NAME("Input Pin"),this,&m_InterfaceLock,phr,L"Input")
{

}
CFilter::~CFilter()
{
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	ASSERT(phr);    
	CFilter *pNewObject = new CFilter(FILTER_TCHAR_NAME, punk, phr);
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
	return NOERROR;
}

#define  PORT      31123			// Server Connection Port
#define  WBADDRESS  "127.0.0.1"		// Server Adress (Work Block Address)	

void CFilter::SendSample(BYTE *buff, int length)
{
	WSADATA         WSAInformation;
	SOCKET          Socket;
	BYTE            *DataPointer = buff;
	sockaddr_in     ConnectionInfo;
	unsigned long	DataSize = length;       

	//pMediaSample->GetPointer(&DataPointer);
	//DataSize = pMediaSample->GetActualDataLength();

	
	// Getting Windows Socket Apllication started and error check 
	if ( WSAStartup ( 0x202, &WSAInformation ) )
    {
		//printf ( " WSA Start Error  %d \n ", WSAGetLastError ( ) );
		//return -1;
    }

	    
	// Creating the AF_INET family STREAM socket of TCP type 
	Socket = socket (AF_INET, SOCK_STREAM, 0);
    
	// Error Check
	if  ( Socket < 0 )       
	{
		//printf (" Socket Error    %d \n ", WSAGetLastError () );
		//return  -1;
	}
	
	// Filling ConnectionInfo fields
	ConnectionInfo.sin_family = AF_INET;
	ConnectionInfo.sin_port   = htons (PORT);
    
	// Converting IP-Adress format (from symbolic to network-styled)
    if ( inet_addr (WBADDRESS) != INADDR_NONE ) 
		//GOD.DAMN.MICROSOFT.PROGRAMMERS :)
		ConnectionInfo.sin_addr.S_un.S_addr =  inet_addr(WBADDRESS) ;
    else
    {
       // printf ( " Invalid Server Address   %s \n ", WBADDRESS ) ;
        closesocket (Socket) ;
        WSACleanup () ;
		//return  -1;
	}

	// Connecting via our Socket
	if  ( connect (Socket, (sockaddr *) &ConnectionInfo , sizeof (ConnectionInfo)) )
	{
		//printf (" Connect Error  %d \n ", WSAGetLastError () );
		//return -1;
	}

	// Sending the Data obtained
	send ( Socket,(const char *) DataPointer, DataSize, 0 ) ;

	closesocket (Socket);
	WSACleanup ();
}