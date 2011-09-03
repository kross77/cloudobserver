#!/bin/bash

OPENSSL_DISTRO_SITE=www.openssl.org
OPENSSL_NAME=openssl-1.0.0d
OPENSSL_DISTRO_NAME="$OPENSSL_NAME".tar.gz
OPENSSL_ROOT_DIR=openssl_libraries
OPENSSL_INSTALL_SUBDIR=install-dir
OPENSSL_COMPILE_SUBDIR=build-dir

KEEP_OLD="true"

echo API: OPENSSL_net_setup.sh OPENSSL_ROOT_DIR OPENSSL_INSTALL_SUBDIR KEEP_OLD OPENSSL_NAME OPENSSL_DISTRO_SITE

if [ "$1" != "" ]; then
	OPENSSL_ROOT_DIR="$1"
fi

if [ "$2" != "" ]; then
	OPENSSL_INSTALL_SUBDIR="$2"
fi

if [ "$3" != "" ]; then
	KEEP_OLD="$3"
fi


if [ "$4" != "" ]; then
	OPENSSL_NAME="$5"
fi

if [ "$5" != "" ]; then
	OPENSSL_DISTRO_SITE="$6"
fi

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

extract_and_clean()
{
	echo_run tar -xzf $OPENSSL_DISTRO_NAME
	echo_run rm -rf $OPENSSL_ROOT_DIR
	echo_run mv $OPENSSL_NAME $OPENSSL_ROOT_DIR
	
	cd $OPENSSL_ROOT_DIR

	echo_run ./config no-shared 
	echo_run make

	if [ ! -d $OPENSSL_INSTALL_SUBDIR ]; then
		echo_run mkdir $OPENSSL_INSTALL_SUBDIR
		echo_run mkdir $OPENSSL_INSTALL_SUBDIR/lib
		echo_run mkdir $OPENSSL_INSTALL_SUBDIR/include
	fi

	echo_run cp -rL ./include/* ./$OPENSSL_INSTALL_SUBDIR/include/
	echo_run cp ./libcrypto.a ./$OPENSSL_INSTALL_SUBDIR/lib
	echo_run cp ./libssl.a ./$OPENSSL_INSTALL_SUBDIR/lib
}

WD=`pwd`
MACHINE=`uname`
HERE=`dirname $0`

cd $HERE

if [ ! -e $OPENSSL_DISTRO_NAME ]; then
	# get boost
	echo_run ${CURL_CMD} http://$OPENSSL_DISTRO_SITE/source/$OPENSSL_DISTRO_NAME -o $OPENSSL_DISTRO_NAME
fi
  
if [ ! -d $OPENSSL_ROOT_DIR ]; then
	echo_run mkdir $OPENSSL_ROOT_DIR
fi

# move the boost distro into place
if [ ! -d $OPENSSL_ROOT_DIR/$OPENSSL_INSTALL_SUBDIR/lib ]; then
	extract_and_clean
else
	if [ ! KEEP_OLD=="true" ]; then
		extract_and_clean
	fi
fi

echo Done!

exit 0;
