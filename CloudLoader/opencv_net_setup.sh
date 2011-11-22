#!/bin/bash
#/OpenCV-2.3.1a.tar.bz2
OPENCV_DISTRO_SITE=surfnet.dl.sourceforge.net
OPENCV_PROJECT_URL=project/opencvlibrary/opencv-unix
OPENCV_NAME=OpenCV-2.3.1a
OPENCV_VERSION=2.3.1
OPENCV_DISTRO_NAME="$OPENCV_NAME".tar.bz2
OPENCV_ROOT_DIR=opencv_libraries
OPENCV_INSTALL_SUBDIR=install-dir
OPENCV_COMPILE_SUBDIR=build-dir

CMAKE_SETUP_FILE_WEB_PATH=http://cloudobserver.googlecode.com/svn-history/r1597/trunk/CloudLoader/cmake_net_setup.sh
CMAKE_PATH=./cmake/bin/cmake
CMAKE_SETUP_FILE_NAME=cmake_net_setup.sh

KEEP_OLD="true"

echo API: ./opencv_net_setup.sh  1=CMAKE_PATH 2=CMAKE_SETUP_FILE_WEB_PATH 3=CMAKE_SETUP_FILE_NAME
echo Warning: This script shall be executed from a path that contains no spaces or non English latters!

#-L protects against redirects
CURL_CMD=curl\ -L 

# Run a command, and echo before doing so. Also checks the exit
# status and quits if there was an error.
#
# WARNING : Does *not* work when the command uses the redirection operator (>)
#
echo_run ()
{
	echo "$@"
	"$@"
	r=$?
	if test $r -ne 0 ; then
		exit $r
	fi
}


if [ "$1" != "" ]; then
	CMAKE_PATH="$2"
fi
if [ "$2" != ""]; then
	CMAKE_SETUP_FILE_WEB_PATH="$2"
fi
if [ "$3" != ""]; then
	CMAKE_SETUP_FILE_NAME="$3"
fi

if [ ! -e $CMAKE_PATH ]; then
	echo_run wget $CMAKE_SETUP_FILE_WEB_PATH
	echo_run chmod u+x ./$CMAKE_SETUP_FILE_NAME
	echo_run ./$CMAKE_SETUP_FILE_NAME
fi

extract() # 1=DISTRO_NAME 2=ROOT_DIR 3=NAME
{
	echo_run tar -xvjf ./$1 -C ./$2
	#echo_run rm -rf $2
	#echo_run mv $3 
}

load() # 1=DISTRO_NAME 2=ROOT_DIR 3=NAME 4=VERSION 5=BOOST_DISTRO_SITE 6=INSTALL_SUBDIR 7=PROJECT_URL
{
	if [ ! -e $1 ]; then
		# get boost
		echo_run ${CURL_CMD} http://$5/$7/$4/$1 -o $1
	fi
	  
	if [ ! -d $2 ]; then
		echo_run mkdir $2
	fi
	
	# move the boost distro into place
	if [ ! -d $2/$6/lib ]; then
		extract  $1 $2 $3
	else
		if [ ! KEEP_OLD=="true" ]; then
			extract $1 $2 $3
		fi
	fi
}


WD=`pwd`
MACHINE=`uname`
HERE=`dirname $0`

cd $HERE

load $OPENCV_DISTRO_NAME $OPENCV_ROOT_DIR $OPENCV_NAME $OPENCV_VERSION $OPENCV_DISTRO_SITE $OPENCV_INSTALL_SUBDIR $OPENCV_PROJECT_URL

cd $OPENCV_ROOT_DIR
if [ -d ./OpenCV-2.3.1 ]; then
 mv -f ./OpenCV-2.3.1/* `pwd`
 rm -rf OpenCV-2.3.1
fi

echo_run ../$CMAKE_PATH -DCMAKE_INSTALL_PREFIX=./$OPENCV_INSTALL_SUBDIR -DBUILD_WITH_STATIC_CRT=ON -DBUILD_SHARED_LIBS=OFF -DBUILD_PYTHON_SUPPORT=OFF -DOPENCV_EXTRA_C_FLAGS=-fPIC -DOPENCV_BUILD_3RDPARTY_LIBS=TRUE
make
make install
echo Done!

exit 0;