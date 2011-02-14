#!/bin/sh

executable=./CloudObserver/bin/Release/CloudObserver.exe
if [ ! -f $executable ]; then
	echo "No executable found. You should first build the Cloud Observer project in release configuration with Mono."
	exit 1
fi

if [ -f cloudobserver.tar.gz ]; then
	rm cloudobserver.tar.gz
fi

mkdir cloudobserver
cp $executable cloudobserver/
cp ./CloudObserver/start.sh cloudobserver/
cp ./CloudObserver/stop.sh cloudobserver/
cp -r ./CloudObserverInstaller/htdocs cloudobserver/
tar -czf cloudobserver.tar.gz --exclude-vcs cloudobserver
rm -fr cloudobserver

exit 0
