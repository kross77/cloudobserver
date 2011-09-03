@echo off
setlocal enabledelayedexpansion

set quantity=%1
set start_index=%2

if [%quantity%] == [] set quantity=1
if [%start_index%] == [] set start_index=1
set /a end_index=%start_index% + %quantity% - 1

for /l %%i in (%start_index%,1,%end_index%) do (
	set NUMBER=00%%i
	set NUMBER=!NUMBER:~-3!
	start CloudClient --server=localhost --generate-video --disable-audio --video-width=320 --video-height=240 --username=ROBOT!NUMBER!
)
