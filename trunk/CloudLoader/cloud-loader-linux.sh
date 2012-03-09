#!/bin/bash

# Display usage information.
usage()
{
	cat << EOF
${CYAN}Usage: $(basename $0) [options]${NORMAL}
${MAGENTA}Options:${NORMAL}
  ${YELLOW}--check-for-updates   ${BLUE}${BOLD}Check if a new version of this script is available${NORMAL}
  ${YELLOW}--checkout-source     ${BLUE}${BOLD}Checkout latest source from version control system${NORMAL}
  ${YELLOW}--help                ${BLUE}${BOLD}Display this information${NORMAL}
  ${YELLOW}--rebuild-libraries   ${BLUE}${BOLD}Rebuild all libraries and utilities${NORMAL}
  ${YELLOW}--self-update         ${BLUE}${BOLD}Update this script to the latest available version${NORMAL}
  ${YELLOW}--verbose             ${BLUE}${BOLD}Echo all executed commands${NORMAL}
  ${YELLOW}--version             ${BLUE}${BOLD}Display version information${NORMAL}
EOF
}

setNumberOfStages() # 1 - number of stages
{
	STAGES=$1
	STAGE=0
}

nextStage() # 1 - stage message
{
	STAGE=$[STAGE+1]
	STAGE_MSG="${YELLOW}[$STAGE/$STAGES] ${BLUE}${BOLD}$1...${NORMAL}"
	let STAGE_COL=$(tput cols)-${#STAGE_MSG}+${#YELLOW}+${#BLUE}+${#BOLD}+${#NORMAL}
	echo -n "$STAGE_MSG"
}

stageOK()
{
	let STAGE_COL=$STAGE_COL+${#GREEN}+${#NORMAL}
	printf "%${STAGE_COL}s\n" "${GREEN}[OK]${NORMAL}"
}

stageFailed()
{
	let STAGE_COL=$STAGE_COL+${#RED}+${#NORMAL}
	printf "%${STAGE_COL}s\n" "${RED}[FAILED]${NORMAL}"
}

# Perform a check for a new version of this script.
checkForUpdates()
{
	echo "${CYAN}Checking for updates...${NORMAL}"
	echo -n "${YELLOW}Current version: ${BLUE}${BOLD}$LOADER_VERSION"
	if $REVISION_DEFINED; then
		echo -n "-$REVISION"
	else
		echo -n " [unknown revision]"
	fi
	echo "${NORMAL}"
	
	export LC_MESSAGES=C
	LOADER_URL=http://$LOADER_SRCSITE$LOADER_SRCPATH/$LOADER_SRCFILE
	LATEST_REVISION=$(svn info $LOADER_URL | grep '^Last Changed Rev:')
	LATEST_REVISION=${LATEST_REVISION#'Last Changed Rev: '}
	export -n LC_MESSAGES
	
	echo "${YELLOW}Latest version: ${BLUE}${BOLD}$LOADER_VERSION-$LATEST_REVISION${NORMAL}"
}

# Update the script to the latest available version.
selfUpdate()
{
	echo "${CYAN}Updating the script...${NORMAL}"
	
	SELF=$(basename "$0")
	UPDATER=cloud-updater-linux.sh
	
	setNumberOfStages 7
	nextStage "Downloading the latest version"
	svn export $LOADER_URL $SELF.new >& /dev/null
	if [ $? -ne 0 ]; then
		stageFailed
		return 1
	fi
	stageOK
	
	nextStage "Reading file modes"
	OCTAL_MODE=$(stat -c '%a' $SELF)
	if [ $? -ne 0 ]; then
		stageFailed
		return 1
	fi
	stageOK
	
	nextStage "Copying file modes"
	chmod $OCTAL_MODE $SELF.new
	if [ $? -ne 0 ]; then
		stageFailed
		return 1
	fi
	stageOK
	
	nextStage "Generating update script"
	cat > $UPDATER << EOF
#!/bin/bash

nextStage() # 1 - stage message
{
	STAGE=\$[STAGE+1]
	STAGE_MSG="\${YELLOW}[\$STAGE/\$STAGES] \${BLUE}\${BOLD}\$1...\${NORMAL}"
	let STAGE_COL=\$(tput cols)-\${#STAGE_MSG}+\${#YELLOW}+\${#BLUE}+\${#BOLD}+\${#NORMAL}
	echo -n "\$STAGE_MSG"
}

stageOK()
{
	let STAGE_COL=\$STAGE_COL+\${#GREEN}+\${#NORMAL}
	printf "%\${STAGE_COL}s\n" "\${GREEN}[OK]\${NORMAL}"
}

stageFailed()
{
	let STAGE_COL=\$STAGE_COL+\${#RED}+\${#NORMAL}
	printf "%\${STAGE_COL}s\n" "\${RED}[FAILED]\${NORMAL}"
}

stageOK

nextStage "Replacing old version with the new one"
mv $SELF.new $SELF
if [ $? -ne 0 ]; then
	stageFailed
	echo "${RED}Update failed.${NORMAL}"
	exit 1
fi
stageOK

nextStage "Deleting update script"
rm \$0
if [ $? -ne 0 ]; then
	stageFailed
	echo "${RED}Update failed.${NORMAL}"
	exit 1
fi
stageOK

echo "${GREEN}Update succeeded.${NORMAL}"
exit 0
EOF
	if [ $? -ne 0 ]; then
		stageFailed
		return 1
	fi
	stageOK
	
	nextStage "Running update script"
	export STAGE STAGE_COL STAGES
	exec /bin/bash $UPDATER
	if [ $? -ne 0 ]; then
		stageFailed
	fi
	
	return 0
}

# Print the command and run it. Exit the script on failure.
run()
{
	if $VERBOSE; then
		echo "$@"
		"$@"
	else
		"$@" >& /dev/null
	fi
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
		run curl -L http://$4$5/$1 -o $DOWNLOADS/$1
	fi
	
	case ${1##*.} in
		bz2 )
			run tar -xjf $DOWNLOADS/$1
			;;
		gz  )
			run tar -xzf $DOWNLOADS/$1
			;;
		zip )
			run unzip $DOWNLOADS/$1
			;;
		*   )
			echo "Error: unknown archive type."
			exit 1
			;;
	esac
	
	run rm -rf $2
	run mv $3 $2
}

# Declare variables related to this loader script.
LOADER_VERSION=0.5.0
LOADER_SRCFILE=cloud-loader-linux.sh
LOADER_SRCPATH=/svn/trunk/CloudLoader
LOADER_SRCSITE=cloudobserver.googlecode.com

# Remember the revision of the script.
REVISION='$Revision$'
if [ "$REVISION" != "\$Revision\$" ]; then
	REVISION=${REVISION#'$Revision: '}
	REVISION=${REVISION%' $'}
	REVISION_DEFINED=true
else
	REVISION=0
	REVISION_DEFINED=false
fi

# Declare style variables.
export NORMAL=$(tput sgr0)
export BOLD=$(tput bold)
export BLACK=$(tput setaf 0)
export RED=$(tput setaf 1)
export GREEN=$(tput setaf 2)
export YELLOW=$(tput setaf 3)
export BLUE=$(tput setaf 4)
export MAGENTA=$(tput setaf 5)
export CYAN=$(tput setaf 6)
export WHITE=$(tput setaf 7)

# Declare option variables.
CHECKOUT_SOURCE=false
REBUILD_LIBRARIES=false
VERBOSE=false

# Parse command line arguments.
for i in $*
do
	case $i in
		--check-for-updates )
			checkForUpdates
			if [ $LATEST_REVISION -gt $REVISION ]; then
				echo "${RED}New version of this script is available.${NORMAL}"
				echo "${CYAN}Type '$0 --self-update' to update it.${NORMAL}"
			else
				echo "${GREEN}You are using the most recent version of this script.${NORMAL}"
			fi
			exit 0
			;;
		--checkout-source   )
			CHECKOUT_SOURCE=true
			;;
		--help              )
			usage
			exit 0
			;;
		--rebuild-libraries )
			REBUILD_LIBRARIES=true
			;;
		--self-update       )
			checkForUpdates
			if [ $LATEST_REVISION -eq $REVISION ]; then
				echo "${GREEN}You already use the most recent version of this script.${NORMAL}"
				exit 0
			fi
			selfUpdate
			if [ $? -ne 0 ]; then
				echo "${RED}Update failed.${NORMAL}"
				exit 1
			fi
			exit 0
			;;
		--verbose           )
			VERBOSE=true
			;;
		--version           )
			echo -n "${CYAN}Cloud Loader $LOADER_VERSION"
			if $REVISION_DEFINED; then
				echo -n "-$REVISION"
			else
				echo -n " [unknown revision]"
			fi
			echo "${NORMAL}"
			echo "${CYAN}Copyright (C) 2012 Cloud Forever. All rights reserved.${NORMAL}"
			exit 0
			;;
		*                   )
			echo "${RED}Unknown option: '$i'${NORMAL}"
			echo "${CYAN}Type '$0 --help' to display usage information.${NORMAL}"
			exit 1
			;;
	esac
done

# Move to the directory containing the script.
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do SOURCE="$(readlink "$SOURCE")"; done
run cd "$( cd -P "$( dirname "$SOURCE" )" && pwd )"

# Declare, create and move to the workspace directory.
WORKSPACE=cloud_server
run mkdir -p $WORKSPACE
run cd $WORKSPACE

# Remember the workspace directory path.
WD=$(pwd)

# Declare variables related to CMake utility.
CMAKE_VERSION=2.8.6
CMAKE_COMPILE="$WD"/cmake-src
CMAKE_INSTALL="$WD"/cmake
CMAKE_SRCBASE=cmake-$CMAKE_VERSION
CMAKE_SRCFILE=$CMAKE_SRCBASE.tar.gz
CMAKE_SRCPATH=/files/v${CMAKE_VERSION%.*}
CMAKE_SRCSITE=www.cmake.org

# Declare variables related to Premake utility.
PREMAKE_VERSION=4.3
PREMAKE_COMPILE="$WD"/premake-src
PREMAKE_INSTALL="$WD"/premake
PREMAKE_SRCBASE=premake-$PREMAKE_VERSION
PREMAKE_SRCFILE=$PREMAKE_SRCBASE-src.zip
PREMAKE_SRCPATH=/projects/premake/files/Premake/$PREMAKE_VERSION
PREMAKE_SRCSITE=sourceforge.net

# Declare variables related to YASM utility.
YASM_VERSION=1.2.0
YASM_COMPILE="$WD"/yasm-src
YASM_INSTALL="$WD"/yasm
YASM_SRCBASE=yasm-$YASM_VERSION
YASM_SRCFILE=$YASM_SRCBASE.tar.gz
YASM_SRCPATH=/projects/yasm/releases
YASM_SRCSITE=www.tortall.net

# Declare variables related to Boost libraries.
BOOST_VERSION=1.47.0
BOOST_COMPILE="$WD"/boost-src
BOOST_INSTALL="$WD"/boost
BOOST_SRCBASE=boost_${BOOST_VERSION//./_}
BOOST_SRCFILE=$BOOST_SRCBASE.tar.bz2
BOOST_SRCPATH=/projects/boost/files/boost/$BOOST_VERSION
BOOST_SRCSITE=sourceforge.net
BOOST_ZLIBSRC="$BOOST_COMPILE"/zlib-src

# Declare variables related to FFmpeg libraries.
FFMPEG_VERSION=0.10
FFMPEG_COMPILE="$WD"/ffmpeg-src
FFMPEG_INSTALL="$WD"/ffmpeg
FFMPEG_SRCBASE=ffmpeg-$FFMPEG_VERSION
FFMPEG_SRCFILE=$FFMPEG_SRCBASE.tar.bz2
FFMPEG_SRCPATH=/releases
FFMPEG_SRCSITE=ffmpeg.org

# Declare variables related to OpenCV libraries.
OPENCV_VERSION=2.3.1
OPENCV_COMPILE="$WD"/opencv-src
OPENCV_INSTALL="$WD"/opencv
OPENCV_SRCBASE=OpenCV-$OPENCV_VERSION
OPENCV_SRCFILE="$OPENCV_SRCBASE"a.tar.bz2 # note the 'a' character (it's 2.3.1a)
OPENCV_SRCPATH=/projects/opencvlibrary/files/opencv-unix/$OPENCV_VERSION
OPENCV_SRCSITE=sourceforge.net
OPENCV_ZLIBSRC="$OPENCV_COMPILE"/zlib-src

# Declare variables related to OpenSSL libraries.
OPENSSL_VERSION=1.0.0d
OPENSSL_COMPILE="$WD"/openssl-src
OPENSSL_INSTALL="$WD"/openssl
OPENSSL_SRCBASE=openssl-$OPENSSL_VERSION
OPENSSL_SRCFILE=$OPENSSL_SRCBASE.tar.gz
OPENSSL_SRCPATH=/source
OPENSSL_SRCSITE=www.openssl.org

# Declare variables related to zlib library.
ZLIB_VERSION=1.2.6
ZLIB_SRCBASE=zlib-$ZLIB_VERSION
ZLIB_SRCFILE=$ZLIB_SRCBASE.tar.bz2
ZLIB_SRCPATH=/projects/libpng/files/zlib/$ZLIB_VERSION
ZLIB_SRCSITE=sourceforge.net

# Declare variables related to Cloud Server application.
CLOUD_COMPILE="$WD"/cloudserver-src
CLOUD_INSTALL="$WD"/install-dir
CLOUD_PREMAKE=build.sh
CLOUD_SRCBASE=CloudServer
CLOUD_SRCPATH=/svn/trunk/$CLOUD_SRCBASE
CLOUD_SRCSITE=cloudobserver.googlecode.com

# Declare other variables.
DOWNLOADS=downloads
OS=linux
JOBS=$(grep ^processor /proc/cpuinfo | wc -l)

# The number of stages is unknown.
setNumberOfStages ?

# Delete existing libraries and utilities if they should be rebuilt.
if $REBUILD_LIBRARIES; then
	nextStage "Deleting existing libraries and utilities"
	run rm -rf "$CMAKE_INSTALL"
	run rm -rf "$OPENCV_INSTALL"
	run rm -rf "$BOOST_INSTALL"
	run rm -rf "$OPENSSL_INSTALL"
	run rm -rf "$PREMAKE_INSTALL"
	run rm -rf "$YASM_INSTALL"
	run rm -rf "$FFMPEG_INSTALL"
	stageOK
fi

# Build CMake utility if necessary.
if [ ! -d "$CMAKE_INSTALL" ]; then
	nextStage "Building CMake utility"
	prepare $CMAKE_SRCFILE "$CMAKE_COMPILE" $CMAKE_SRCBASE $CMAKE_SRCSITE $CMAKE_SRCPATH
	run cd "$CMAKE_COMPILE"
	run ./bootstrap --parallel=$JOBS --prefix="$CMAKE_INSTALL"
	run make -j$JOBS install
	run cd $WD
	run rm -rf "$CMAKE_COMPILE"
	stageOK
fi

# Build Premake utility if necessary.
if [ ! -d "$PREMAKE_INSTALL" ]; then
	nextStage "Building Premake utility"
	prepare $PREMAKE_SRCFILE "$PREMAKE_COMPILE" $PREMAKE_SRCBASE $PREMAKE_SRCSITE $PREMAKE_SRCPATH
	run cd "$PREMAKE_COMPILE"/build/gmake.unix
	run make -j$JOBS config=release
	run cd ../..
	run mkdir -p "$PREMAKE_INSTALL"/bin
	run cp bin/release/premake4 "$PREMAKE_INSTALL"/bin
	run cd $WD
	run rm -rf "$PREMAKE_COMPILE"
	stageOK
fi

# Build YASM utility if necessary.
if [ ! -d "$YASM_INSTALL" ]; then
	nextStage "Building YASM utility"
	prepare $YASM_SRCFILE "$YASM_COMPILE" $YASM_SRCBASE $YASM_SRCSITE $YASM_SRCPATH
	run cd "$YASM_COMPILE"
	run ./configure --prefix="$YASM_INSTALL"
	run make -j$JOBS install
	run cd $WD
	run rm -rf "$YASM_COMPILE"
	stageOK
fi

# Build Boost libraries if necessary.
if [ ! -d "$BOOST_INSTALL" ]; then
	nextStage "Building Boost libraries"
	prepare $BOOST_SRCFILE "$BOOST_COMPILE" $BOOST_SRCBASE $BOOST_SRCSITE $BOOST_SRCPATH
	prepare $ZLIB_SRCFILE "$BOOST_ZLIBSRC" $ZLIB_SRCBASE $ZLIB_SRCSITE $ZLIB_SRCPATH
	run cd "$BOOST_COMPILE"
	run ./bootstrap.sh
	run ./b2 -j$JOBS -d0 --with-thread --with-system --with-filesystem --with-serialization --with-program_options --with-regex --with-date_time --with-iostreams -sZLIB_SOURCE="$BOOST_ZLIBSRC" -sNO_BZIP2=1 cflags=-fPIC cxxflags=-fPIC link=static --prefix="$BOOST_INSTALL" release install
	run cd $WD
	run rm -rf "$BOOST_COMPILE"
	stageOK
fi

# Build FFmpeg libraries if necessary.
if [ ! -d "$FFMPEG_INSTALL" ]; then
	nextStage "Building FFmpeg libraries"
	prepare $FFMPEG_SRCFILE "$FFMPEG_COMPILE" $FFMPEG_SRCBASE $FFMPEG_SRCSITE $FFMPEG_SRCPATH
	run cd "$FFMPEG_COMPILE"
	export PATH=$PATH:"$YASM_INSTALL"/bin
	run ./configure --enable-static --disable-shared --prefix="$FFMPEG_INSTALL"
	run make -j$JOBS install
	run cd $WD
	run rm -rf "$FFMPEG_COMPILE"
	stageOK
fi

# Build OpenCV libraries if necessary.
if [ ! -d "$OPENCV_INSTALL" ]; then
	nextStage "Building OpenCV libraries"
	prepare $OPENCV_SRCFILE "$OPENCV_COMPILE" $OPENCV_SRCBASE $OPENCV_SRCSITE $OPENCV_SRCPATH
	prepare $ZLIB_SRCFILE "$OPENCV_ZLIBSRC" $ZLIB_SRCBASE $ZLIB_SRCSITE $ZLIB_SRCPATH
	run cd "$OPENCV_COMPILE"
	run cp $(echo "$OPENCV_ZLIBSRC"/*.[ch]) ./3rdparty/zlib
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
	run make -j$JOBS install
	run cp "$OPENCV_INSTALL"/share/OpenCV/3rdparty/lib/* "$OPENCV_INSTALL"/lib
	run cd $WD
	run rm -rf "$OPENCV_COMPILE"
	stageOK
fi

# Build OpenSSL libraries if necessary.
if [ ! -d "$OPENSSL_INSTALL" ]; then
	nextStage "Building OpenSSL libraries"
	prepare $OPENSSL_SRCFILE "$OPENSSL_COMPILE" $OPENSSL_SRCBASE $OPENSSL_SRCSITE $OPENSSL_SRCPATH
	run cd "$OPENSSL_COMPILE"
	run ./config shared no-asm --prefix="$OPENSSL_INSTALL" --openssldir="$OPENSSL_INSTALL"/share
	run make install
	run cd $WD
	run rm -rf "$OPENSSL_COMPILE"
	stageOK
fi

# Checkout Cloud Server application source code if necessary.
if $CHECKOUT_SOURCE || [ ! -d "$CLOUD_COMPILE" ]; then
	nextStage "Checking out Cloud Server application source code"
	run rm -rf "$CLOUD_COMPILE"
	run svn checkout https://$CLOUD_SRCSITE$CLOUD_SRCPATH "$CLOUD_COMPILE"
	stageOK
fi

# Build Cloud Server application.
nextStage "Building Cloud Server application"
run cd "$CLOUD_COMPILE"
if [ ! -e $CLOUD_PREMAKE ]; then
	cat > $CLOUD_PREMAKE << EOF
"$PREMAKE_INSTALL"/bin/premake4 --os=$OS --BoostLibsPath="$BOOST_INSTALL"/lib  --OpenCVLibsPath="$OPENCV_INSTALL"/lib --OpenSSLLibsPath="$OPENSSL_INSTALL"/lib  --BoostIncludesPath="$BOOST_INSTALL"/include  --OpenCVIncludesPath="$OPENCV_INSTALL"/include --OpenSSLIncludesPath="$OPENSSL_INSTALL"/include --platform=x32 gmake
EOF
	run chmod u+x ./$CLOUD_PREMAKE
fi
run ./$CLOUD_PREMAKE
run cd projects/$OS-gmake
run make -j$JOBS config=release
run cd $WD
stageOK

# Install Cloud Server application.
nextStage "Installing Cloud Server application"
if [ ! -d "$CLOUD_INSTALL" ]; then
	run mkdir "$CLOUD_INSTALL"
else
	run rm -rf "$CLOUD_INSTALL"/htdocs
	run rm -rf "$CLOUD_INSTALL"/config.xml
fi
run cp -r "$CLOUD_COMPILE"/projects/$OS-gmake/bin/release/* "$CLOUD_INSTALL"
run rm -rf "$CLOUD_COMPILE"
stageOK

exit 0

