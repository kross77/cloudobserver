RAC - readme:

-----------------------------------------------------------------------------------------------------------------------
Preparation instructions:
  - Download or build latest official distributions of library's and headers for next libs (if distributions are not presented you should compile library's manually on your own or call for help )
    - Boost C++ library's ( http://www.boost.org/ )  (we tested with version 1.4.6)
    - Boost.Extension ( http://boost-extension.redshoelace.com/docs/boost/extension/index.html, we use latest revision 50116 http://svn.boost.org/svn/boost/sandbox/boost/extension/, we adress it as part of boost 'boost/extension/**' )
    - Boost.Process ( we use our costume modification of it that can be found in our SVN but we base it on  http://svn.boost.org/svn/boost/sandbox/SOC/2010/process/ r71393  )
    - SQLite (http://www.sqlite.org/cintro.html)
    -----------------------------------------------------------------------------------
    -----------------------------------------------------------------------------------
    Also we recommend you to have expirience in building from source next libs, we may require tham later:
    - FFmpeg ( http://www.ffmpeg.org/ ) (we tested with version 0.6.1)
    - OpenCV ( http://opencv.willowgarage.com/wiki/ ) (we tested with version 2.2)
    - OpenAL ( http://connect.creativelabs.com/openal/default.aspx ) (we tested with version 1.13)
  - Be sure to have C99 compiler ( or for MSVC++ download headers fro here http://code.google.com/p/msinttypes/downloads/list )  (we tested with version "r26")

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