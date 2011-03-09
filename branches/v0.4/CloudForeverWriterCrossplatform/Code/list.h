#include <iostream>
#include <cstring>
#include <boost/lexical_cast.hpp>
#ifdef WIN
#pragma comment(lib, "strmiids")
#include <windows.h>
#include <dshow.h>
#elif defined LIN
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#elif defined MAC
#include <QuickTime/QuickTime.h>
#else
#error "unknown platform"
#endif



namespace CamerasListNamespace
{
	class CamerasList
	{
	public:
		CamerasList(void);
		~CamerasList(void);	
		int SelectFromList();
		
	#ifdef WIN
	private: HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	#endif
		
	};
}

