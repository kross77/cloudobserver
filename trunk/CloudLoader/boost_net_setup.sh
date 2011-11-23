#!/bin/bash

BOOST_DISTRO_SITE=surfnet.dl.sourceforge.net
BOOST_PROJECT_URL=project/boost/boost
BOOST_NAME=boost_1_48_0
BOOST_VERSION=1.48.0
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



KEEP_OLD="true"

echo API: boost_net_setup.sh BOOST_ROOT_DIR BOOST_INSTALL_SUBDIR KEEP_OLD BOOST_VERSION BOOST_NAME BOOST_DISTRO_SITE
echo Warning: This script shall be executed from a path that contains no spaces or non English latters!

if [ "$1" != "" ]; then
	BOOST_ROOT_DIR="$1"
fi

if [ "$2" != "" ]; then
	BOOST_INSTALL_SUBDIR="$2"
fi

if [ "$3" != "" ]; then
	KEEP_OLD="$3"
fi

if [ "$4" != "" ]; then
	BOOST_VERSION="$4"
fi

if [ "$5" != "" ]; then
	BOOST_NAME="$5"
fi

if [ "$6" != "" ]; then
	BOOST_DISTRO_SITE="$6"
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

extract() # 1=DISTRO_NAME 2=ROOT_DIR 3=NAME
{
	echo_run tar -xzf $1
	echo_run rm -rf $2
	echo_run mv $3 $2
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

cd $HERE

if [ ! -d ./$ALTERNATIVE_ZLIB_FOLDER ]; then
	load $ZLIB_DISTRO_NAME $ZLIB_ROOT_DIR $ZLIB_NAME $ZLIB_VERSION $BOOST_DISTRO_SITE $ZLIB_INSTALL_SUBDIR $ZLIB_PROJECT_URL
else
ZLIB_ROOT_DIR="$ALTERNATIVE_ZLIB_FOLDER"
fi

load $BOOST_DISTRO_NAME $BOOST_ROOT_DIR $BOOST_NAME $BOOST_VERSION $BOOST_DISTRO_SITE $BOOST_INSTALL_SUBDIR $BOOST_PROJECT_URL
cd $BOOST_ROOT_DIR

echo_run ./bootstrap.sh

echo_run ./b2 -j4 -d0 --with-thread --with-system --with-filesystem --with-program_options --with-regex --with-date_time --with-iostreams -sZLIB_SOURCE="$WD"/"$ZLIB_ROOT_DIR"/ -sNO_BZIP2=1  link=shared --prefix=./$BOOST_INSTALL_SUBDIR release --builddir=./$BOOST_COMPILE_SUBDIR install

echo Done!

exit 0;