#!/bin/bash

#use script_name.sh /absolute/or/relative/folder/to/install/docs/into/
LOCAL_REV=0
LOADER_REV=0
REMOTE_REPO="http://cloudobserver.googlecode.com/svn"
REBUILD_LIBRARIES=0
COUNTER=0

args=("$@")

CLOUD_COMPONENT_NAME=CloudServer
CLOUD_ROOT_DIR=cloud_server_docs
export LC_MESSAGES=C
WD=`pwd`
MACHINE=`uname`
HERE=`dirname $0`

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

while [  $COUNTER -lt 1 ]; do

        REMOTE_REV=`svn info $REMOTE_REPO | grep '^Revision:' | awk '{print $2}'`
        if [[ $REMOTE_REV != $LOCAL_REV ]] ; then
                echo $REMOTE_REV

                LOCAL_REV=$REMOTE_REV

				cd $HERE
				
				if [ ! -d $CLOUD_ROOT_DIR ]; then
				        run mkdir -p $CLOUD_ROOT_DIR
				fi
				
				cd $CLOUD_ROOT_DIR
                
                run rm -rf $CLOUD_COMPONENT_NAME/
        		run svn checkout $REMOTE_REPO/trunk/$CLOUD_COMPONENT_NAME/ $CLOUD_COMPONENT_NAME
                
                run cd $CLOUD_COMPONENT_NAME/documentation/
                run doxygen
                
                run cd $WD
                
                if [ ! -d ${args[0]} ]; then
				        run mkdir -p ${args[0]}
				fi
                
                run cp -rf $CLOUD_ROOT_DIR/$CLOUD_COMPONENT_NAME/documentation/release/html/ ${args[0]}
                
        fi
        sleep  300
done