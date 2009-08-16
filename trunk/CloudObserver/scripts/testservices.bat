@echo off

%CloudObserverBin%\CloudObserver.ConsoleApps.Test StorageService %CloudObserverController%
%CloudObserverBin%\CloudObserver.ConsoleApps.Test AuthenticationService %CloudObserverController%
%CloudObserverBin%\CloudObserver.ConsoleApps.Test AccountsService %CloudObserverController%
%CloudObserverBin%\CloudObserver.ConsoleApps.Test BroadcastService %CloudObserverController%
%CloudObserverBin%\CloudObserver.ConsoleApps.Test IPCamerasService %CloudObserverController%