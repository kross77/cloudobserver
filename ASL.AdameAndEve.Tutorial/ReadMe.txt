CloudGame cross-platform CF client:

-----------------------------------------------------------------------------------------------------------------------
Preparation instructions:
  - Download or build latest official distributions of library's and headers for next libs (if distributions are not presented you should compile library's manually on your own or call for help )
    - FFmpeg ( http://www.ffmpeg.org/ ) (we tested with version 0.6.1)
    - Boost C++ libraries ( http://www.boost.org/ )  (we tested with version 1.6.1)
    - OpenCV ( http://opencv.willowgarage.com/wiki/ ) (we tested with version 2.1)
    - OpenAL ( http://connect.creativelabs.com/openal/default.aspx ) (we tested with version 1.1)
	- Adobe Source Libraries (ASL) ( http://stlab.adobe.com/ ) (we tested with version 1.0.43)
	- Simple DirectMedia Layer (SDL) ( http://www.libsdl.org/ ) (we tested with version 1.2)
  - Be sure to have C99 compiler ( or for MSVC++ download headers fro here http://code.google.com/p/msinttypes/downloads/list )  (we tested with version "r26")

You can find instructions on FFmpeg, Boost C++ libraries, OpenCV and OpenAL in other `ReadMe` files and wiki on our project home site. You can find detailed, tested by us instructions on compilation of Adobe Source Libraries (ASL) here ( http://stackoverflow.com/questions/6397501/how-to-compile-asl-boost-based-adobe-c-gui-library-on-windows-7/6418957#6418957 ). As for now we use SDL from on-site provided builds ( http://www.libsdl.org/download-1.2.php )
On Windows:
This project is meant to be compiled and tested with VS2010.
Project has not yet been tested on Mac OS X nor on Linux.
-----------------------------------------------------------------------------------------------------------------------
How we see this CF subproject:
 	# 2 windows. One with SDL based game that shall be listening for simple keybord commands. One with ASL Adam and Eve based layout controls. 
	# Game shall use at least one OpenGL GLSL pixel shader with properties modifieble thrue ASL gui.
	# Rendered CloudGame frames shall be broadcastable to CF servers.  
-----------------------------------------------------------------------------------------------------------------------
To create a project for your compiler/IDE follow the instructions:
 - Download free, open-source project files generator Premake (see http://industriousone.com/premake/download for instructions)
 - Run Premake with command alike premake4  --help to see our project building file specific options (on windows you will need to fill paths for library's and headers)
 - Run Premake with command alike one we provide in example scripts
 - Project files would be placed into ./projects directory (relative to premake4.lua file)
 
-----------------------------------------------------------------------------------------------------------------------
CF team wishes you good luck!