@echo off
echo Building Cloud Observer solution. This may take several minutes. Please wait...
"C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe" /build release src\CloudObserver.sln
copy src\CloudObserver.UserInterface\bin\Release\CloudObserver.UserInterface.xap .