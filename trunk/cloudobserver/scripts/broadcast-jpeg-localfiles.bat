@echo off

echo Starting Local JPEG Files Camera broadcast...
start "Local JPEG Files Camera broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 16 15 %CloudObserverController% Files %~dp0..\resources\frames\jpg\000.jpg %~dp0..\resources\frames\jpg\001.jpg %~dp0..\resources\frames\jpg\002.jpg %~dp0..\resources\frames\jpg\003.jpg %~dp0..\resources\frames\jpg\004.jpg %~dp0..\resources\frames\jpg\005.jpg %~dp0..\resources\frames\jpg\006.jpg %~dp0..\resources\frames\jpg\007.jpg
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%