// This is the main DLL file.

#include "stdafx.h"
#include "guids.h"
#include "FilterTransform.h"

// DON'T FORGET TO INCLUDE ws2_32.lib
#include  <winsock.h>
#include  <windows.h>
#include  <stdio.h>

#define  PORT      31123			// Server Connection Port
#define  WBADDRESS  "127.0.0.1"		// Server Adress (Work Block Address)	


EXTERN_C const GUID CLSID_TransformSkelet;

//CFilter::CFilter()
//{
//}
CFilter::CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr) :
    CTransInPlaceFilter(tszName, punk, CLSID_TransformSkelet, phr, true)
{
}
CFilter::~CFilter()
{
}

CUnknown * WINAPI CFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	//ASSERT(phr);    
	CFilter *pNewObject = new CFilter(NAME("fv Add Graph To ROT Sample Filter"), punk, phr);
    if (pNewObject == NULL) {
        if (phr)
            *phr = E_OUTOFMEMORY;
    }

    return pNewObject;
}


HRESULT CFilter::CheckInputType(const CMediaType* mtIn)
{
	return E_INVALIDARG;
}

STDMETHODIMP CFilter::JoinFilterGraph(IFilterGraph *pGraph, LPCWSTR pName)
{
	//DWORD dwRot;
	//CAutoLock cAutoLock(&m_fvLock);
	//AddToRot(pGraph,&dwRot);

	return CBaseFilter::JoinFilterGraph(pGraph,pName);
}

//HRESULT FilterTransform::AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister)
//{
//	HANDLE g_hEvent=CreateEvent(NULL,TRUE,FALSE,"fvAddToRotEvent001");
//	if (WaitForSingleObject(g_hEvent,0)==WAIT_OBJECT_0) 
//		return S_OK;
//	
//	SetEvent(g_hEvent);
//	
//	IMoniker * pMoniker;
//	IRunningObjectTable *pROT;
//	if (FAILED(GetRunningObjectTable(0, &pROT))) 
//	{
//		return E_FAIL;
//	}
//	WCHAR wsz[256];
//	
//	wsprintfW(wsz, L"FilterGraph %08x pid %08x", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());
//	HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
//	if (SUCCEEDED(hr))
//	{
//		hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, pMoniker, pdwRegister);
//		pMoniker->Release();
//	}
//	pROT->Release();
//	return hr;
//}


HRESULT CFilter::Transform(IMediaSample *pMediaSample)
{
	return NOERROR;
}

////////////////////////////////////////////////////
//////////////|  NEW METHOD IS HERE   |/////////////
////////////////////////////////////////////////////
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
    if ( inet_addr (WBADDRESS) != INADDR_NONE ) 
		//GOD.DAMN.MICROSOFT.PROGRAMMERS :)
		ConnectionInfo.sin_addr.S_un.S_addr =  inet_addr(WBADDRESS) ;
    else
    {
        printf ( " Invalid Server Address   %s \n ", WBADDRESS ) ;
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
	send ( Socket,(const char *) DataPointer, DataSize, 0 ) ;

	closesocket (Socket);
	WSACleanup ();

	return NOERROR;
}
