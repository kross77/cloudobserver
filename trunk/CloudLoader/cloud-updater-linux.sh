#!/bin/bash
LOCAL_REV=0
LOADER="cloud-loader-linux.sh"
LOADER_URL="http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$LOADER"
LOADER_REV=0
REMOTE_REPO="http://cloudobserver.googlecode.com/svn/"
REBUILD_LIBRARIES=0
RUN_DIR="./cloud_server/run_dir/"
CF_SERVER_INSTALL_DIR="./cloud_server/install-dir/"
ROBOT1_NAME=RobotAlpha
ROBOT2_NAME=RobotBeta
CD=`pwd`
COUNTER=0

export LC_MESSAGES=C

kill `ps aux | grep -F 'CloudServer' | grep -v -F 'grep' | awk '{ print $2 }'` 

if [ ! -d "$RUN_DIR" ]; then
	mkdir $RUN_DIR
fi

if [ -d "$CF_SERVER_INSTALL_DIR" ]; then
	cp -r $CF_SERVER_INSTALL_DIR* $RUN_DIR
	cd $RUN_DIR
	nohup ./CloudServer >& /dev/null &
	nohup ./CloudClient --server=localhost --username=$ROBOT1_NAME --robot >& /dev/null &
	nohup ./CloudClient --server=localhost --username=$ROBOT2_NAME --robot >& /dev/null &
	cd $CD
fi

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
		
		if [ "$REBUILD_LIBRARIES" == "1" ]; then
			./$LOADER --checkout-source --rebuild-libraries
			REBUILD_LIBRARIES=0
		else
			./$LOADER --checkout-source
		fi
		
		cd $CD
		
		kill `ps aux | grep -F 'CloudServer' | grep -v -F 'grep' | awk '{ print $2 }'` 
		cp -r $CF_SERVER_INSTALL_DIR* $RUN_DIR
		cd $RUN_DIR
		nohup ./CloudServer >& /dev/null &
		nohup ./CloudClient --server=localhost --username=$ROBOT1_NAME --robot >& /dev/null &
		nohup ./CloudClient --server=localhost --username=$ROBOT2_NAME --robot >& /dev/null &
		cd ./htdocs/js/
		echo  "\$(document).ready(function() {\$('#rol').after('. Revision "  $LOCAL_REV  "');});" >> cf.js
		cd $CD
		
	fi
	sleep  250
done

