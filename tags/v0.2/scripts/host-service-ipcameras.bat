@echo off

echo Starting IPCamerasService...
start "IPCameras Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host IPCamerasService %CloudObserverBin%\CloudObserver.Services.IPCamerasService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%