#!/bin/sh

revision=`svnversion`
version=0.4.0.$revision
target=cloudobserver-$version

executable=./CloudObserver/bin/Release/CloudObserver.exe
if [ ! -f $executable ]; then
	echo "No executable found. You should first build the Cloud Observer project in release configuration with Mono."
	exit 1
fi

if [ -f $target.tar.gz ]; then
	rm $target.tar.gz
fi

mkdir $target
cp $executable $target
cp ./CloudObserver/start.sh $target
cp ./CloudObserver/stop.sh $target
chmod a+x $target/start.sh $target/stop.sh
cp -r ./CloudObserverInstaller/htdocs $target
tar -czf $target.tar.gz --exclude-vcs $target
rm -fr $target

exit 0
