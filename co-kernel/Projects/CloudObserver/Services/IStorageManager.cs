using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface IStorageManager
    {
        [OperationContract]
        void Test();
    }
}