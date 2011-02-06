@echo off

echo Starting Cloud Observer Services...
echo.

if not defined CloudObserverEnvironment call %~dp0setenvironment.bat

echo Step 1: controller start
if '%CloudObserverHostController%'=='true' (
call %~dp0host-controller.bat
) else (
echo ----------skipped----------
)
echo.

echo Step 2: services start
call %~dp0host-services.bat
echo.

echo Step 3: services test
if '%CloudObserverTesting%'=='true' (
call %~dp0testservices.bat
) else (
echo ---------skipped--------
)
echo.

echo Step 4: policies setup
call %~dp0setpolicies.bat
echo.

echo Done.