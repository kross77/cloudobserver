@echo off

echo Starting ControllerService...
start "Controller Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host ControllerService %CloudObserverBin%\CloudObserver.Services.ControllerService.dll %CloudObserverIP% %CloudObserverPort% null
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%