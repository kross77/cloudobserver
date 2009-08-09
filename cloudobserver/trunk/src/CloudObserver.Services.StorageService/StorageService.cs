using System;
using System.ServiceModel;
using CloudObserver.Storages;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class StorageService : AbstractService, StorageServiceContract
    {
        private Storage storage;

        public void SetBasePath(string basePath)
        {
            storage = new LocalStorage(basePath);
        }

        public void SaveIntoStorage(string path, byte[] data)
        {
            if (storage == null) storage = new LocalStorage();
            storage.SaveIntoStorage(path, data);
        }

        public byte[] LoadFromStorage(string path)
        {
            if (storage == null) storage = new LocalStorage();
            return storage.LoadFromStorage(path);
        }
    }
}