using System;
using System.IO;

namespace CloudObserverStorageLibrary
{
    public class CloudObserverStorage
    {
        private readonly string basePath;

        public CloudObserverStorage() : this(System.Environment.GetEnvironmentVariable("windir") + @"\CloudObserverStorage\") { }

        public CloudObserverStorage(string basePath)
        {
            if (!Directory.Exists(basePath)) Directory.CreateDirectory(basePath);
            this.basePath = basePath;
        }

        public void SaveIntoStorage(string path, byte[] data)
        {
            File.WriteAllBytes(basePath + path, data);
        }

        public byte[] GetFromStorage(string path)
        {
            return File.ReadAllBytes(basePath + path);
        }
    }
}