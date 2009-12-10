@echo off

echo Starting TestSoundService...
start "Test Sound Service Host" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Host TestSoundService %CloudObserverBin%\CloudObserver.Services.TestSoundService.dll %CloudObserverIP% %CloudObserverPort% %CloudObserverController%
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%