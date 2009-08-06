using System;
using System.ServiceModel;
using CloudObserver.Storages;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class StorageService : Service, StorageServiceContract
    {
        private Storage storage;

        public StorageService()
        {
            storage = new LocalStorage();
        }

        public StorageService(string baseAddress)
        {
            storage = new LocalStorage(baseAddress);
        }

        public void SaveIntoStorage(string path, byte[] data)
        {
            storage.SaveIntoStorage(path, data);
        }

        public byte[] LoadFromStorage(string path)
        {
            return storage.LoadFromStorage(path);
        }
    }
}