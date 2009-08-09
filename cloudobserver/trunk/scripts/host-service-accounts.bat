@echo off

echo Starting AccountsService...
start "Accounts Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host AccountsService %CloudObserverBin%\CloudObserver.Services.AccountsService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%