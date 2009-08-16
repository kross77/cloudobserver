@echo off

echo Starting Cloud Observer Broadcast...
echo.

if not defined CloudObserverEnvironment call %~dp0setenvironment.bat

call %~dp0broadcast-jpeg-stuttgartairport.bat
echo.

call %~dp0broadcast-mjpeg-stuttgartairport.bat
echo.

call %~dp0broadcast-jpeg-boschsecuritysystems.bat
echo.

call %~dp0broadcast-mjpeg-johnkittocommunitycollege.bat
echo.

call %~dp0broadcast-jpeg-spbupeterhofcampus.bat
echo.

call %~dp0broadcast-jpeg-localfiles.bat
echo.

call %~dp0broadcast-png-localfiles.bat
echo.

echo Done.