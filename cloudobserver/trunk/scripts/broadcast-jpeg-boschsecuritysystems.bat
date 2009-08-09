@echo off

echo Starting Bosch Security Systems JPEG Camera broadcast...
start "Bosch Security Systems JPEG Camera broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 9 15 %CloudObserverController% JPEG http://89.106.173.195/snap.jpg true live live
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%