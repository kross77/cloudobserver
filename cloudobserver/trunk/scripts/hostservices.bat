@echo off

echo Starting StorageService...
start "Storage Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host StorageService %cd%\bin\CloudObserver.Services.StorageService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting AuthenticationService...
start "Authentication Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host AuthenticationService %cd%\bin\CloudObserver.Services.AuthenticationService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting AccountsService...
start "Accounts Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host AccountsService %cd%\bin\CloudObserver.Services.AccountsService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting BroadcastService...
start "Broadcast Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host BroadcastService %cd%\bin\CloudObserver.Services.BroadcastService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting IPCamerasService...
start "IPCameras Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host IPCamerasService %cd%\bin\CloudObserver.Services.IPCamerasService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%