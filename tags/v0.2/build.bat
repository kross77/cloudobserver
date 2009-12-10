@echo off

setlocal

if not defined CloudObserverEnvironment call .\scripts\setenvironment.bat

echo Building Cloud Observer solution. This may take several minutes. Please wait...

%MSVisualStudio% /build release %~dp0src\CloudObserver.sln

echo Done.

endlocal