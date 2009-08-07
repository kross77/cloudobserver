@echo off

echo Starting John Kitto Community College broadcast...
start "John Kitto Community College Broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 10 15 %CloudObserverController% MJPG http://146.176.65.10/axis-cgi/mjpg/video.cgi false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%