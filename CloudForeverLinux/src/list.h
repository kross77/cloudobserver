

#if !defined(_WIN32)
#include <sstream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#endif
#include <iostream>
class CamerasList
{
public:
	CamerasList(void);
	~CamerasList(void);

	int SelectFromList();
};
