@echo off

echo Starting VirtualCamerasService...
start "VirtualCameras Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host VirtualCamerasService %cd%\bin\CloudObserver.Services.VirtualCamerasService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%