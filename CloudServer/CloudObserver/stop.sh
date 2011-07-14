#!/bin/sh

lock_file=/tmp/CloudObserver.exe.lock

if [ -f $lock_file ]
then
	kill `cat < $lock_file`
fi
