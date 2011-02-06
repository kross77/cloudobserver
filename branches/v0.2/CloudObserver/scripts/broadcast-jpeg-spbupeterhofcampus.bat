@echo off

echo Starting SPBU Peterhof Campus JPEG Camera 1 broadcast...
start "SPBU Peterhof Campus JPEG Camera 1 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 11 1 %CloudObserverController% JPEG http://www.campus.spbu.ru/images/webcam/camera1.jpg false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting SPBU Peterhof Campus JPEG Camera 2 broadcast...
start "SPBU Peterhof Campus JPEG Camera 2 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 12 1 %CloudObserverController% JPEG http://www.campus.spbu.ru/images/webcam/camera2.jpg false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting SPBU Peterhof Campus JPEG Camera 3 broadcast...
start "SPBU Peterhof Campus JPEG Camera 3 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 13 1 %CloudObserverController% JPEG http://www.campus.spbu.ru/images/webcam/camera3.jpg false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting SPBU Peterhof Campus JPEG Camera 4 broadcast...
start "SPBU Peterhof Campus JPEG Camera 4 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 14 1 %CloudObserverController% JPEG http://www.campus.spbu.ru/images/webcam/camera4.jpg false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%

echo Starting SPBU Peterhof Campus JPEG Camera 5 broadcast...
start "SPBU Peterhof Campus JPEG Camera 5 broadcast" /min %CloudObserverBin%\CloudObserver.ConsoleApps.Broadcast 15 1 %CloudObserverController% JPEG http://www.campus.spbu.ru/images/webcam/camera5.jpg false
if not %CloudObserverDelay%==0 %CloudObserverBin%\CloudObserver.ConsoleApps.Delay %CloudObserverDelay%