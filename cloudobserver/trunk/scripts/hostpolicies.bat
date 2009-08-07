@echo off

echo Hosting policies..
start "Policies Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Policies %CloudObserverIP% %CloudObserverPort%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%