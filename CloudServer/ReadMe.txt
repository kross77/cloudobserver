Server - read-me:
-----------------------------------------------------------------------------------------------------------------------
Project idea is simple  -  server is a gateway\container that receives requests and redirect them into services (which shall be declared in configuration file and exist in form of shared libraries, which are metres of separate projects)
-----------------------------------------------------------------------------------------------------------------------
This project require and use:
    - Boost C++ library's ( http://www.boost.org/ )  (we tested with version 1.48.0)
	- Boost-Reflection ( we use it because of this tutorial http://boost-extension.redshoelace.com/docs/boost/extension/boost_extension/extension_reflection.html, we use latest revision 71517 http://svn.boost.org/svn/boost/sandbox/boost/reflection/, we adress it as part of boost 'boost/reflection/**' )
    - Boost.Process ( we use our costume modification of it that can be found in our SVN but we base it on  http://svn.boost.org/svn/boost/sandbox/SOC/2010/process/ r71393  )
    - Boost.Extension ( http://boost-extension.redshoelace.com/docs/boost/extension/index.html, we use costume modification of revision 50116 http://svn.boost.org/svn/boost/sandbox/boost/extension/, we address it as part of boost 'boost/extension/**' and store it in project svn - so just download this project svn - boost-extension will be in it)



On Windows you should remember where to you downloaded\compiled libraries and headers are.

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