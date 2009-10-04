@echo off

echo Starting John Kitto Community College MJPEG Camera broadcast...
start "John Kitto Community College MJPEG Camera broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 10 15 %CloudObserverController% MJPEG http://146.176.65.10/axis-cgi/mjpg/video.cgi false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%