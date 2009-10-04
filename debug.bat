@echo off

setlocal

echo Starting Cloud Observer Debugger...
echo.

if not defined CloudObserverEnvironment call .\scripts\setenvironment.bat

call .\scripts\host-controller.bat
echo.

call .\scripts\host-service-testsound.bat
echo.

start .\bin\CloudObserver.Client.exe

echo Done.

endlocal