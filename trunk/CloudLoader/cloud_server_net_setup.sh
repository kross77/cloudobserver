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
	echo_run echo ../premake-4.3/bin/release/premake4 --os=$OS_NAME --BoostLibsPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib  --OpenSSLLibsPath=../$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/lib  --BoostIncludesPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/include --OpenSSLIncludesPath=../$OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/include  --platform=x32 gmake > $CLOUD_LOCAL_BUILDING_FILE_NAME
	echo_run chmod u+x ./$CLOUD_LOCAL_BUILDING_FILE_NAME
fi

echo_run ./$CLOUD_LOCAL_BUILDING_FILE_NAME

cd projects/$OS_NAME-gmake

echo_run make config=release

if [ ! -d ../../../$CLOUD_INSTALL_SUBDIR/lib_boost ]; then
	echo_run mkdir ../../../$CLOUD_INSTALL_SUBDIR/lib_boost
	echo_run cp -r ../../../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib/* ../../../$CLOUD_INSTALL_SUBDIR/lib_boost/
fi

echo_run cp -r ./bin/release/* ../../../$CLOUD_INSTALL_SUBDIR/
cd ../../../
echo -------------------------------------------------------------------------------
echo Done!

exit 0
