@echo off

echo Starting AccountsService...
start "Accounts Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host AccountsService %cd%\bin\CloudObserver.Services.AccountsService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%