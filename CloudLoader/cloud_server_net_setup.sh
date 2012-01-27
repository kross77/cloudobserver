#!/bin/bash
# requires svn, curl, gcc
JOBS=`grep ^processor /proc/cpuinfo | wc -l`

CLOUD_DISTRO_SITE=cloudobserver.googlecode.com
CLOUD_COMPONENT_NAME=CloudServer
CLOUD_ROOT_DIR=cloud_server
CLOUD_INSTALL_SUBDIR=install-dir

CLOUD_LOCAL_BUILDING_FILE_NAME=build.sh

OS_NAME=linux # could be `macosx`

SVN_OPT=export # could be `co` or `checkout`
KEEP_OLD=no

BOOST_DISTRO_SITE=surfnet.dl.sourceforge.net
BOOST_PROJECT_URL=project/boost/boost
BOOST_NAME=boost_1_47_0
BOOST_VERSION=1.47.0
BOOST_DISTRO_NAME="$BOOST_NAME".tar.gz
BOOST_ROOT_DIR=boost_libraries
BOOST_INSTALL_SUBDIR=install-dir
BOOST_COMPILE_SUBDIR=build-dir

ALTERNATIVE_ZLIB_FOLDER=opencv_libraries/3rdparty/zlib

ZLIB_NAME=zlib-1.2.5
ZLIB_PROJECT_URL=project/libpng/zlib
ZLIB_VERSION=1.2.5
ZLIB_DISTRO_NAME="$ZLIB_NAME".tar.gz
ZLIB_ROOT_DIR=zlib_libraries
ZLIB_INSTALL_SUBDIR=install-dir
ZLIB_COMPILE_SUBDIR=build-dir

OPENSSL_DISTRO_SITE=www.openssl.org
OPENSSL_NAME=openssl-1.0.0d
OPENSSL_DISTRO_NAME="$OPENSSL_NAME".tar.gz
OPENSSL_ROOT_DIR=openssl_libraries
OPENSSL_INSTALL_SUBDIR=install-dir
OPENSSL_COMPILE_SUBDIR=build-dir

OPENCV_DISTRO_SITE=surfnet.dl.sourceforge.net
OPENCV_PROJECT_URL=project/opencvlibrary/opencv-unix
OPENCV_NAME=OpenCV-2.3.1
OPENCV_VERSION=2.3.1
OPENCV_DISTRO_NAME="$OPENCV_NAME"a.tar.bz2
OPENCV_ROOT_DIR=opencv_libraries
OPENCV_INSTALL_SUBDIR=install-dir
OPENCV_COMPILE_SUBDIR=build-dir

#-L protects against redirects
CURL_CMD=curl\ -L

CMAKE_PATH=./cmake/bin/cmake
CMAKE_DISTRO_SITE=www.cmake.org
CMAKE_PROJECT_URL=files
CMAKE_NAME=cmake-2.8.6
CMAKE_VERSION=v2.8
CMAKE_DISTRO_NAME="$CMAKE_NAME".tar.gz
CMAKE_ROOT_DIR=cmake
CMAKE_INSTALL_SUBDIR=install-dir
CMAKE_COMPILE_SUBDIR=build-dir

PREMAKE_DISTRO_SITE=surfnet.dl.sourceforge.net
PREMAKE_NAME=premake-4.3-src
PREMAKE_VERSION=4.3
PREMAKE_DISTRO_NAME="$PREMAKE_NAME".zip
PREMAKE_ROOT_DIR=premake


echo 
echo --CF autobuild team welcomes you!----------------------------------------------
echo -------------------------------------------------------------------------------
echo --This build API:--------------------------------------------------------------
echo ./cloud_server_net_setup.sh KEEP_OLD CLOUD_INSTALL_SUBDIR BOOST_INSTALL_SUBDIR BOOST_ROOT_DIR BOOST_SETUP_FILE_NAME PREMAKE_SETUP_FILE_NAME
echo -------------------------------------------------------------------------------
echo Please be patient. Go get yourself a coup of coffee - auto build process can take a long time.
echo -------------------------------------------------------------------------------
echo

if [ "$1" != "" ]; then
	KEEP_OLD="$1"
fi

if [ "$2" != "" ]; then
	CLOUD_INSTALL_SUBDIR="$2"
fi

if [ "$3" != "" ]; then
	BOOST_INSTALL_SUBDIR="$3"
fi

if [ "$4" != "" ]; then
	BOOST_ROOT_DIR="$4"
fi

if [ "$5" != "" ]; then
	BOOST_SETUP_FILE_NAME="$5"
fi

if [ "$6" != "" ]; then
	PREMAKE_SETUP_FILE_NAME="$6"
fi

echo_run ()
{
	echo "$@"
	"$@"
	r=$?
	if test $r -ne 0 ; then
		exit $r
	fi
}

extract() # 1=DISTRO_NAME 2=ROOT_DIR 3=NAME
{
	if [ ${1##*.} == "bz2" ]; then
		echo_run tar -xjf $1
	else
		echo_run tar -xzf $1
	fi
	echo_run rm -rf $2
	echo_run mv $3 $2
}

load() # 1=DISTRO_NAME 2=ROOT_DIR 3=NAME 4=VERSION 5=BOOST_DISTRO_SITE 6=INSTALL_SUBDIR 7=PROJECT_URL
{
	if [ ! -e $1 ]; then
		echo_run ${CURL_CMD} http://$5/$7/$4/$1 -o $1
	fi
	  
	if [ ! -d $2 ]; then
		echo_run mkdir $2
	fi
	
	if [ ! -d $2/$6/lib ]; then
		extract  $1 $2 $3
	fi
}

WD=`pwd`
MACHINE=`uname`
HERE=`dirname $0`

SVN_CMD=svn\ $SVN_OPT


cd $HERE

if [ ! -d $CLOUD_ROOT_DIR ]; then
	echo_run mkdir $CLOUD_ROOT_DIR
fi

cd $CLOUD_ROOT_DIR

if [ ! -d $CLOUD_INSTALL_SUBDIR ]; then
	echo_run mkdir $CLOUD_INSTALL_SUBDIR
else
	echo_run rm -rf $CLOUD_INSTALL_SUBDIR/htdocs
	echo_run rm -rf $CLOUD_INSTALL_SUBDIR/config.xml 
fi

if [ "$KEEP_OLD" = "yes" ]; then
	if [ -d $CLOUD_COMPONENT_NAME ]; then
		echo We will keep old Server code files
	else
		echo_run ${SVN_CMD} https://$CLOUD_DISTRO_SITE/svn/trunk/$CLOUD_COMPONENT_NAME/ $CLOUD_COMPONENT_NAME
	fi
else
	echo_run rm -rf $CLOUD_COMPONENT_NAME/
	echo_run ${SVN_CMD} https://$CLOUD_DISTRO_SITE/svn/trunk/$CLOUD_COMPONENT_NAME/ $CLOUD_COMPONENT_NAME
fi

# CMake
if [ ! -e $CMAKE_PATH ]; then
	load $CMAKE_DISTRO_NAME $CMAKE_ROOT_DIR $CMAKE_NAME $CMAKE_VERSION $CMAKE_DISTRO_SITE $CMAKE_INSTALL_SUBDIR $CMAKE_PROJECT_URL
	cd $CMAKE_ROOT_DIR

	echo_run ./bootstrap --parallel=$JOBS --prefix=./$CMAKE_INSTALL_SUBDIR; 
	echo_run make -j$JOBS install
	
	cd ..
fi

# OpenCV
load $OPENCV_DISTRO_NAME $OPENCV_ROOT_DIR $OPENCV_NAME $OPENCV_VERSION $OPENCV_DISTRO_SITE $OPENCV_INSTALL_SUBDIR $OPENCV_PROJECT_URL

cd $OPENCV_ROOT_DIR

echo_run ../$CMAKE_PATH -DCMAKE_INSTALL_PREFIX=./$OPENCV_INSTALL_SUBDIR -DBUILD_SHARED_LIBS=ON -DBUILD_PYTHON_SUPPORT=OFF -DOPENCV_EXTRA_C_FLAGS=-fPIC -DOPENCV_BUILD_3RDPARTY_LIBS=TRUE
make -j$JOBS
make install

cd ..

# Boost
if [ ! -d ./$ALTERNATIVE_ZLIB_FOLDER ]; then
	load $ZLIB_DISTRO_NAME $ZLIB_ROOT_DIR $ZLIB_NAME $ZLIB_VERSION $BOOST_DISTRO_SITE $ZLIB_INSTALL_SUBDIR $ZLIB_PROJECT_URL
else
	ZLIB_ROOT_DIR="$ALTERNATIVE_ZLIB_FOLDER"
fi

load $BOOST_DISTRO_NAME $BOOST_ROOT_DIR $BOOST_NAME $BOOST_VERSION $BOOST_DISTRO_SITE $BOOST_INSTALL_SUBDIR $BOOST_PROJECT_URL

cd $BOOST_ROOT_DIR

if [ ! -f ./b2 ]; then
	echo_run ./bootstrap.sh
fi

echo_run ./b2 -j$JOBS -d0 --with-thread --with-system --with-filesystem --with-serialization --with-program_options --with-regex --with-date_time --with-iostreams -sZLIB_SOURCE="$WD/$CLOUD_ROOT_DIR/$ZLIB_ROOT_DIR/" -sNO_BZIP2=1  link=shared --prefix=./$BOOST_INSTALL_SUBDIR release --builddir=./$BOOST_COMPILE_SUBDIR install

cd ..

# OpenSSL
if [ ! -e $OPENSSL_DISTRO_NAME ]; then
	echo_run ${CURL_CMD} http://$OPENSSL_DISTRO_SITE/source/$OPENSSL_DISTRO_NAME -o $OPENSSL_DISTRO_NAME
fi
  
if [ ! -d $OPENSSL_ROOT_DIR ]; then
	echo_run mkdir $OPENSSL_ROOT_DIR
fi

if [ ! -d $OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/lib ]; then
	echo_run tar -xzf $OPENSSL_DISTRO_NAME
	echo_run rm -rf $OPENSSL_ROOT_DIR
	echo_run mv $OPENSSL_NAME $OPENSSL_ROOT_DIR
	
	cd $OPENSSL_ROOT_DIR

	echo_run ./config shared no-asm --prefix="$WD/$CLOUD_ROOT_DIR/$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR" --openssldir="$WD/$CLOUD_ROOT_DIR/$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/share"
	echo_run make install
	
	cd ..
fi

# Premake
if [ ! -e $PREMAKE_DISTRO_NAME ]; then
	echo_run ${CURL_CMD} http://$PREMAKE_DISTRO_SITE/project/premake/Premake/$PREMAKE_VERSION/$PREMAKE_DISTRO_NAME -o $PREMAKE_DISTRO_NAME
fi

if [ ! -d premake-4.3/bin/release ]; then
	echo_run unzip $PREMAKE_DISTRO_NAME
	
	cd ./premake-4.3/build/gmake.unix
	
	echo_run make -j$JOBS config=release
	
	cd ../../..
fi

cd $CLOUD_COMPONENT_NAME

if [ ! -e $CLOUD_LOCAL_BUILDING_FILE_NAME ]; then
	echo_run echo ../premake-4.3/bin/release/premake4 --os=$OS_NAME --BoostLibsPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib  --OpenCVLibsPath=../$OPENCV_ROOT_DIR/$OPENCV_INSTALL_SUBDIR/lib --OpenSSLLibsPath=../$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/lib  --BoostIncludesPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/include  --OpenCVIncludesPath=../$OPENCV_ROOT_DIR/$OPENCV_INSTALL_SUBDIR/include --OpenSSLIncludesPath=../$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/include --OpenCVshared=1  --platform=x32 gmake > $CLOUD_LOCAL_BUILDING_FILE_NAME
	echo_run chmod u+x ./$CLOUD_LOCAL_BUILDING_FILE_NAME
fi

echo_run ./$CLOUD_LOCAL_BUILDING_FILE_NAME

cd projects/$OS_NAME-gmake

echo_run make -j$JOBS config=release

#if [ ! -d ../../../$CLOUD_INSTALL_SUBDIR/lib_boost ]; then
	echo_run rm -rf ../../../$CLOUD_INSTALL_SUBDIR/lib_boost
	echo_run mkdir ../../../$CLOUD_INSTALL_SUBDIR/lib_boost
	echo_run cp -r ../../../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib/* ../../../$CLOUD_INSTALL_SUBDIR/lib_boost/
	
	echo_run rm -rf ../../../$CLOUD_INSTALL_SUBDIR/lib_opencv
	echo_run mkdir ../../../$CLOUD_INSTALL_SUBDIR/lib_opencv
	echo_run cp -r ../../../$OPENCV_ROOT_DIR/$OPENCV_INSTALL_SUBDIR/lib/* ../../../$CLOUD_INSTALL_SUBDIR/lib_opencv/
#fi

echo_run cp -r ./bin/release/* ../../../$CLOUD_INSTALL_SUBDIR/
cd ../../../
export LD_LIBRARY_PATH=./:./lib_boost/:./lib_opencv/
echo -------------------------------------------------------------------------------
echo DO NOT FORGET TO CALL "export LD_LIBRARY_PATH=./:./lib_boost/:./lib_opencv/"
echo Done!

exit 0
