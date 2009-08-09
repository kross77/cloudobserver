@echo off

echo Starting Local PNG Files Camera broadcast...
start "Local PNG Files Camera broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 17 15 %CloudObserverController% Files %~dp0..\resources\frames\png\000.png %~dp0..\resources\frames\png\001.png %~dp0..\resources\frames\png\002.png %~dp0..\resources\frames\png\003.png %~dp0..\resources\frames\png\004.png %~dp0..\resources\frames\png\005.png %~dp0..\resources\frames\png\006.png %~dp0..\resources\frames\png\007.png
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%