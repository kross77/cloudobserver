using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface StorageServiceContract : AbstractServiceContract
    {
        [OperationContract]
        void SaveIntoStorage(string path, byte[] data);

        [OperationContract]
        byte[] LoadFromStorage(string path);
    }
}