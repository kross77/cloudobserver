@echo off

echo Starting Cloud Observer Website...

if not defined CloudObserverEnvironment call %~dp0setenvironment.bat

start %~dp0..\src\CloudObserver.UserInterface\bin\Release\TestPage.html

echo Done.