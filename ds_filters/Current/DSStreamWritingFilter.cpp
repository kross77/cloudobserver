#include  "stdafx.h"
#include  "guids.h"
#include  "Filter.h"

// DON'T FORGET TO INCLUDE ws2_32.lib
#include  <winsock2.h>
#include  <windows.h>


#define  PORT      31123			// Server Connection Port
#define  WBADRESS  "127.0.0.1"		// Server Adress	


EXTERN_C const GUID CLSID_RendererSkelet;

CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CBaseRenderer(CLSID_RendererSkelet, tszName, punk, phr),
		m_InputPin(NAME("Input Pin"),this,&m_InterfaceLock,phr,L"Input")
{
}

CFilter::~CFilter()
{
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	ASSERT(phr);    
	CFilter *pNewObject = new CFilter(NAME("fv Add Graph To ROT Sample Filter"), punk, phr);
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

HRESULT CFilter::DoRenderSample (IMediaSample *pMediaSample)
{
	//we can get pointer to data is rendered
    //BYTE *buff;
	//pMediaSample->GetPointer(&buff);
	
	//we can get actual size of data is saved in buffer
	//pMediaSample->GetActualDataLength();
	
	return NOERROR;
}
////////////////////////////////////////NEW METHOD/////////////////
HRESULT CFilter::SendData (IMediaSample *pMediaSample)
{
	WSADATA         WSAInformation;
	SOCKET          Socket;
	BYTE            *DataPointer;
	sockaddr_in     ConnectionInfo;
	unsigned long	DataSize;       

	pMediaSample->GetPointer(&DataPointer);
	DataSize = pMediaSample->GetActualDataLength();

	
	// Getting Windows Socket Apllication started and error check 
	if ( WSAStartup ( 0x202, &WSAInformation ) )
    {
		printf ( " WSA Start Error  %d \n ", WSAGetLastError ( ) );
		return -1;
    }

	    
	// Creating the AF_INET family STREAM socket of TCP type 
	Socket = socket (AF_INET, SOCK_STREAM, 0);
    
	// Error Check
	if  ( Socket < 0 )       
	{
		printf (" Socket Error    %d \n ", WSAGetLastError () );
		return  -1;
	}
	
	// Filling ConnectionInfo fields
	ConnectionInfo.sin_family = AF_INET;
	ConnectionInfo.sin_port   = htons (PORT);

	// Converting IP-Adress format (from symbolic to network-styled)
    if ( inet_addr (SERVERADDR) != INADDR_NONE )    
		ConnectionInfo.sin_addr = inet_addr(SERVERADDR) ;
    else
    {
        printf ( " Invalid Server Address   %s \n ", SERVERADDR ) ;
        closesocket (Socket) ;
        WSACleanup () ;
		return  -1;
	}

	// Connecting via our Socket
	if  ( connect (Socket, (sockaddr *) &ConnectionInfo , sizeof (ConnectionInfo)) )
	{
		printf (" Connect Error  %d \n ", WSAGetLastError () );
		return -1;
	}

	// Sending the Data obtained
	send ( Socket, &DataPointer, DataSize, 0 ) ;

	closesocket (my_sock);
	WSACleanup ();

	return NOERROR;
}