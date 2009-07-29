using System;
using System.IO;

namespace CloudObserverStorageLibrary
{
    public class CloudObserverStorage
    {
        private readonly string baseAddress;

        public CloudObserverStorage() : this(@"C:\CloudObserverStorage\") { }

        public CloudObserverStorage(string baseAddress)
        {
            this.baseAddress = baseAddress;
        }

        public void SaveIntoStorage(string path, byte[] data)
        {
            File.WriteAllBytes(baseAddress + path, data);
        }

        public byte[] GetFromStorage(string path)
        {
            return File.ReadAllBytes(baseAddress + path);
        }
    }
}