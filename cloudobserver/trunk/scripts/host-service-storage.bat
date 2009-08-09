@echo off

echo Starting StorageService...
start "Storage Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host StorageService %CloudObserverBin%\CloudObserver.Services.StorageService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%