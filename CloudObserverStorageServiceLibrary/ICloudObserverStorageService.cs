using System;
using System.ServiceModel;

namespace CloudObserverStorageServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverStorageService
    {
        [OperationContract]
        void SaveIntoStorage(string path, byte[] data);

        [OperationContract]
        byte[] GetFromStorage(string path);
    }
}