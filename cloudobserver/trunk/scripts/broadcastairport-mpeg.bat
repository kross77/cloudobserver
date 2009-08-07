@echo off

echo Starting Stuttgart Airport MJPG Camera 1 broadcast...
start "Stuttgart Airport MJPG Camera 1 Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 5 15 %CloudObserverController% MJPG http://195.243.185.195/axis-cgi/mjpg/video.cgi?camera=1 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport MJPG Camera 2 broadcast...
start "Stuttgart Airport MJPG Camera 2 Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 6 15 %CloudObserverController% MJPG http://195.243.185.195/axis-cgi/mjpg/video.cgi?camera=2 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport MJPG Camera 3 broadcast...
start "Stuttgart Airport MJPG Camera 3 Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 7 15 %CloudObserverController% MJPG http://195.243.185.195/axis-cgi/mjpg/video.cgi?camera=3 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport MJPG Camera 4 broadcast...
start "Stuttgart Airport MJPG Camera 4 Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 8 15 %CloudObserverController% MJPG http://195.243.185.195/axis-cgi/mjpg/video.cgi?camera=4 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%