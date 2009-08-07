@echo off

setlocal

echo Starting Cloud Observer (broadcast)...
echo.

if not defined CloudObserverEnvironment call .\scripts\setenvironment.bat

call .\scripts\broadcastairport-jpeg.bat
echo.

call .\scripts\broadcastairport-mjpg.bat
echo.

call .\scripts\broadcastboschsecuritysystems.bat
echo.

call .\scripts\broadcastjkcc.bat
echo.

call .\scripts\broadcastcampus.bat
echo.

echo Done.

endlocal