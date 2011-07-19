#!/bin/bash

PREMAKE_DISTRO_SITE=surfnet.dl.sourceforge.net
PREMAKE_NAME=premake-4.3-src
PREMAKE_VERSION=4.3
PREMAKE_DISTRO_NAME="$PREMAKE_NAME".zip
PREMAKE_ROOT_DIR=premake

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

WD=`pwd`
MACHINE=`uname`
HERE=`dirname $0`

cd $HERE

if [ "$1" != "" ]; then
	PREMAKE_DISTRO_SITE="$1"
fi

if [ ! -e $PREMAKE_DISTRO_NAME ]; then
	# get boost
	echo_run ${CURL_CMD} http://$PREMAKE_DISTRO_SITE/project/premake/Premake/$PREMAKE_VERSION/$PREMAKE_DISTRO_NAME -o $PREMAKE_DISTRO_NAME
fi

if [ ! -d premake-4.3/bin/release ]; then
	# move the boost distro into place
	echo_run unzip $PREMAKE_DISTRO_NAME
	
	cd ./premake-4.3/build/gmake.unix
	
	echo_run make config=release
fi

echo Done!

exit 0;
