CF cross-platform client:

-----------------------------------------------------------------------------------------------------------------------
Preparation instructions:
  - Download or build latest official distributions of library's and headers for next libs (if distributions are not presented you should compile library's manually on your own or call for help )
    - FFmpeg ( http://www.ffmpeg.org/ ) (we tested with version 0.9)
    - Boost C++ library's ( http://www.boost.org/ )  (we tested with version 1.48.0)
    - OpenCV ( http://opencv.willowgarage.com/wiki/ ) (we tested with version 2.3.1)
    - OpenAL ( http://connect.creativelabs.com/openal/default.aspx ) (we tested with version 1.13)
	- Tcl with Tk ( http://www.tcl.tk/ ) (we tested with version 8.5.10)
  - Be sure to have C99 compiler ( or for MSVC++ download headers fro here http://code.google.com/p/msinttypes/downloads/list )  (we tested with version "r26")

It is recommended to use the free ActiveTcl distribution from ActiveState ( http://www.activestate.com/activetcl ) instead of building Tcl and Tk on your own, version 8.5.9.2 works fine. On Windows you should install it into your "Program Files" or "Program Files (x86)" folder to make the premake script automatically find it there.

On Windows you should remember where to you downloaded library's and headers 
(or if you want to target only 32 bit platform and use visual studio 2008 get our Librarys-Windows-x32-vs08 archive and install it into your system as described in its own read me text file. in case of successful installation build file will not require anething from you but path to C99 compiler includes required for ffmpeg and provided here http://code.google.com/p/msinttypes/downloads/list ).

On Linux in most cases listed library's with there headers would install into /usr/** directory's. Please check if its true on your Linux like OS and if it is you should not think about external libs and headers disposition for our project.

On Mac OS X we recommend use of MacPorts  ( http://www.macports.org/ ) for library's installation. Notice - OpenAL is already installed on your system. Listed library's with there headers would probably be installed in /Library/Frameworks/**, /System/Library/Frameworks/** and /opt/local/** directory's. Please check if its true on your Mac OS and if it is you should not think about external libs and headers disposition for our project.

-----------------------------------------------------------------------------------------------------------------------
To create a project for your compiler/IDE follow the instructions:
 - Download free, open-source project files generator Premake (see http://industriousone.com/premake/download for instructions)
 - Run Premake with command alike premake4  --help to see our project building file specific options (on windows you will need to fill paths for library's and headers)
 - Run Premake with command alike one we provide in example scripts
 - Project files would be placed into ./projects directory (relative to premake4.lua file)
 
-----------------------------------------------------------------------------------------------------------------------
CF team wishes you good luck!