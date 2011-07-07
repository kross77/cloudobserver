#!/bin/sh

revision=`svnversion`
version=0.4.0
target_dir=cloudobserver-$version
target=$target_dir.$revision

executable=./CloudObserver/bin/Release/CloudObserver.exe
if [ ! -f $executable ]; then
	echo "No executable found. You should first build the Cloud Observer project in release configuration with Mono."
	exit 1
fi

if [ -f $target.tar.gz ]; then
	rm $target.tar.gz
fi

mkdir $target_dir
cp $executable $target_dir
cp ./CloudObserver/start.sh $target_dir
cp ./CloudObserver/stop.sh $target_dir
chmod a+x $target_dir/start.sh $target_dir/stop.sh
cp -r ./CloudObserverInstaller/htdocs $target_dir
mkdir $target_dir/dumps
tar -czf $target.tar.gz --exclude-vcs $target_dir
rm -fr $target_dir

exit 0
