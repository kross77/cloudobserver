using System;
using System.Runtime.Serialization;

namespace CloudObserver.Services
{
    [DataContract]
    public enum ServiceType
    {
        ControllerService = 0,
        AuthenticationService = 1,
        AccountsService = 2,
        BroadcastService = 3,
        StorageService = 4,
        VirtualCamerasService = 5,
    }
}