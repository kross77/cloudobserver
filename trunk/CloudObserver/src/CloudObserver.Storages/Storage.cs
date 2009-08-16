using System;

namespace CloudObserver.Storages
{
    public abstract class Storage
    {
        public abstract void SaveIntoStorage(string path, byte[] data);

        public abstract byte[] LoadFromStorage(string path);
    }
}