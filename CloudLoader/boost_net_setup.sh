#!/bin/bash

BOOST_DISTRO_SITE=surfnet.dl.sourceforge.net
BOOST_NAME=boost_1_47_0
BOOST_VERSION=1.47.0
BOOST_DISTRO_NAME="$BOOST_NAME".tar.gz
BOOST_ROOT_DIR=boost_libraries
BOOST_INSTALL_SUBDIR=install-dir
BOOST_COMPILE_SUBDIR=build-dir

KEEP_OLD="true"

echo API: boost_net_setup.sh BOOST_ROOT_DIR BOOST_INSTALL_SUBDIR KEEP_OLD BOOST_VERSION BOOST_NAME BOOST_DISTRO_SITE

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

extract_and_clean()
{
	echo_run tar -xzf $BOOST_DISTRO_NAME
	echo_run rm -rf $BOOST_ROOT_DIR
	echo_run mv $BOOST_NAME $BOOST_ROOT_DIR
	
	if [ -d $BOOST_INSTALL_SUBDIR ]; then
		echo_run rm -rf $BOOST_INSTALL_SUBDIR
		echo_run mkdir $BOOST_INSTALL_SUBDIR
	fi
	if [ ! -d $BOOST_INSTALL_SUBDIR ]; then
		echo_run mkdir $BOOST_INSTALL_SUBDIR
	fi
	if [ -d $BOOST_COMPILE_SUBDIR ]; then
		echo_run rm -rf $BOOST_COMPILE_SUBDIR
		echo_run mkdir $BOOST_COMPILE_SUBDIR
	fi
	if [ ! -d $BOOST_COMPILE_SUBDIR ]; then
		echo_run mkdir $BOOST_COMPILE_SUBDIR
	fi
	
	cd $BOOST_ROOT_DIR

	echo_run ./bootstrap.sh

	echo_run ./bjam -j4 link=shared --builddir=./$BOOST_COMPILE_SUBDIR install --without-mpi --without-chrono --without-exception --without-graph --without-graph_parallel --without-iostreams --without-wave --without-python --prefix=./$BOOST_INSTALL_SUBDIR
	# or call # echo_run ./bjam -j4 link=static threading=single,multi --builddir=./$BOOST_COMPILE_SUBDIR install --with-mpi --without-python  --prefix=./$BOOST_INSTALL_SUBDIR
}


WD=`pwd`
MACHINE=`uname`
HERE=`dirname $0`

cd $HERE

if [ ! -e $BOOST_DISTRO_NAME ]; then
	# get boost
	echo_run ${CURL_CMD} http://$BOOST_DISTRO_SITE/project/boost/boost/$BOOST_VERSION/$BOOST_DISTRO_NAME -o $BOOST_DISTRO_NAME
fi
  
if [ ! -d $BOOST_ROOT_DIR ]; then
	echo_run mkdir $BOOST_ROOT_DIR
fi

# move the boost distro into place
if [ ! -d $BOOST_ROOT_DIR/$BOOST_INSTALL_SUBDIR/lib ]; then
	extract_and_clean
else
	if [ ! KEEP_OLD=="true" ]; then
		extract_and_clean
	fi
fi

echo Done!

exit 0;
