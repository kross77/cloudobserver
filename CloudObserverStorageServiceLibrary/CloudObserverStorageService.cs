using System;
using CloudObserverStorageLibrary;

namespace CloudObserverStorageServiceLibrary
{
    public class CloudObserverStorageService : ICloudObserverStorageService
    {
        private CloudObserverStorage storage;

        public CloudObserverStorageService()
        {
            storage = new CloudObserverStorage();
        }

        public CloudObserverStorageService(string baseAddress)
        {
            storage = new CloudObserverStorage(baseAddress);
        }

        public void SaveIntoStorage(string path, byte[] data)
        {
            storage.SaveIntoStorage(path, data);
        }

        public byte[] GetFromStorage(string path)
        {
            return storage.GetFromStorage(path);
        }
    }
}