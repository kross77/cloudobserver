#!/bin/bash
# requires svn, curl, gcc
BOOST_VERSION=1.47.0
CMAKE_VERSION=2.8.6
OPENCV_VERSION=2.3.1
OPENSSL_VERSION=1.0.0d
PREMAKE_VERSION=4.3

WORKSPACE=cloud_server

JOBS=`grep ^processor /proc/cpuinfo | wc -l`

CLOUD_DISTRO_SITE=cloudobserver.googlecode.com
CLOUD_COMPONENT_NAME=CloudServer
CLOUD_INSTALL_SUBDIR=install-dir

CLOUD_LOCAL_BUILDING_FILE_NAME=build.sh

DOWNLOADS_DIR=downloads

OS_NAME=linux # could be `macosx`

KEEP_OLD=no
REBUILD_LIBRARIES=no

BOOST_DISTRO_SITE=surfnet.dl.sourceforge.net
BOOST_PROJECT_PATH=project/boost/boost/$BOOST_VERSION
BOOST_NAME=boost_${BOOST_VERSION//./_}
BOOST_DISTRO_NAME="$BOOST_NAME".tar.bz2
BOOST_ROOT_DIR=boost_libraries
BOOST_INSTALL_SUBDIR=install-dir
BOOST_COMPILE_SUBDIR=build-dir

ZLIB_ROOT_DIR=opencv_libraries/3rdparty/zlib

OPENSSL_DISTRO_SITE=www.openssl.org
OPENSSL_NAME=openssl-$OPENSSL_VERSION
OPENSSL_DISTRO_NAME="$OPENSSL_NAME".tar.gz
OPENSSL_PROJECT_PATH=source
OPENSSL_ROOT_DIR=openssl_libraries
OPENSSL_INSTALL_SUBDIR=install-dir
OPENSSL_COMPILE_SUBDIR=build-dir

OPENCV_DISTRO_SITE=surfnet.dl.sourceforge.net
OPENCV_PROJECT_PATH=project/opencvlibrary/opencv-unix/$OPENCV_VERSION
OPENCV_NAME=OpenCV-$OPENCV_VERSION
OPENCV_DISTRO_NAME="$OPENCV_NAME"a.tar.bz2
OPENCV_ROOT_DIR=opencv_libraries
OPENCV_INSTALL_SUBDIR=install-dir
OPENCV_COMPILE_SUBDIR=build-dir

CMAKE_DISTRO_SITE=www.cmake.org
CMAKE_PROJECT_PATH=files/v${CMAKE_VERSION%.*}
CMAKE_NAME=cmake-$CMAKE_VERSION
CMAKE_DISTRO_NAME="$CMAKE_NAME".tar.gz
CMAKE_ROOT_DIR=cmake
CMAKE_INSTALL_SUBDIR=install-dir
CMAKE_COMPILE_SUBDIR=build-dir

PREMAKE_DISTRO_SITE=surfnet.dl.sourceforge.net
PREMAKE_PROJECT_PATH=project/premake/Premake/$PREMAKE_VERSION
PREMAKE_NAME=premake-$PREMAKE_VERSION
PREMAKE_DISTRO_NAME="$PREMAKE_NAME"-src.zip
PREMAKE_ROOT_DIR=premake


echo 
echo --CF autobuild team welcomes you!----------------------------------------------
echo -------------------------------------------------------------------------------
echo --This build API:--------------------------------------------------------------
echo ./cloud_server_net_setup.sh KEEP_OLD REBUILD_LIBRARIES
echo -------------------------------------------------------------------------------
echo Please be patient. Go get yourself a coup of coffee - auto build process can take a long time.
echo -------------------------------------------------------------------------------
echo

if [ "$1" != "" ]; then
	KEEP_OLD="$1"
fi

if [ "$2" != "" ]; then
	REBUILD_LIBRARIES="$2"
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

load() # 1=DISTRO_NAME 2=ROOT_DIR 3=NAME 4=DISTRO_SITE 5=DISTRO_PATH
{
	if [ ! -e $DOWNLOADS_DIR/$1 ]; then
		echo_run curl -L http://$4/$5/$1 -o $DOWNLOADS_DIR/$1
	fi
	
	if [ ${1##*.} == "zip" ]; then
		echo_run unzip $DOWNLOADS_DIR/$1
	elif [ ${1##*.} == "bz2" ]; then
		echo_run tar -xjf $DOWNLOADS_DIR/$1
	else
		echo_run tar -xzf $DOWNLOADS_DIR/$1
	fi
	echo_run mv $3 $2
}

WD=`pwd`
MACHINE=`uname`
HERE=`dirname $0`

cd $HERE

if [ ! -d $WORKSPACE ]; then
	echo_run mkdir $WORKSPACE
fi

cd $WORKSPACE

if [ ! -d $DOWNLOADS_DIR ]; then
	echo_run mkdir $DOWNLOADS_DIR
fi

if [ "$REBUILD_LIBRARIES" = "yes" ]; then
	rm -rf $CMAKE_ROOT_DIR
	rm -rf $OPENCV_ROOT_DIR
	rm -rf $BOOST_ROOT_DIR
	rm -rf $OPENSSL_ROOT_DIR
	rm -rf $PREMAKE_ROOT_DIR
fi

# CMake
if [ ! -d $CMAKE_ROOT_DIR ]; then
	load $CMAKE_DISTRO_NAME $CMAKE_ROOT_DIR $CMAKE_NAME $CMAKE_DISTRO_SITE $CMAKE_PROJECT_PATH
	cd $CMAKE_ROOT_DIR

	echo_run ./bootstrap --parallel=$JOBS --prefix=./$CMAKE_INSTALL_SUBDIR; 
	echo_run make -j$JOBS install
	
	cd ..
fi

# OpenCV
if [ ! -d $OPENCV_ROOT_DIR ]; then
	load $OPENCV_DISTRO_NAME $OPENCV_ROOT_DIR $OPENCV_NAME $OPENCV_DISTRO_SITE $OPENCV_PROJECT_PATH

	cd $OPENCV_ROOT_DIR

	# Adding the following option:
	#   -DEXECUTABLE_OUTPUT_PATH=./$OPENCV_INSTALL_SUBDIR/bin
	# to the CMake call leads to an error during the build
	# with 'opencv_traincascade' executable not being created.
	# It seems like a bug in OpenCV CMake script.
	echo_run ../$CMAKE_ROOT_DIR/bin/cmake \
		-DBUILD_DOCS=OFF \
		-DBUILD_EXAMPLES=OFF \
		-DBUILD_NEW_PYTHON_SUPPORT=OFF \
		-DBUILD_PACKAGE=OFF \
		-DBUILD_SHARED_LIBS=OFF \
		-DBUILD_TESTS=OFF \
		-DBUILD_WITH_DEBUG_INFO=OFF \
		-DCMAKE_BACKWARDS_COMPATIBILITY=2.8.2 \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_CONFIGURATION_TYPES=Release \
		-DCMAKE_INSTALL_PREFIX=./$OPENCV_INSTALL_SUBDIR \
		-DCMAKE_VERBOSE=OFF \
		-DENABLE_PROFILING=OFF \
		-DENABLE_SOLUTION_FOLDERS=OFF \
		-DENABLE_SSE=OFF \
		-DENABLE_SSE2=OFF \
		-DENABLE_SSE3=OFF \
		-DENABLE_SSE41=OFF \
		-DENABLE_SSE42=OFF \
		-DENABLE_SSSE3=OFF \
		-DINSTALL_C_EXAMPLES=OFF \
		-DINSTALL_PYTHON_EXAMPLES=OFF \
		-DLIBRARY_OUTPUT_PATH=./$OPENCV_INSTALL_SUBDIR/lib \
		-DOPENCV_BUILD_3RDPARTY_LIBS=TRUE \
		-DOPENCV_CONFIG_FILE_INCLUDE_DIR=./ \
		-DOPENCV_EXTRA_C_FLAGS=-fPIC \
		-DOPENCV_EXTRA_C_FLAGS_DEBUG= \
		-DOPENCV_EXTRA_C_FLAGS_RELEASE= \
		-DOPENCV_EXTRA_EXE_LINKER_FLAGS= \
		-DOPENCV_EXTRA_EXE_LINKER_FLAGS_DEBUG= \
		-DOPENCV_EXTRA_EXE_LINKER_FLAGS_RELEASE= \
		-DOPENCV_WARNINGS_ARE_ERRORS=OFF \
		-DPYTHON_PACKAGES_PATH= \
		-DUSE_FAST_MATH=OFF \
		-DUSE_OMIT_FRAME_POINTER=OFF \
		-DUSE_PRECOMPILED_HEADERS=OFF \
		-DWITH_1394=OFF \
		-DWITH_CUDA=OFF \
		-DWITH_EIGEN=OFF \
		-DWITH_FFMPEG=OFF \
		-DWITH_GSTREAMER=OFF \
		-DWITH_GTK=OFF \
		-DWITH_IPP=OFF \
		-DWITH_JASPER=ON \
		-DWITH_JPEG=ON \
		-DWITH_OPENEXR=OFF \
		-DWITH_OPENNI=OFF \
		-DWITH_PNG=ON \
		-DWITH_PVAPI=OFF \
		-DWITH_QT=OFF \
		-DWITH_QT_OPENGL=OFF \
		-DWITH_TBB=OFF \
		-DWITH_TIFF=ON \
		-DWITH_UNICAP=OFF \
		-DWITH_V4L=OFF \
		-DWITH_XIMEA=OFF \
		-DWITH_XINE=OFF
	make -j$JOBS install

	echo_run cp $OPENCV_INSTALL_SUBDIR/share/OpenCV/3rdparty/lib/* $OPENCV_INSTALL_SUBDIR/lib

	cd ..
fi

# Boost
if [ ! -d $BOOST_ROOT_DIR ]; then
	load $BOOST_DISTRO_NAME $BOOST_ROOT_DIR $BOOST_NAME $BOOST_DISTRO_SITE $BOOST_PROJECT_PATH

	cd $BOOST_ROOT_DIR

	if [ ! -f ./b2 ]; then
		echo_run ./bootstrap.sh
	fi

	echo_run ./b2 -j$JOBS -d0 --with-thread --with-system --with-filesystem --with-serialization --with-program_options --with-regex --with-date_time --with-iostreams -sZLIB_SOURCE="$WD/$WORKSPACE/$ZLIB_ROOT_DIR/" -sNO_BZIP2=1 cflags=-fPIC cxxflags=-fPIC link=static --prefix=./$BOOST_INSTALL_SUBDIR release --builddir=./$BOOST_COMPILE_SUBDIR install

	cd ..
fi

# OpenSSL
if [ ! -d $OPENSSL_ROOT_DIR ]; then
	load $OPENSSL_DISTRO_NAME $OPENSSL_ROOT_DIR $OPENSSL_NAME $OPENSSL_DISTRO_SITE $OPENSSL_PROJECT_PATH
	
	cd $OPENSSL_ROOT_DIR

	echo_run ./config shared no-asm --prefix="$WD/$WORKSPACE/$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR" --openssldir="$WD/$WORKSPACE/$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/share"
	echo_run make install

	cd ..
fi

# Premake
if [ ! -d $PREMAKE_ROOT_DIR ]; then
	load $PREMAKE_DISTRO_NAME $PREMAKE_ROOT_DIR $PREMAKE_NAME $PREMAKE_DISTRO_SITE $PREMAKE_PROJECT_PATH
	
	cd $PREMAKE_ROOT_DIR/build/gmake.unix
	
	echo_run make -j$JOBS config=release
	
	cd ../../..
fi

# CloudServer
if [ "$KEEP_OLD" = "no" -o ! -d $CLOUD_COMPONENT_NAME ]; then
	echo_run rm -rf $CLOUD_COMPONENT_NAME/
	echo_run svn checkout https://$CLOUD_DISTRO_SITE/svn/trunk/$CLOUD_COMPONENT_NAME/ $CLOUD_COMPONENT_NAME
fi

cd $CLOUD_COMPONENT_NAME

if [ ! -e $CLOUD_LOCAL_BUILDING_FILE_NAME ]; then
	echo_run echo ../$PREMAKE_ROOT_DIR/bin/release/premake4 --os=$OS_NAME --BoostLibsPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib  --OpenCVLibsPath=../$OPENCV_ROOT_DIR/$OPENCV_INSTALL_SUBDIR/lib --OpenSSLLibsPath=../$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/lib  --BoostIncludesPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/include  --OpenCVIncludesPath=../$OPENCV_ROOT_DIR/$OPENCV_INSTALL_SUBDIR/include --OpenSSLIncludesPath=../$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/include --platform=x32 gmake > $CLOUD_LOCAL_BUILDING_FILE_NAME
	echo_run chmod u+x ./$CLOUD_LOCAL_BUILDING_FILE_NAME
fi

echo_run ./$CLOUD_LOCAL_BUILDING_FILE_NAME

cd projects/$OS_NAME-gmake

echo_run make -j$JOBS config=release

cd ../../..

# Install
if [ ! -d $CLOUD_INSTALL_SUBDIR ]; then
	echo_run mkdir $CLOUD_INSTALL_SUBDIR
else
	echo_run rm -rf $CLOUD_INSTALL_SUBDIR/htdocs
	echo_run rm -rf $CLOUD_INSTALL_SUBDIR/config.xml 
fi
echo_run cp -r $CLOUD_COMPONENT_NAME/projects/$OS_NAME-gmake/bin/release/* $CLOUD_INSTALL_SUBDIR
echo Done!

exit 0
