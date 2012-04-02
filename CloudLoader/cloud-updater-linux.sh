#!/bin/bash
LOCAL_REV=0
LOADER="cloud-loader-linux.sh"
LOADER_URL="http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$LOADER"
REMOTE_REPO="http://cloudobserver.googlecode.com/svn/"
REBUILD_LIBRARIES=false
RUN_DIR="./run_dir/"
CF_SERVER_INSTALL_DIR="./install-dir/"
ROBOT1_NAME=RobotAlpha
ROBOT2_NAME=RobotBeta
CD=`pwd`

export LC_MESSAGES=C

kill `ps aux | grep -F 'CloudServer' | grep -v -F 'grep' | awk '{ print $2 }'` 
kill `ps aux | grep -F '$ROBOT1_NAME' | grep -v -F 'grep' | awk '{ print $2 }'`
kill `ps aux | grep -F '$ROBOT2_NAME' | grep -v -F 'grep' | awk '{ print $2 }'`

if [ ! -e ./$LOADER ]; then
	wget $LOADER_URL
	chmod u+x $LOADER
fi

if [ ! -d "$RUN_DIR" ]; then
	mkdir -p $RUN_DIR
fi

if [ -d "$CF_SERVER_INSTALL_DIR" ]; then
	cp -r $CF_SERVER_INSTALL_DIR* $RUN_DIR
	cd $RUN_DIR
	
	LOCAL_REV=$(cat htdocs/js/cf.js | grep 'Revision')
	LOCAL_REV=${LOCAL_REV#"\$(document).ready(function() {\$('#rol').after('. Revision "}
	LOCAL_REV=${LOCAL_REV%$(echo "');});")}
	echo $LOCAL_REV
	
	nohup ./CloudServer >& /dev/null &
	sleep 5
	nohup ./CloudClient --server=localhost:4773 --robot --username=$ROBOT1_NAME >& /dev/null &
	nohup ./CloudClient --server=localhost:4773 --robot --username=$ROBOT2_NAME >& /dev/null &
	cd $CD
fi

while true; do

	REMOTE_REV=`svn info $REMOTE_REPO | grep '^Revision:' | awk '{print $2}'`
	if [[ $REMOTE_REV != $LOCAL_REV ]] ; then
		echo $REMOTE_REV
		./$LOADER "--check-for-updates"
		if [ $? -eq 1 ]; then
			./$LOADER "--self-update"
			REBUILD_LIBRARIES=true
		fi
		LOCAL_REV=$REMOTE_REV
		
		if $REBUILD_LIBRARIES; then
			./$LOADER --build --checkout-source --rebuild-libraries
			REBUILD_LIBRARIES=false
		else
			./$LOADER --build --checkout-source
		fi
		
		cd $CD
		
		kill `ps aux | grep -F 'CloudServer' | grep -v -F 'grep' | awk '{ print $2 }'` 
		kill `ps aux | grep -F '$ROBOT1_NAME' | grep -v -F 'grep' | awk '{ print $2 }'`
		kill `ps aux | grep -F '$ROBOT2_NAME' | grep -v -F 'grep' | awk '{ print $2 }'`
		cp -rf $CF_SERVER_INSTALL_DIR* $RUN_DIR
		cd $RUN_DIR
		nohup ./CloudServer >& /dev/null &
		sleep 5
		nohup ./CloudClient --server=localhost:4773 --robot --username=$ROBOT1_NAME >& /dev/null &
		nohup ./CloudClient --server=localhost:4773 --robot --username=$ROBOT2_NAME >& /dev/null &
		cd $CD
		
	fi
	sleep  250
done

