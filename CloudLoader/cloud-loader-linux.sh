#!/bin/bash
# requires svn, curl, gcc
BOOST_VERSION=1.47.0
CMAKE_VERSION=2.8.6
OPENCV_VERSION=2.3.1
OPENSSL_VERSION=1.0.0d
PREMAKE_VERSION=4.3

WORKSPACE=cloud_server
DOWNLOADS=downloads

JOBS=`grep ^processor /proc/cpuinfo | wc -l`

CLOUD_SRCSITE=cloudobserver.googlecode.com
CLOUD_COMPILE=CloudServer
CLOUD_INSTALL=install-dir

CLOUD_PREMAKE=build.sh

OS=linux

KEEP_OLD=no
REBUILD_LIBRARIES=no

BOOST_SRCSITE=surfnet.dl.sourceforge.net
BOOST_SRCPATH=project/boost/boost/$BOOST_VERSION
BOOST_SRCBASE=boost_${BOOST_VERSION//./_}
BOOST_SRCFILE="$BOOST_SRCBASE".tar.bz2
BOOST_COMPILE=boost_libraries
BOOST_INSTALL=install-dir

ZLIB_COMPILE=opencv_libraries/3rdparty/zlib

OPENSSL_SRCSITE=www.openssl.org
OPENSSL_SRCBASE=openssl-$OPENSSL_VERSION
OPENSSL_SRCFILE="$OPENSSL_SRCBASE".tar.gz
OPENSSL_SRCPATH=source
OPENSSL_COMPILE=openssl_libraries
OPENSSL_INSTALL=install-dir

OPENCV_SRCSITE=surfnet.dl.sourceforge.net
OPENCV_SRCPATH=project/opencvlibrary/opencv-unix/$OPENCV_VERSION
OPENCV_SRCBASE=OpenCV-$OPENCV_VERSION
OPENCV_SRCFILE="$OPENCV_SRCBASE"a.tar.bz2
OPENCV_COMPILE=opencv_libraries
OPENCV_INSTALL=install-dir

CMAKE_SRCSITE=www.cmake.org
CMAKE_SRCPATH=files/v${CMAKE_VERSION%.*}
CMAKE_SRCBASE=cmake-$CMAKE_VERSION
CMAKE_SRCFILE="$CMAKE_SRCBASE".tar.gz
CMAKE_COMPILE=cmake
CMAKE_INSTALL=install-dir

PREMAKE_SRCSITE=surfnet.dl.sourceforge.net
PREMAKE_SRCPATH=project/premake/Premake/$PREMAKE_VERSION
PREMAKE_SRCBASE=premake-$PREMAKE_VERSION
PREMAKE_SRCFILE="$PREMAKE_SRCBASE"-src.zip
PREMAKE_COMPILE=premake
PREMAKE_INSTALL=install-dir

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

load() # 1=SRCFILE 2=COMPILE 3=SRCBASE 4=SRCSITE 5=SRCPATH
{
	if [ ! -e $DOWNLOADS/$1 ]; then
		echo_run curl -L http://$4/$5/$1 -o $DOWNLOADS/$1
	fi
	
	if [ ${1##*.} == "zip" ]; then
		echo_run unzip $DOWNLOADS/$1
	elif [ ${1##*.} == "bz2" ]; then
		echo_run tar -xjf $DOWNLOADS/$1
	else
		echo_run tar -xzf $DOWNLOADS/$1
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

if [ ! -d $DOWNLOADS ]; then
	echo_run mkdir $DOWNLOADS
fi

if [ "$REBUILD_LIBRARIES" = "yes" ]; then
	rm -rf $CMAKE_COMPILE
	rm -rf $OPENCV_COMPILE
	rm -rf $BOOST_COMPILE
	rm -rf $OPENSSL_COMPILE
	rm -rf $PREMAKE_COMPILE
fi

# CMake
if [ ! -d $CMAKE_COMPILE ]; then
	load $CMAKE_SRCFILE $CMAKE_COMPILE $CMAKE_SRCBASE $CMAKE_SRCSITE $CMAKE_SRCPATH
	cd $CMAKE_COMPILE

	echo_run ./bootstrap --parallel=$JOBS --prefix=./$CMAKE_INSTALL; 
	echo_run make -j$JOBS install
	
	cd ..
fi

# OpenCV
if [ ! -d $OPENCV_COMPILE ]; then
	load $OPENCV_SRCFILE $OPENCV_COMPILE $OPENCV_SRCBASE $OPENCV_SRCSITE $OPENCV_SRCPATH

	cd $OPENCV_COMPILE

	# Adding the following option:
	#   -DEXECUTABLE_OUTPUT_PATH=./$OPENCV_INSTALL/bin
	# to the CMake call leads to an error during the build
	# with 'opencv_traincascade' executable not being created.
	# It seems like a bug in OpenCV CMake script.
	echo_run ../$CMAKE_COMPILE/bin/cmake \
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
		-DCMAKE_INSTALL_PREFIX=./$OPENCV_INSTALL \
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
		-DLIBRARY_OUTPUT_PATH=./$OPENCV_INSTALL/lib \
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

	echo_run cp $OPENCV_INSTALL/share/OpenCV/3rdparty/lib/* $OPENCV_INSTALL/lib

	cd ..
fi

# Boost
if [ ! -d $BOOST_COMPILE ]; then
	load $BOOST_SRCFILE $BOOST_COMPILE $BOOST_SRCBASE $BOOST_SRCSITE $BOOST_SRCPATH

	cd $BOOST_COMPILE

	if [ ! -f ./b2 ]; then
		echo_run ./bootstrap.sh
	fi

	echo_run ./b2 -j$JOBS -d0 --with-thread --with-system --with-filesystem --with-serialization --with-program_options --with-regex --with-date_time --with-iostreams -sZLIB_SOURCE="$WD/$WORKSPACE/$ZLIB_COMPILE/" -sNO_BZIP2=1 cflags=-fPIC cxxflags=-fPIC link=static --prefix=./$BOOST_INSTALL release install

	cd ..
fi

# OpenSSL
if [ ! -d $OPENSSL_COMPILE ]; then
	load $OPENSSL_SRCFILE $OPENSSL_COMPILE $OPENSSL_SRCBASE $OPENSSL_SRCSITE $OPENSSL_SRCPATH
	
	cd $OPENSSL_COMPILE

	echo_run ./config shared no-asm --prefix="$WD/$WORKSPACE/$OPENSSL_COMPILE/$OPENSSL_INSTALL" --openssldir="$WD/$WORKSPACE/$OPENSSL_COMPILE/$OPENSSL_INSTALL/share"
	echo_run make install

	cd ..
fi

# Premake
if [ ! -d $PREMAKE_COMPILE ]; then
	load $PREMAKE_SRCFILE $PREMAKE_COMPILE $PREMAKE_SRCBASE $PREMAKE_SRCSITE $PREMAKE_SRCPATH
	
	cd $PREMAKE_COMPILE/build/gmake.unix
	
	echo_run make -j$JOBS config=release
	
	cd ../..
	
	mkdir -p ./$PREMAKE_INSTALL/bin
	cp bin/release/premake4 ./$PREMAKE_INSTALL/bin
	
	cd ..
fi

# CloudServer
if [ "$KEEP_OLD" = "no" -o ! -d $CLOUD_COMPILE ]; then
	echo_run rm -rf $CLOUD_COMPILE/
	echo_run svn checkout https://$CLOUD_SRCSITE/svn/trunk/$CLOUD_COMPILE/ $CLOUD_COMPILE
fi

cd $CLOUD_COMPILE

if [ ! -e $CLOUD_PREMAKE ]; then
	echo_run echo ../$PREMAKE_COMPILE/bin/release/premake4 --os=$OS --BoostLibsPath=../$BOOST_COMPILE/$BOOST_INSTALL/lib  --OpenCVLibsPath=../$OPENCV_COMPILE/$OPENCV_INSTALL/lib --OpenSSLLibsPath=../$OPENSSL_COMPILE/$OPENSSL_INSTALL/lib  --BoostIncludesPath=../$BOOST_COMPILE/$BOOST_INSTALL/include  --OpenCVIncludesPath=../$OPENCV_COMPILE/$OPENCV_INSTALL/include --OpenSSLIncludesPath=../$OPENSSL_COMPILE/$OPENSSL_INSTALL/include --platform=x32 gmake > $CLOUD_PREMAKE
	echo_run chmod u+x ./$CLOUD_PREMAKE
fi

echo_run ./$CLOUD_PREMAKE

cd projects/$OS-gmake

echo_run make -j$JOBS config=release

cd ../../..

# Install
if [ ! -d $CLOUD_INSTALL ]; then
	echo_run mkdir $CLOUD_INSTALL
else
	echo_run rm -rf $CLOUD_INSTALL/htdocs
	echo_run rm -rf $CLOUD_INSTALL/config.xml 
fi
echo_run cp -r $CLOUD_COMPILE/projects/$OS-gmake/bin/release/* $CLOUD_INSTALL
echo Done!

exit 0
