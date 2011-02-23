
#include <iostream>
#include <sstream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <boost/lexical_cast.hpp>

#include "../list.h"

using namespace std;

CamerasList::CamerasList(void)
{
}

CamerasList::~CamerasList(void)
{
}


int CamerasList::SelectFromList()
{
	int fd;
	int i =0;
	int selectedIndex;
	ostringstream videoDevice;
	videoDevice << "/dev/video" << i;

	cout << endl <<"Let us select video device."<< endl << "Available capture devices are:" << endl;


	while ((fd = open(videoDevice.str().c_str(), O_RDONLY)) != -1)
	{
		struct v4l2_capability capability;
		memset(&capability, 0, sizeof(capability));
		if (-1 == ioctl(fd, VIDIOC_QUERYCAP, &capability))
		{
			//error
		}
		cout << i << ". " << capability.card << endl;
		close(fd);
		i++;
		videoDevice.str("");
		videoDevice << "/dev/video" << i;
	}

	selectedIndex = 999;
	if (i <= 0)
	{
		cout << "No devices found." << endl;
		return 999;
	}
	//we have some cameras
	if (i == 1)
	{
		cout<< "Default device will be used.\n" << endl;
		selectedIndex = 0;
	}
	else
	{
		while (selectedIndex > i - 1 || selectedIndex < 0)
		{
			try
			{
				//cin >> selectedIndex;
				string s;
				getline(cin, s, '\n');
				selectedIndex = boost::lexical_cast<int>(s);
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

