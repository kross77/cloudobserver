#include "list.h"

CamerasListNamespace::CamerasList::CamerasList(void)
{
}

CamerasListNamespace::CamerasList::~CamerasList(void)
{
}

int CamerasListNamespace::CamerasList::SelectFromList()
{
	
	int i = 0;
	int selectedIndex;
	#ifdef MAC
	std::cout << std::endl << "Let us select video device." << std::endl << "Available capture devices are:" << std::endl;
	
	SeqGrabComponent seqGrabber = NULL;
	SGDeviceList deviceList = NULL;
	
	// Find and open a sequence grabber
	ComponentDescription theDesc;
	theDesc.componentType           = SeqGrabComponentType;
	theDesc.componentSubType        = 0L;
	theDesc.componentManufacturer   = 'appl';
	theDesc.componentFlags          = 0L;
	theDesc.componentFlagsMask      = 0L;   
	Component sgCompID = FindNextComponent(NULL, &theDesc);
	if (sgCompID != 0) {
		seqGrabber = OpenComponent(sgCompID);
		if (seqGrabber)
		{
			ComponentResult result = SGInitialize(seqGrabber);
			if (result == noErr)
			{
				// Get a video channel
				SGChannel videoChannel;
				result = SGNewChannel(seqGrabber, VideoMediaType, &videoChannel);
				if (result == noErr)
				{
					// build a device list
					SGGetChannelDeviceList(videoChannel, sgDeviceListDontCheckAvailability | sgDeviceListIncludeInputs, &deviceList);
				} else {
					std::cout << "Couldn't create video channel - please connect a video device and try again." << std::endl;
					return 999;
				}
				SGDisposeChannel(seqGrabber, videoChannel);
			} else {
				std::cout << "SG call failed." << std::endl;
				return 999;
			}
		} else {
			std::cout << "FindNextComponent failed." << std::endl;
			return 999;
		}
	} else {
		std::cout << "FindNextComponent failed." << std::endl;
		return 999;
	}
	
    if (deviceList)
    {
        for (int theDeviceIndex = 0; theDeviceIndex != (*deviceList)->count; ++theDeviceIndex)
        {
			SGDeviceName theDeviceEntry = (*deviceList)->entry[theDeviceIndex];
            std::cout << i << ".1. " <<  theDeviceEntry.name << std::endl; 
            // name of device is a pstring in theDeviceEntry.name
			
			SGDeviceInputList theInputs = theDeviceEntry.inputs;
            if (theInputs != NULL)
            {
                for (int theInputIndex = 0; theInputIndex != (*theInputs)->count; ++theInputIndex)
                {
                    SGDeviceInputName theInput = (*theInputs)->entry[theInputIndex];
                    std::cout << i << ".2. " << theInput.name << std::endl;       
                    // name of input is a pstring in theInput.name
                }
            }
			i++;
        }
    }
	
	SGDisposeDeviceList(seqGrabber, deviceList);
	SGRelease(seqGrabber);
	#elif defined LIN
	int fd;
cout << endl << "Let us select video device." << endl << "Available capture devices are:" << endl;

ostringstream videoDevice;
videoDevice << "/dev/video" << i;

while ((fd = open(videoDevice.str().c_str(), O_RDONLY)) != -1)
{
	struct v4l2_capability capability;
	memset(&capability, 0, sizeof(capability));
	if (-1 == ioctl(fd, VIDIOC_QUERYCAP, &capability)) {}
	cout << i << ". " << capability.card << endl;
	close(fd);

	i++;
	videoDevice.str("");
	videoDevice << "/dev/video" << i;
}
	#elif defined WIN
				CoInitialize(NULL);
		IEnumMoniker *pEnum;
	printf("\nLet us select video device\n");
	printf("Available Capture Devices are:\n");
	HRESULT hr;
	hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
	if (SUCCEEDED(hr))
	{
		IMoniker *pMoniker = NULL;
		
		while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
		{
			IPropertyBag *pPropBag;
			HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
			if (FAILED(hr))
			{
				pMoniker->Release();
				continue;  
			} 

			VARIANT var;
			VariantInit(&var);

			// Get description or friendly name.
			hr = pPropBag->Read(L"Description", &var, 0);
			if (FAILED(hr))
			{
				hr = pPropBag->Read(L"FriendlyName", &var, 0);
			}
			if (SUCCEEDED(hr))
			{
				std::cout << i;
				printf(") %S\n", var.bstrVal);
				i++;
				VariantClear(&var); 
			}

			hr = pPropBag->Write(L"FriendlyName", &var);

			pPropBag->Release();
			pMoniker->Release();

		}
	}
	#else
		#error "unknown platform"
	#endif
	
	selectedIndex = 999;
	if (i <= 0)
	{
		std::cout << "No devices found." << std::endl;
		return 999;
	}
	else if (i == 1)
	{
		std::cout << "Default device will be used.\n" << std::endl;
		selectedIndex = 0;
	}
	else
	{
		while (selectedIndex > i - 1 || selectedIndex < 0)
		{
			try
			{
				std::string s;
				std::getline(std::cin, s, '\n');
				selectedIndex = boost::lexical_cast<int>(s);
			}
			catch(std::exception& e)
			{
				std::cout << "Please input index from 0 to " << i - 1 << std::endl;
				selectedIndex = 999;
			}
		}
	}
	return selectedIndex;
}


#ifdef WIN
HRESULT CamerasListNamespace::CamerasList::EnumerateDevices( REFGUID category, IEnumMoniker **ppEnum )
{
	// Create the System Device Enumerator.
	ICreateDevEnum *pDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,  
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

	if (SUCCEEDED(hr))
	{
		// Create an enumerator for the category.
		hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
		if (hr == S_FALSE)
		{
			hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
		}
		pDevEnum->Release();
	}
	return hr;
}
#endif