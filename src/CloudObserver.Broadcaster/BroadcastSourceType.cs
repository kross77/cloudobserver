using System;

namespace CloudObserver.Broadcaster
{
    public enum BroadcastSourceType
    {
        UnknownType = 0,
        LocalStorage = 1,
        CloudObserverCamera = 2,
        IPCamera = 3,
    }
}