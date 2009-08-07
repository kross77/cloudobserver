@echo off

echo Starting Bosch Security Systems broadcast...
start "Bosch Security Systems Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 10 15 %CloudObserverController% JPEG http://89.106.173.195/snap.jpg true live live
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%