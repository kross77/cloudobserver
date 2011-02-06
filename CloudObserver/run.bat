@echo off

setlocal

echo Starting Cloud Observer...
echo.

if not defined CloudObserverEnvironment call .\scripts\setenvironment.bat

call .\scripts\run-services.bat
echo.

call .\scripts\run-broadcast.bat
echo.

call .\scripts\run-website.bat
echo.

echo Done.

endlocal