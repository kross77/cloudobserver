#!/bin/bash
LOCAL_REV=0
LOADER="cloud-loader-linux.sh"
LOADER_URL="http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$LOADER"
REMOTE_REPO="http://cloudobserver.googlecode.com/svn/"
REBUILD_LIBRARIES=0
RUN_DIR="./cloud_server/run_dir/"
CF_SERVER_INSTALL_DIR="./cloud_server/install-dir/"
ROBOT1_NAME=RobotAlpha
ROBOT2_NAME=RobotBeta
CD=`pwd`

export LC_MESSAGES=C

kill `ps aux | grep -F 'CloudServer' | grep -v -F 'grep' | awk '{ print $2 }'` 
kill `ps aux | grep -F '$ROBOT1_NAME' | grep -v -F 'grep' | awk '{ print $2 }'`
kill `ps aux | grep -F '$ROBOT2_NAME' | grep -v -F 'grep' | awk '{ print $2 }'`

if [ ! -d "$RUN_DIR" ]; then
	mkdir -p $RUN_DIR
fi

if [ -d "$CF_SERVER_INSTALL_DIR" ]; then
	cp -r $CF_SERVER_INSTALL_DIR* $RUN_DIR
	cd $RUN_DIR
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
			REBUILD_LIBRARIES=1
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
		kill `ps aux | grep -F '$ROBOT1_NAME' | grep -v -F 'grep' | awk '{ print $2 }'`
		kill `ps aux | grep -F '$ROBOT2_NAME' | grep -v -F 'grep' | awk '{ print $2 }'`
		cp -rf $CF_SERVER_INSTALL_DIR* $RUN_DIR
		cd $RUN_DIR
		nohup ./CloudServer >& /dev/null &
		sleep 5
		
		PID=`ps aux |grep CloudServer|grep -v grep| head -n 1 |awk '{print $2}'`

		while [ `top -n 1 -b -p $PID | grep $PID |awk '{print $9"/1"}' |bc` -gt 1 ]
		do
			echo Server still starting up ...
			sleep 5
		done
		
		nohup ./CloudClient --server=localhost:4773 --robot --username=$ROBOT1_NAME >& /dev/null &
		nohup ./CloudClient --server=localhost:4773 --robot --username=$ROBOT2_NAME >& /dev/null &
		cd $CD
		
	fi
	sleep  250
done

