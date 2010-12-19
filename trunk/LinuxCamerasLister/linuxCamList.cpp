//  оригинал в котором есть как смотреть на такие свойства как  depth,  size, Maximum size, Minimum size. http://stackoverflow.com/questions/4290834/how-to-get-a-list-of-video-capture-devices-web-cameras-on-linux-ubuntu-c/4290867#4290867 
//также стоит обратить внимание на http://www.cs.fsu.edu/~baker/devices/lxr/http/source/xawtv-3.95/console/v4l-info.c#L111 если этот код не будет рабочим ну савсем=)

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev.h>
#include <boost/lexical_cast.hpp>

  #include "videodev.h"
  #include "videodev2.h"
  
 #include "struct-dump.h"
  #include "struct-v4l.h"
  #include "struct-v4l2.h"

using namespace std;
int main(){
    int fd;
    int i = 0;
    int SelectedIndex;
    string devIndexName;
    	 int tab = 5;
	printf("\nLet us select video device\n");
	printf("Available Capture Devices are:\n");
	
	devIndexName = "/dev/video";
	devIndexName += i;
  
	
	
    while((fd = open(devIndexName.c_str(), O_RDONLY)) != -1){
    	struct v4l2_capability  capability;

         memset(&capability,0,sizeof(capability));
        if (-1 == ioctl(fd,VIDIOC_QUERYCAP,&capability)){}
       // попробуем вывести имя амеры
       cout << capability.card << endl;  
    devIndexName = "/dev/video";
	devIndexName += i;
	i++;   
	//close(fd);  // незнаю может тут енто стоит использовать для чистоты кода=)
    }
    
    
    
   SelectedIndex = 999;
	if (i <= 0)
	{
		cout <<"No devices found. \n " << endl;
	return 999;

	}else if(i == 1){
			cout <<"Default device will be used\n" << std::endl;
			SelectedIndex = 0;
		}else{
		while(SelectedIndex > i-1 || SelectedIndex < 0)
		{
			try{		
			std::string s;
			std::getline( cin, s, '\n' );
			SelectedIndex =  boost::lexical_cast<int>(s);
			}
			catch(std::exception& e){
				std::cout <<"please input index from 0 to " << i-1 << std::endl;
				SelectedIndex = 999;
			}
		}}
		
	}

    return SelectedIndex;
}