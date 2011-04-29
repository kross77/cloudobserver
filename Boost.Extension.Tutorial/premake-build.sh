#!/bin/sh
chmod a+x premake4
./premake4 clean
./premake4 --os=linux --BoostIncludesPath="./libs/" --platform=x32 gmake

