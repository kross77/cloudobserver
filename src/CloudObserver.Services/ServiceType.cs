using System;
using System.Runtime.Serialization;

namespace CloudObserver.Services
{
    [DataContract]
    public enum ServiceType
    {
        [EnumMember]
        UnknownService = 0,
        [EnumMember]
        ControllerService = 1,
        [EnumMember]
        AuthenticationService = 2,
        [EnumMember]
        AccountsService = 3,
        [EnumMember]
        BroadcastService = 4,
        [EnumMember]
        StorageService = 5,
        [EnumMember]
        IPCamerasService = 6,
    }
}