// http://stackoverflow.com/questions/4290834/how-to-get-a-list-of-video-capture-devices-web-cameras-on-linux-ubuntu-c/4290867#4290867
// http://www.cs.fsu.edu/~baker/devices/lxr/http/source/xawtv-3.95/console/v4l-info.c#L111

#include <iostream>
#include <sstream>
#include <string.h>
#include <QuickTime/QuickTime.h>
//#include <boost/lexical_cast.hpp>

using namespace std;

int main()
{
	
	int i = 0;
	int selectedIndex;

	cout << endl << "Let us select video device." << endl << "Available capture devices are:" << endl;
	
	SGDeviceList deviceList;
	
	// Find and open a sequence grabber
	ComponentDescription theDesc;
	theDesc.componentType           = SeqGrabComponentType;
	theDesc.componentSubType        = 0L;
	theDesc.componentManufacturer   = 'appl';
	theDesc.componentFlags          = 0L;
	theDesc.componentFlagsMask      = 0L;   
	Component sgCompID = FindNextComponent(NULL, &theDesc);
	if (sgCompID != 0) {
		ComponentInstance seqGrabber = OpenComponent(sgCompID);
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
					/* build a device list */
					SGGetChannelDeviceList(videoChannel, sgDeviceListDontCheckAvailability | sgDeviceListIncludeInputs, &deviceList);
				} else {
					cout << "Couldn't create video channel - please connect a video device and try again.";
					return 999;
				}
			} else {
				cout << "SG call failed.";
				return 999;
			}
		} else {
			cout << "FindNextComponent failed.";
			return 999;
		}
	} else {
		cout << "FindNextComponent failed.";
		return 999;
	}

    if (deviceList)
    {
        for (int theDeviceIndex = 0; theDeviceIndex != (*deviceList)->count; ++theDeviceIndex)
        {
			SGDeviceName theDeviceEntry = (*deviceList)->entry[theDeviceIndex];
            cout << i << ".1. " <<  theDeviceEntry.name << endl; 
            // name of device is a pstring in theDeviceEntry.name
			
			SGDeviceInputList theInputs = theDeviceEntry.inputs;
            if (theInputs != NULL)
            {
                for (int theInputIndex = 0; theInputIndex != (*theInputs)->count; ++theInputIndex)
                {
                    SGDeviceInputName theInput = (*theInputs)->entry[theInputIndex];
                    cout << i << ".2. " << theInput.name << endl;       
                    // name of input is a pstring in theInput.name
                }
            }
			i++;
        }
    }
	
	selectedIndex = 999;
	if (i <= 0)
	{
		cout << "No devices found." << endl;
		return 999;
	}
	else if (i == 1)
	{
		cout << "Default device will be used.\n" << endl;
		selectedIndex = 0;
	}
	else
	{
		while (selectedIndex > i - 1 || selectedIndex < 0)
		{
			try
			{
				cin >> selectedIndex;
				//string s;
				//getline(cin, s, '\n');
				//selectedIndex = boost::lexical_cast<int>(s);
			}
			catch(std::exception& e)
			{
				cout << "Please input index from 0 to " << i - 1 << endl;
				selectedIndex = 999;
			}
		}
	}
	return selectedIndex;
}
