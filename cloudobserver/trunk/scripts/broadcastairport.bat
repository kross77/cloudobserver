@echo off

echo Starting Stuttgart Airport JPEG Camera 1 broadcast...
start "Stuttgart Airport JPEG Camera 1 Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 11 15 %CloudObserverController% JPEG http://195.243.185.195/axis-cgi/jpg/image.cgi?camera=1 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport JPEG Camera 2 broadcast...
start "Stuttgart Airport JPEG Camera 2 Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 12 15 %CloudObserverController% JPEG http://195.243.185.195/axis-cgi/jpg/image.cgi?camera=2 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport JPEG Camera 3 broadcast...
start "Stuttgart Airport JPEG Camera 3 Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 13 15 %CloudObserverController% JPEG http://195.243.185.195/axis-cgi/jpg/image.cgi?camera=3 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport JPEG Camera 4 broadcast...
start "Stuttgart Airport JPEG Camera 4 Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 14 15 %CloudObserverController% JPEG http://195.243.185.195/axis-cgi/jpg/image.cgi?camera=4 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%