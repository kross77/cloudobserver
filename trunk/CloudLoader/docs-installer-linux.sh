#!/bin/bash

LOCAL_REV=0
LOADER_REV=0
REMOTE_REPO="http://cloudobserver.googlecode.com/svn"
REBUILD_LIBRARIES=0
COUNTER=0
CLOUD_COMPONENT_NAME=CloudServer
CLOUD_ROOT_DIR=cloud_server_docs
export LC_MESSAGES=C
WD=`pwd`
MACHINE=`uname`
HERE=`dirname $0`

if [ "$1" = "" ]
then
	echo "Usage: $0 <url to extract doxygen generated docs into>"
	exit
fi

while [  $COUNTER -lt 1 ]; do

        REMOTE_REV=`svn info $REMOTE_REPO | grep '^Revision:' | awk '{print $2}'`
        if [[ $REMOTE_REV != $LOCAL_REV ]] ; then
                echo $REMOTE_REV

                LOCAL_REV=$REMOTE_REV

				cd $HERE
				
				if [ ! -d $CLOUD_ROOT_DIR ]; then
				        mkdir -p $CLOUD_ROOT_DIR
				fi
				
				cd $CLOUD_ROOT_DIR
                
                rm -rf $CLOUD_COMPONENT_NAME/
        		svn checkout $REMOTE_REPO/trunk/$CLOUD_COMPONENT_NAME/ $CLOUD_COMPONENT_NAME
                
                cd $CLOUD_COMPONENT_NAME/documentation/

                doxygen
                cd release/latex/
                
				pdflatex refman.tex
				makeindex refman.idx
				pdflatex refman.tex
				mv -f refman.pdf cloud_observer_cpp_docs.pdf
                
                cd $WD
                
                if [ ! -d $1 ]; then
				        mkdir -p $1
				fi
                
                cp -rf $CLOUD_ROOT_DIR/$CLOUD_COMPONENT_NAME/documentation/release/html/ $1
                cp -f $CLOUD_ROOT_DIR/$CLOUD_COMPONENT_NAME/documentation/release/latex/cloud_observer_cpp_docs.pdf $1
                
        fi
        sleep  300
done