CF cross-platform writer:

-----------------------------------------------------------------------------------------------------------------------
Preparation instructions:
  - Download or build latest official distributions of library's and headers for next libs (if distributions are not presented you should compile library's manually on your own or call for help )
    - FFmpeg ( http://www.ffmpeg.org/ ) (we tested with version 0.6.1)
    - Boost C++ library's ( http://www.boost.org/ )  (we tested with version 0.6.1)
    - OpenCV ( http://opencv.willowgarage.com/wiki/ ) (we tested with version 2.1)
    - OpenAL ( http://connect.creativelabs.com/openal/default.aspx ) (we tested with version 1.1)
  - Be sure to have C99 compiler ( or for MSVC++ download headers fro here http://code.google.com/p/msinttypes/downloads/list )  (we tested with version "r26")

On Windows you should remember where to you downloaded library's and headers.

On Linux in most cases listed library's with thare headers would install into /usr/** directory's. Please check if its true on your Linux like OS and if it is you should not think about external libs and headers disposition for our project.

On Mac OS X we recommend use of MacPorts  ( http://www.macports.org/ ) for library's installation. Notice - OpenAL is already installed on your system. Listed library's with there headers would probably be installed in /Library/Frameworks/**, /System/Libarary/Frameworks/** and /opt/local/** directory's. Please check if its true on your Mac OS and if it is you should not think about external libs and headers disposition for our project.

-----------------------------------------------------------------------------------------------------------------------
To create a project for your compiler/IDE follow the instructions:
 - Download free, open-source project files generator Premake (see http://industriousone.com/premake/download for instructions)
 - Run Premake with command alike premake4.exe  --file=build.lua --help to see our project building file specific options (on windows you will need to fill paths for library's and headers)
 - Run Premake with command alike one we provide in premake-vs2008-example.bat (on Linux and Mac OS X most options can be not used)
 - Project files would be placed into ./build dirctory (relative to build.lua file)
 
-----------------------------------------------------------------------------------------------------------------------
CF team wishes you good luck!