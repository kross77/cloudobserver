@echo off

setlocal

echo Starting Cloud Observer (broadcast)...
echo.

if not defined CloudObserverEnvironment call .\scripts\setenvironment.bat

call .\scripts\broadcastboschsecuritysystems.bat
echo.

call .\scripts\broadcastairport.bat
echo.

call .\scripts\broadcastcampus.bat
echo.

echo Done.

endlocal