#!/bin/bash
LOCAL_REV=0
LOADER="cloud-loader-linux.sh"
LOADER_URL="http://cloudobserver.googlecode.com/svn/trunk/CloudLoader/$LOADER"
REMOTE_REPO="http://cloudobserver.googlecode.com/svn/"
REBUILD_LIBRARIES=false
RUN_DIR="./run_dir/"
CF_SERVER_INSTALL_DIR="./install-dir/"

export LC_MESSAGES=C

if [ ! -e ./$LOADER ]; then
	wget $LOADER_URL
	chmod u+x $LOADER
fi

./$LOADER stop

if [ -d "$CF_SERVER_INSTALL_DIR" ]; then
	./$LOADER deploy
	
	LOCAL_REV=$(cat $RUN_DIR/htdocs/js/cf.js | grep 'Revision')
	LOCAL_REV=${LOCAL_REV#"\$(document).ready(function() {\$('#rol').after('. Revision "}
	LOCAL_REV=${LOCAL_REV%$(echo "');});")}
	echo $LOCAL_REV
	
	./$LOADER start
fi

while true; do

	REMOTE_REV=`svn info $REMOTE_REPO | grep '^Revision:' | awk '{print $2}'`
	if [[ $REMOTE_REV != $LOCAL_REV ]] ; then
		echo $REMOTE_REV
		./$LOADER "check-for-updates"
		if [ $? -eq 1 ]; then
			./$LOADER "self-update"
			REBUILD_LIBRARIES=true
		fi
		LOCAL_REV=$REMOTE_REV
		
		if $REBUILD_LIBRARIES; then
			./$LOADER --checkout-source --rebuild-libraries build
			REBUILD_LIBRARIES=false
		else
			./$LOADER --checkout-source build
		fi
		
		./$LOADER stop
		./$LOADER deploy
		./$LOADER start
		
	fi
	sleep  250
done

