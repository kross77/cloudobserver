@echo off

setlocal

echo Starting Cloud Observer...
echo.

if not defined CloudObserverEnvironment call .\scripts\setenvironment.bat

echo Step 1: controller start
if '%CloudObserverHostController%'=='true' (
call .\scripts\hostcontroller.bat
) else (
echo ----------skipped----------
)
echo.

echo Step 2: services start
call .\scripts\hostservices.bat
echo.

echo Step 3: services test
if '%CloudObserverTesting%'=='true' (
call .\scripts\testservices.bat
) else (
echo ---------skipped--------
)
echo.

echo Step 4: policies setup
call .\scripts\hostpolicies.bat
echo.

echo Done.

endlocal