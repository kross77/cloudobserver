using System.Runtime.Serialization;

namespace CloudObserver.Services
{
    [DataContract]
    public enum ServiceType
    {
        [EnumMember]
        CloudController,

        [EnumMember]
        DatabaseManager,

        [EnumMember]
        Gateway,

        [EnumMember]
        ResourceManager,

        [EnumMember]
        StorageManager,

        [EnumMember]
        WorkBlock        
    }
}
