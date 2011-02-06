@echo off

echo Starting Stuttgart Airport MJPEG Camera 1 broadcast...
start "Stuttgart Airport MJPEG Camera 1 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 5 15 %CloudObserverController% MJPEG http://195.243.185.195/axis-cgi/mjpg/video.cgi?camera=1 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport MJPEG Camera 2 broadcast...
start "Stuttgart Airport MJPEG Camera 2 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 6 15 %CloudObserverController% MJPEG http://195.243.185.195/axis-cgi/mjpg/video.cgi?camera=2 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport MJPEG Camera 3 broadcast...
start "Stuttgart Airport MJPEG Camera 3 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 7 15 %CloudObserverController% MJPEG http://195.243.185.195/axis-cgi/mjpg/video.cgi?camera=3 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting Stuttgart Airport MJPEG Camera 4 broadcast...
start "Stuttgart Airport MJPEG Camera 4 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 8 15 %CloudObserverController% MJPEG http://195.243.185.195/axis-cgi/mjpg/video.cgi?camera=4 false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%