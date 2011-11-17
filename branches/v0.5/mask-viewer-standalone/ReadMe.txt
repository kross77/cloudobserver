MaskViewer - read-me:
-----------------------------------------------------------------------------------------------------------------------
Project idea is simple  -  open .mask file, find borders of each cluster, render in browser readable format such as: (rastr) JPEG, PNG; (vector) SVG.
-----------------------------------------------------------------------------------------------------------------------
This project require and use:
    - Boost C++ library's ( http://www.boost.org/ )  (we tested with version 1.4.7)
	- OpenCV C++ library ( http://opencv.willowgarage.com/wiki/ ) (we tested with version 2.3)

On Windows you should remember where to you downloaded\compiled libraries and headers.

On Linux in most cases listed library's with there headers would install into /usr/** directory's. Please check if its true on your Linux like OS and if it is you should not think about external libs and headers disposition for our project.

On Mac OS X we recommend use of MacPorts  ( http://www.macports.org/ ) for library's installation. Listed library's with there headers would probably be installed in /Library/Frameworks/**, /System/Library/Frameworks/** and /opt/local/** directory's. Please check if its true on your Mac OS and if it is you should not think about external libs and headers disposition for our project.

-----------------------------------------------------------------------------------------------------------------------
To create a project for your compiler/IDE follow the instructions:
 - Download free, open-source project files generator Premake (see http://industriousone.com/premake/download for instructions)
 - Run Premake with command alike premake4  --help to see our project building file specific options (on windows you will need to fill paths for library's and headers)
 - Run Premake with command alike one we provide in example scripts
 - Project files would be placed into ./projects directory (relative to premake4.lua file)
 
-----------------------------------------------------------------------------------------------------------------------
CF team wishes you good luck!