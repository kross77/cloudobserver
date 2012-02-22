#!/bin/bash
# requires svn, curl, gcc

# Move to the directory containing the script.
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do SOURCE="$(readlink "$SOURCE")"; done
cd "$( cd -P "$( dirname "$SOURCE" )" && pwd )"

# Declare, create and move to the workspace directory.
WORKSPACE=cloud_server
mkdir -p $WORKSPACE
cd $WORKSPACE

# Remember the workspace directory path.
WD=`pwd`

# Declare variables related to Boost libraries.
BOOST_VERSION=1.47.0
BOOST_COMPILE="$WD"/boost-src
BOOST_INSTALL="$WD"/boost
BOOST_SRCBASE=boost_${BOOST_VERSION//./_}
BOOST_SRCFILE=$BOOST_SRCBASE.tar.bz2
BOOST_SRCPATH=project/boost/boost/$BOOST_VERSION
BOOST_SRCSITE=surfnet.dl.sourceforge.net

# Declare variables related to Cloud Server application.
CLOUD_COMPILE="$WD"/cloudserver-src
CLOUD_INSTALL="$WD"/install-dir
CLOUD_PREMAKE=build.sh
CLOUD_SRCBASE=CloudServer
CLOUD_SRCPATH=svn/trunk/$CLOUD_SRCBASE
CLOUD_SRCSITE=cloudobserver.googlecode.com

# Declare variables related to CMake utility.
CMAKE_VERSION=2.8.6
CMAKE_COMPILE="$WD"/cmake-src
CMAKE_INSTALL="$WD"/cmake
CMAKE_SRCBASE=cmake-$CMAKE_VERSION
CMAKE_SRCFILE=$CMAKE_SRCBASE.tar.gz
CMAKE_SRCPATH=files/v${CMAKE_VERSION%.*}
CMAKE_SRCSITE=www.cmake.org

# Declare variables related to OpenCV libraries.
OPENCV_VERSION=2.3.1
OPENCV_COMPILE="$WD"/opencv-src
OPENCV_INSTALL="$WD"/opencv
OPENCV_SRCBASE=OpenCV-$OPENCV_VERSION
OPENCV_SRCFILE="$OPENCV_SRCBASE"a.tar.bz2 # note the 'a' character (it's 2.3.1a)
OPENCV_SRCPATH=project/opencvlibrary/opencv-unix/$OPENCV_VERSION
OPENCV_SRCSITE=surfnet.dl.sourceforge.net

# Declare variables related to OpenSSL libraries.
OPENSSL_VERSION=1.0.0d
OPENSSL_COMPILE="$WD"/openssl-src
OPENSSL_INSTALL="$WD"/openssl
OPENSSL_SRCBASE=openssl-$OPENSSL_VERSION
OPENSSL_SRCFILE=$OPENSSL_SRCBASE.tar.gz
OPENSSL_SRCPATH=source
OPENSSL_SRCSITE=www.openssl.org

# Declare variables related to Premake utility.
PREMAKE_VERSION=4.3
PREMAKE_COMPILE="$WD"/premake-src
PREMAKE_INSTALL="$WD"/premake
PREMAKE_SRCBASE=premake-$PREMAKE_VERSION
PREMAKE_SRCFILE=$PREMAKE_SRCBASE-src.zip
PREMAKE_SRCPATH=project/premake/Premake/$PREMAKE_VERSION
PREMAKE_SRCSITE=surfnet.dl.sourceforge.net

# Declare variables related to zlib library.
ZLIB_COMPILE="$OPENCV_COMPILE"/3rdparty/zlib

# Declare option variables.
CHECKOUT_SOURCE=false
REBUILD_LIBRARIES=false
VERBOSE=false

# Declare other variables.
DOWNLOADS=downloads
OS=linux
JOBS=`grep ^processor /proc/cpuinfo | wc -l`

# Parse command line arguments.
for i in $*
do
	case $i in
		--checkout-source	)
			CHECKOUT_SOURCE=true
			;;
		--help				)
			echo "Usage: cloud-loader-linux.sh [options]"
			echo "Options:"
			echo "  --checkout-source     Checkout latest source from version control system"
			echo "  --help                Display this information"
			echo "  --rebuild-libraries   Rebuild all libraries and utilities"
			echo "  --verbose             Echo all executed commands"
			exit 0
			;;
		--rebuild-libraries	)
			REBUILD_LIBRARIES=true
			;;
		--verbose			)
			VERBOSE=true
			;;
	esac
done

# Print the command and run it. Exit the script on failure.
run()
{
	if $VERBOSE; then
		echo "$@"
	fi
	"$@"
	result=$?
	if [ $result -ne 0 ]; then
		exit $result
	fi
}

# Prepare the library or utility by extracting its source to compile directory.
# Download the source archive if necessary.
prepare() # 1=SRCFILE 2=COMPILE 3=SRCBASE 4=SRCSITE 5=SRCPATH
{
	if [ ! -d $DOWNLOADS ]; then
		run mkdir -p $DOWNLOADS
	fi
	
	if [ ! -e $DOWNLOADS/$1 ]; then
		run curl -L http://$4/$5/$1 -o $DOWNLOADS/$1
	fi
	
	case ${1##*.} in
		bz2	)
			run tar -xjf $DOWNLOADS/$1
			;;
		gz	)
			run tar -xzf $DOWNLOADS/$1
			;;
		zip	)
			run unzip $DOWNLOADS/$1
			;;
		*	)
			echo "Error: unknown archive type."
			exit 1;
			;;
	esac
	
	run rm -rf $2
	run mv $3 $2
}

# Delete existing libraries and utilities if they should be rebuilt.
if $REBUILD_LIBRARIES; then
	rm -rf "$CMAKE_INSTALL"
	rm -rf "$OPENCV_INSTALL"
	rm -rf "$BOOST_INSTALL"
	rm -rf "$OPENSSL_INSTALL"
	rm -rf "$PREMAKE_INSTALL"
fi

# Build CMake utility if necessary.
if [ ! -d "$CMAKE_INSTALL" ]; then
	prepare $CMAKE_SRCFILE "$CMAKE_COMPILE" $CMAKE_SRCBASE $CMAKE_SRCSITE $CMAKE_SRCPATH
	cd "$CMAKE_COMPILE"
	run ./bootstrap --parallel=$JOBS --prefix="$CMAKE_INSTALL"; 
	run make -j$JOBS install
	cd ..
fi

# Build OpenCV libraries if necessary.
if [ ! -d "$OPENCV_INSTALL" ]; then
	prepare $OPENCV_SRCFILE "$OPENCV_COMPILE" $OPENCV_SRCBASE $OPENCV_SRCSITE $OPENCV_SRCPATH
	cd "$OPENCV_COMPILE"
	# Adding the following option:
	#   -DEXECUTABLE_OUTPUT_PATH="$OPENCV_INSTALL"/bin
	# to the CMake call leads to an error during the build
	# with 'opencv_traincascade' executable not being created.
	# It seems like a bug in OpenCV CMake script.
	run "$CMAKE_INSTALL"/bin/cmake \
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
		-DCMAKE_INSTALL_PREFIX="$OPENCV_INSTALL" \
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
		-DLIBRARY_OUTPUT_PATH="$OPENCV_INSTALL"/lib \
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
	run cp "$OPENCV_INSTALL"/share/OpenCV/3rdparty/lib/* "$OPENCV_INSTALL"/lib
	cd ..
fi

# Build Boost libraries if necessary.
if [ ! -d "$BOOST_INSTALL" ]; then
	prepare $BOOST_SRCFILE "$BOOST_COMPILE" $BOOST_SRCBASE $BOOST_SRCSITE $BOOST_SRCPATH
	cd "$BOOST_COMPILE"
	run ./bootstrap.sh
	run ./b2 -j$JOBS -d0 --with-thread --with-system --with-filesystem --with-serialization --with-program_options --with-regex --with-date_time --with-iostreams -sZLIB_SOURCE="$ZLIB_COMPILE" -sNO_BZIP2=1 cflags=-fPIC cxxflags=-fPIC link=static --prefix="$BOOST_INSTALL" release install
	cd ..
fi

# Build OpenSSL libraries if necessary.
if [ ! -d "$OPENSSL_INSTALL" ]; then
	prepare $OPENSSL_SRCFILE "$OPENSSL_COMPILE" $OPENSSL_SRCBASE $OPENSSL_SRCSITE $OPENSSL_SRCPATH
	cd "$OPENSSL_COMPILE"
	run ./config shared no-asm --prefix="$OPENSSL_INSTALL" --openssldir="$OPENSSL_INSTALL"/share
	run make install
	cd ..
fi

# Build Premake utility if necessary.
if [ ! -d "$PREMAKE_INSTALL" ]; then
	prepare $PREMAKE_SRCFILE "$PREMAKE_COMPILE" $PREMAKE_SRCBASE $PREMAKE_SRCSITE $PREMAKE_SRCPATH
	cd "$PREMAKE_COMPILE"/build/gmake.unix
	run make -j$JOBS config=release
	cd ../..
	mkdir -p "$PREMAKE_INSTALL"/bin
	cp bin/release/premake4 "$PREMAKE_INSTALL"/bin
	cd ..
fi

# Checkout Cloud Server application source code if necessary.
if $CHECKOUT_SOURCE || [ ! -d "$CLOUD_COMPILE" ]; then
	run rm -rf "$CLOUD_COMPILE"/
	run svn checkout https://$CLOUD_SRCSITE/$CLOUD_SRCPATH "$CLOUD_COMPILE"
fi

# Build Cloud Server application.
cd "$CLOUD_COMPILE"

if [ ! -e $CLOUD_PREMAKE ]; then
	run echo "$PREMAKE_INSTALL"/bin/premake4 --os=$OS --BoostLibsPath="$BOOST_INSTALL"/lib  --OpenCVLibsPath="$OPENCV_INSTALL"/lib --OpenSSLLibsPath="$OPENSSL_INSTALL"/lib  --BoostIncludesPath="$BOOST_INSTALL"/include  --OpenCVIncludesPath="$OPENCV_INSTALL"/include --OpenSSLIncludesPath="$OPENSSL_INSTALL"/include --platform=x32 gmake > $CLOUD_PREMAKE
	run chmod u+x ./$CLOUD_PREMAKE
fi
run ./$CLOUD_PREMAKE
cd projects/$OS-gmake
run make -j$JOBS config=release
cd ../../..

# Install Cloud Server application.
if [ ! -d "$CLOUD_INSTALL" ]; then
	run mkdir "$CLOUD_INSTALL"
else
	run rm -rf "$CLOUD_INSTALL"/htdocs
	run rm -rf "$CLOUD_INSTALL"/config.xml 
fi
run cp -r "$CLOUD_COMPILE"/projects/$OS-gmake/bin/release/* "$CLOUD_INSTALL"
echo Done!

exit 0
