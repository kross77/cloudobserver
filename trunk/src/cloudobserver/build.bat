@SET PATH=%VS90COMNTOOLS%..\IDE
devenv /build release cloudobserver.sln
mkdir bin
for /r %%i in (CloudObserver*Library.dll) do copy /y %%i bin
for /r %%i in (*.exe) do copy /y %%i bin
copy /y CloudObserverWebsite\index.html bin
copy /y CloudObserverWebsite\ClientBin\CloudObserverUserInterface.xap bin