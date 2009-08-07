using System;
using System.IO;

namespace CloudObserver.Storages
{
    public class LocalStorage : Storage
    {
        private string basePath;

        public LocalStorage() : this(System.Environment.GetEnvironmentVariable(@"D:\fchunovkin\share\CloudObserver\storage")) { }

        public LocalStorage(string basePath)
        {
            if (!Directory.Exists(basePath)) Directory.CreateDirectory(basePath);
            this.basePath = basePath;
        }

        public override void SaveIntoStorage(string path, byte[] data)
        {
            string absolutePath = basePath + path;
            if (!Directory.Exists(absolutePath)) Directory.CreateDirectory(absolutePath);
            File.WriteAllBytes(absolutePath, data);
        }

        public override byte[] LoadFromStorage(string path)
        {
            return File.ReadAllBytes(basePath + path);
        }
    }
}