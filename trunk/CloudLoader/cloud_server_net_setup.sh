#!/bin/bash
# requires svn, premake, curl, gcc

CLOUD_DISTRO_SITE=cloudobserver.googlecode.com
CLOUD_COMPONENT_NAME=CloudServer
CLOUD_ROOT_DIR=cloud_server
CLOUD_INSTALL_SUBDIR=install-dir

OS_NAME=linux # could be `macosx`

SVN_OPT=export # could be `co` or `checkout`
BOOST_ROOT_DIR=boost_libraries
BOOST_INSTALL_SUBDIR=install-dir
BOOST_SETUP_FILE_NAME=boost_net_setup.sh

PREMAKE_SETUP_FILE_NAME=premake_net_setup.sh

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

if [ ! -d $CLOUD_COMPONENT_NAME ]; then
    echo_run mkdir $CLOUD_COMPONENT_NAME
fi

echo_run ${SVN_CMD} --force https://$CLOUD_DISTRO_SITE/svn/trunk/$CLOUD_COMPONENT_NAME/ $CLOUD_COMPONENT_NAME

if [ ! -e $BOOST_SETUP_FILE_NAME ]; then
    echo_run wget http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$BOOST_SETUP_FILE_NAME
    echo_run chmod u+x $BOOST_SETUP_FILE_NAME
fi

echo_run ./$BOOST_SETUP_FILE_NAME

if [ ! -e $PREMAKE_SETUP_FILE_NAME ]; then
    echo_run wget http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$PREMAKE_SETUP_FILE_NAME
    echo_run chmod u+x $PREMAKE_SETUP_FILE_NAME
fi

echo_run ./$PREMAKE_SETUP_FILE_NAME

cd $CLOUD_COMPONENT_NAME

echo_run ../premake-4.3/bin/release/premake4 --os=$OS_NAME --BoostLibsPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib --BoostIncludesPath=../$BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/include  --platform=x32 gmake

cd projects/$OS_NAME-gmake

echo_run make config=debug
echo_run make config=release

echo_run mv --force --update ./bin/release ../../../$CLOUD_INSTALL_SUBDIR

echo Done!

exit 0
