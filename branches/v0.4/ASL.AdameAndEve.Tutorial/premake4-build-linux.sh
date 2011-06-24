#!/bin/sh
chmod a+x premake4
./premake4 --os=linux  --platform=x32 gmake
#./premake4 --os=linux  --platform=x32 codeblocks
exit 0
