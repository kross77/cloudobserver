#!/bin/bash
LOCAL_REV=0
LOADER="cloud-loader-linux.sh"
LOADER_URL="http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$LOADER"
LOADER_REV=0
REMOTE_REPO="http://cloudobserver.googlecode.com/svn/"
REBUILD_LIBRARIES=0
CD=`pwd`
COUNTER=0

export LC_MESSAGES=en_US

while [  $COUNTER -lt 1 ]; do

	REMOTE_REV=`svn info $REMOTE_REPO | grep '^Revision:' | awk '{print $2}'`
	if [[ $REMOTE_REV != $LOCAL_REV ]] ; then
		echo $REMOTE_REV
		REMOTE_LOADER_REV=`svn info $LOADER_URL | grep '^Last Changed Rev:' | awk '{print $4}'`
		if [[ $REMOTE_LOADER_REV != $LOADER_REV ]] ; then			
			REBUILD_LIBRARIES=1
			echo $REMOTE_LOADER_REV
			LOADER_REV=$REMOTE_LOADER_REV
			wget -q $LOADER_URL -O $LOADER
			chmod u+x $LOADER
		fi
		LOCAL_REV=$REMOTE_REV
		kill `ps aux | grep -F 'CloudServer' | grep -v -F 'grep' | awk '{ print $2 }'` 
		
		if [ "$REBUILD_LIBRARIES" == "1" ]; then
			./$LOADER no yes
			REBUILD_LIBRARIES=0
		else
			./$LOADER.sh
		fi
		
		cd ./cloud_server/install-dir/
		nohup ./CloudServer >& /dev/null &
		cd ./htdocs/js/
		echo  "\$(document).ready(function() {\$('#rol').after('. Revision "  $LOCAL_REV  "');});" >> cf.js
		cd $CD
		
	fi
	sleep  300
done
