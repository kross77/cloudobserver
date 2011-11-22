#!/bin/bash

CMAKE_DISTRO_SITE=www.cmake.org
CMAKE_PROJECT_URL=files
CMAKE_NAME=cmake-2.8.6
CMAKE_VERSION=v2.8
CMAKE_DISTRO_NAME="$CMAKE_NAME".tar.gz
CMAKE_ROOT_DIR=cmake
CMAKE_INSTALL_SUBDIR=install-dir
CMAKE_COMPILE_SUBDIR=build-dir

KEEP_OLD="true"

echo Warning: This script shall be executed from a path that contains no spaces or non English latters!

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

load $CMAKE_DISTRO_NAME $CMAKE_ROOT_DIR $CMAKE_NAME $CMAKE_VERSION $CMAKE_DISTRO_SITE $CMAKE_INSTALL_SUBDIR $CMAKE_PROJECT_URL
cd $CMAKE_ROOT_DIR

echo_run ./bootstrap --prefix=./$CMAKE_INSTALL_SUBDIR; 
echo_run make
echo_run make install

echo Done!

exit 0;
