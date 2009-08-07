@echo off

setlocal

echo Starting Cloud Observer (client)...
echo.

if not defined CloudObserverEnvironment call .\scripts\setenvironment.bat

CloudObserver.html
echo.

echo Done.

endlocal