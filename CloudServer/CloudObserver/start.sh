#!/bin/sh

lock_file=/tmp/CloudObserver.exe.lock

if [ -f $lock_file ]
then
	kill `cat < $lock_file`
fi

if [ -f $lock_file ]
then
	rm $lock_file
fi

mono-service2 CloudObserver.exe
