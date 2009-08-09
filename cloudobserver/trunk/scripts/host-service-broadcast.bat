@echo off

echo Starting BroadcastService...
start "Broadcast Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host BroadcastService %CloudObserverBin%\CloudObserver.Services.BroadcastService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%