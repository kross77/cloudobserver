#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "advapi32")
#pragma comment(lib, "winmm")
#pragma comment(lib, "ole32")
#pragma comment(lib, "oleaut32")

#ifdef _DEBUG
    #pragma comment(lib, "strmbasd")
#else
    #pragma comment(lib, "strmbase")
#endif




#include "stdafx.h"
#include "Filter.h"
#include "guids.h"
#include "filters.inc"

#define CreateComObject(clsid, iid, var) CoCreateInstance( clsid, NULL, CLSCTX_INPROC_SERVER, iid, (void **)&var);

STDAPI AMovieSetupRegisterServer( CLSID   clsServer, LPCWSTR szDescription, LPCWSTR szFileName, LPCWSTR szThreadingModel = L"Both", LPCWSTR szServerType     = L"InprocServer32" );
STDAPI AMovieSetupUnregisterServer( CLSID clsServer );


//STDAPI RegisterFilters( BOOL bRegister )
//{
//    HRESULT hr = NOERROR;
//    WCHAR achFileName[MAX_PATH];
//    char achTemp[MAX_PATH];
//    ASSERT(g_hInst != 0);
//
//    if( 0 == GetModuleFileNameA(g_hInst, achTemp, sizeof(achTemp))) 
//        return AmHresultFromWin32(GetLastError());
//
//    MultiByteToWideChar(CP_ACP, 0L, achTemp, lstrlenA(achTemp) + 1, 
//                       achFileName, NUMELMS(achFileName));
//  
//    hr = CoInitialize(0);
//    if(bRegister)
//    {
//        hr = AMovieSetupRegisterServer(CLSID_SourceSkelet, g_wszName, achFileName, L"Both", L"InprocServer32");
//    }
//
//    if( SUCCEEDED(hr) )
//    {
//        IFilterMapper2 *fm = 0;
//        hr = CreateComObject( CLSID_FilterMapper2, IID_IFilterMapper2, fm );
//        if( SUCCEEDED(hr) )
//        {
//            if(bRegister)
//            {
//                IMoniker *pMoniker = 0;
//                REGFILTER2 rf2;
//                rf2.dwVersion = 1;
//                rf2.dwMerit = MERIT_DO_NOT_USE;
//                rf2.cPins = 1;
//                rf2.rgPins = &AMSPinVCam;
//                hr = fm->RegisterFilter(CLSID_SourceSkelet, g_wszName, &pMoniker, &CLSID_VideoInputDeviceCategory, NULL, &rf2);
//            }
//            else
//            {
//                hr = fm->UnregisterFilter(&CLSID_VideoInputDeviceCategory, 0, CLSID_SourceSkelet);
//            }
//        }
//
//      // release interface
//      //
//      if(fm)
//          fm->Release();
//    }
//
//    if( SUCCEEDED(hr) && !bRegister )
//        hr = AMovieSetupUnregisterServer( CLSID_VirtualCam );
//
//    CoFreeUnusedLibraries();
//    CoUninitialize();
//    return hr;
//}

STDAPI DllRegisterServer()
{
    //return RegisterFilters(TRUE);
	return AMovieDllRegisterServer2(TRUE);
}

STDAPI DllUnregisterServer()
{
    //return RegisterFilters(FALSE);
	return AMovieDllRegisterServer2(FALSE);
}

extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  dwReason, LPVOID lpReserved)
{
	return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}

