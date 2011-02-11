 // http://stackoverflow.com/questions/4290834/how-to-get-a-list-of-video-capture-devices-web-cameras-on-linux-ubuntu-c/4290867#4290867
// http://www.cs.fsu.edu/~baker/devices/lxr/http/source/xawtv-3.95/console/v4l-info.c#L111

#include <iostream>
#include <sstream>
#include <string.h>
#include <quicktime.h>
//#include <boost/lexical_cast.hpp>

using namespace std;

int main()
{
	
	int i = 0;
	int selectedIndex;

	cout << endl << "Let us select video device." << endl << "Available capture devices are:" << endl;


  // first get a video channel from the sequence grabber

   ComponentDescription    theDesc;
   Component               sgCompID;
   ComponentResult         result;
   theDesc.componentType           = SeqGrabComponentType;
   theDesc.componentSubType        = 0L;
   theDesc.componentManufacturer   = 'appl';
   theDesc.componentFlags          = 0L;
   theDesc.componentFlagsMask      = 0L;   
   sgCompID = FindNextComponent (NULL, &theDesc);
   seqGrabber = OpenComponent (sgCompID);
   result = SGInitialize (seqGrabber);
   result = SGNewChannel (seqGrabber, VideoMediaType, &videoChannel);
   SGDeviceList  theDevices;
   SGGetChannelDeviceList(videoChannel, sgDeviceListDontCheckAvailability | sgDeviceListIncludeInputs, &theDevices);

    if (theDevices)
    {
        int theDeviceIndex;
        for (theDeviceIndex = 0; theDeviceIndex != (*theDevices)->count; ++theDeviceIndex)
        {
            SGDeviceName theDeviceEntry = (*theDevices)->entry[theDeviceIndex];
            cout << i << ".1. " <<  theDeviceEntry.name << endl; 
            // name of device is a pstring in theDeviceEntry.name

        SGDeviceInputList theInputs = theDeviceEntry.inputs;
            if (theInputs != NULL)
            {
                int theInputIndex;
                for ( theInputIndex = 0; theInputIndex != (*theInputs)->count; ++theInputIndex)
                {
                    SGDeviceInputName theInput = (*theInputs)->entry[theInputIndex];
                    cout << i << ".2. " << theInput.name << endl;       
                    // name of input is a pstring in theInput.name
                }
            }
        }       
    } // i++ we need to add...

	
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

