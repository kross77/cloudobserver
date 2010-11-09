General Simple Video Transmitter solution

Solution is using crossplatform opensource librarys.

OpenCV
OpenAL
FFmpeg
Boost

Solution consists of 3 test projects - individual "hello world" like projects for each of OpenCV OpenAL FFmpeg libs, one for testing encoding into file and previewing
Solution contains project called as solution - main project, independent from others, can stream encoded live video+audio stream inside container onto cloud server via TCP connection.

There is LibsAndHeaders folder avaliable for project developers it contains  Install.ReadMe.txt file with instructions for installing all 4 libs, headers and so on contained in the folder distribution.

Worning! Developer - be aware not all boost libs are inclided into LibsAndHeaders folder! Only ones required for current build!  So be ready for compiler linker errors.

Worning! Developer - Do not belive to your own eyes!=) Good luck!
--------------------------------------------
Nearest Project Steps:
Enable Socket streaming into cloud core.
--------------------------------------------

In case you want to collect and instal all 4 libs onn your own here are shourt instructions on libs install

How to install lib into IDE  (	let us look at OpenCV as an example, we use .Lib files - not DLLs!)

1) Install OpenCV

Download the OpenCV 2.1.0 Windows installer from SourceForge - "OpenCV-2.1.0-win32-vs2008.exe".
Install it to a folder (without any spaces in it), say "C:\OpenCV2.1\". This article will refer to this path as $openCVDir
During installation, enable the option "Add OpenCV to the system PATH for all users".

2) Configure Visual Studio

Open VC++ Directories configuration: Tools > Options > Projects and Solutions > VC++ Directories
Choose "Show directories for: Include files"
Add "$openCVDir\include\opencv"
Choose "Show directories for: Library files"
Add "$openCVDir\lib"
Choose "Show directories for: Source files"
Add "$openCVDir\src\cv"
Add "$openCVDir\src\cvaux"
Add "$openCVDir\src\cxcore"
Add "$openCVDir\src\highgui"

3) Configure your Project

After you've created a project you'll need to add the OpenCV dependencies.

Open Project Properties: Project > %projectName% Properties...
Open Linker Input properties: Configuration Properties > Linker > Input
Open the "..." window to edit "Additional Dependencies" and on each line put:
"cv210.lib"
"cxcore210.lib"
"highgui210.lib"
And any other lib file necessary for your project
Your project should now build. If you get any errors try restarting Visual Studio and then doing a clean Rebuild.



FFMpeg Encoder


For FFMpeg Lib Includes we use method provided on [1] by adding FFmpeg as additional folder in sln (adding to project external libs path '../ffmpeg/lib/' and additional includes (in C++ tab) '../ffmpeg/include/')
For Boost install (in case you want to add it on your own see [2])
For TCP streaming with FFmpeg see [3]
For boost managed queue see [4]
Bibliography:

http://opencv.willowgarage.com/wiki/VisualC%2B%2B_VS2008
[1]http://unick-soft.ru/Articles.cgi?id=20
[2]http://www.qrck.ru/doc/libs/1_44_0/more/getting_started/windows.html
[3]http://lab.dyne.org/Ffmpeg/UseUrlProtocol
http://nashruddin.com/display-video-from-webcam-with-opencv.html
http://opensource.creative.com/pipermail/openal/2008-January/010877.html
[4]http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html

http://connect.creativelabs.com/openal/default.aspx
http://www.boost.org/


http://ffmpeg.arrozcru.org/autobuilds/