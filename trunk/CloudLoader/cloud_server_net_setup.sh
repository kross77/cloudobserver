#!/bin/bash
# requires svn, premake, curl, gcc

CLOUD_DISTRO_SITE=cloudobserver.googlecode.com
CLOUD_COMPONENT_NAME=CloudServer
CLOUD_ROOT_DIR=cloud_server
CLOUD_INSTALL_SUBDIR=install-dir

CLOUD_LOCAL_BUILDING_FILE_NAME=build.sh

OS_NAME=linux # could be `macosx`

SVN_OPT=export # could be `co` or `checkout`
KEEP_OLD=no

BOOST_ROOT_DIR=boost_libraries
BOOST_INSTALL_SUBDIR=install-dir
BOOST_SETUP_FILE_NAME=boost_net_setup.sh

OPENSSL_ROOT_DIR=openssl_libraries
OPENSSL_INSTALL_SUBDIR=install-dir
OPENSSL_SETUP_FILE_NAME=openssl_net_setup.sh

OPENCV_ROOT_DIR=opencv_libraries
OPENCV_INSTALL_SUBDIR=install-dir
OPENCV_SETUP_FILE_NAME=opencv_net_setup.sh

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

PREMAKE_SETUP_FILE_NAME=premake_net_setup.sh


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

# OpenCV
if [ ! -e $CMAKE_PATH ]; then
	echo_run wget $CMAKE_SETUP_FILE_WEB_PATH
	echo_run chmod u+x ./$CMAKE_SETUP_FILE_NAME
	echo_run ./$CMAKE_SETUP_FILE_NAME
fi

load $OPENCV_DISTRO_NAME $OPENCV_ROOT_DIR $OPENCV_NAME $OPENCV_VERSION $OPENCV_DISTRO_SITE $OPENCV_INSTALL_SUBDIR $OPENCV_PROJECT_URL

cd $OPENCV_ROOT_DIR
if [ -d ./OpenCV-2.3.1 ]; then
 mv -f ./OpenCV-2.3.1/* `pwd`
 rm -rf OpenCV-2.3.1
fi

echo_run ../$CMAKE_PATH -DCMAKE_INSTALL_PREFIX=./$OPENCV_INSTALL_SUBDIR -DBUILD_SHARED_LIBS=ON -DBUILD_PYTHON_SUPPORT=OFF -DOPENCV_EXTRA_C_FLAGS=-fPIC -DOPENCV_BUILD_3RDPARTY_LIBS=TRUE
make
make install

cd ..

if [ ! -e $BOOST_SETUP_FILE_NAME ]; then
	echo_run wget http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$BOOST_SETUP_FILE_NAME
	echo_run chmod u+x $BOOST_SETUP_FILE_NAME
fi

echo_run ./$BOOST_SETUP_FILE_NAME $BOOST_ROOT_DIR $BOOST_INSTALL_SUBDIR

if [ ! -e $OPENSSL_SETUP_FILE_NAME ]; then
	echo_run wget http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$OPENSSL_SETUP_FILE_NAME
	echo_run chmod u+x $OPENSSL_SETUP_FILE_NAME
fi

echo_run ./$OPENSSL_SETUP_FILE_NAME $OPENSSL_ROOT_DIR $OPENSSL_INSTALL_SUBDIR

if [ ! -e $PREMAKE_SETUP_FILE_NAME ]; then
	echo_run wget http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$PREMAKE_SETUP_FILE_NAME
	echo_run chmod u+x $PREMAKE_SETUP_FILE_NAME
fi

echo_run ./$PREMAKE_SETUP_FILE_NAME 

cd $CLOUD_COMPONENT_NAME

if [ ! -e $CLOUD_LOCAL_BUILDING_FILE_NAME ]; then
	echo_run echo ../premake-4.3/bin/release/premake4 --os=$OS_NAME --BoostLibsPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib  --OpenCVLibsPath=../$OPENCV_ROOT_DIR/$OPENCV_INSTALL_SUBDIR/lib --OpenSSLLibsPath=../$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/lib  --BoostIncludesPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/include  --OpenCVIncludesPath=../$OPENCV_ROOT_DIR/$OPENCV_INSTALL_SUBDIR/include --OpenSSLIncludesPath=../$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/include --OpenCVshared=1  --platform=x32 gmake > $CLOUD_LOCAL_BUILDING_FILE_NAME
	echo_run chmod u+x ./$CLOUD_LOCAL_BUILDING_FILE_NAME
fi

echo_run ./$CLOUD_LOCAL_BUILDING_FILE_NAME

cd projects/$OS_NAME-gmake

echo_run make config=release

if [ ! -d ../../../$CLOUD_INSTALL_SUBDIR/lib_boost ]; then
	echo_run mkdir ../../../$CLOUD_INSTALL_SUBDIR/lib_boost
	echo_run cp -r ../../../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib/* ../../../$CLOUD_INSTALL_SUBDIR/lib_boost/
	
	echo_run mkdir ../../../$CLOUD_INSTALL_SUBDIR/lib_opencv
	echo_run cp -r ../../../$OPENCV_ROOT_DIR/$OPENCV_INSTALL_SUBDIR/lib/* ../../../$CLOUD_INSTALL_SUBDIR/lib_opencv/
fi

echo_run cp -r ./bin/release/* ../../../$CLOUD_INSTALL_SUBDIR/
cd ../../../
export LD_LIBRARY_PATH=./:./lib_boost/:./lib_opencv/
echo -------------------------------------------------------------------------------
echo DO NOT FORGET TO CALL "export LD_LIBRARY_PATH=./:./lib_boost/:./lib_opencv/"
echo Done!

exit 0
