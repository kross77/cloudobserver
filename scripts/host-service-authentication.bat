@echo off

echo Starting AuthenticationService...
start "Authentication Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host AuthenticationService %CloudObserverBin%\CloudObserver.Services.AuthenticationService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%