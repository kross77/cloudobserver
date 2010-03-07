using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class StorageManager : IStorageManager
    {
        public void Test()
        {
        }
    }
}