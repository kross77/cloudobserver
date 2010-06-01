using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Text;

namespace CloudObserver.Kernel.Contents
{
    public class UnknownContent : Content
    {
        private const int bufferSize = 8192;
        private const int sleepInterval = 100;

        private List<Stream> readers;

        public UnknownContent(int id, string contentType, string ipAddress, int receiverPort, int senderPort)
            : base(id, contentType, ipAddress, receiverPort, senderPort)
        {
            readers = new List<Stream>();
        }

        protected override void OnReaderConnected(Stream stream)
        {
            readers.Add(stream);
        }

        protected override void OnWriterConnected(Stream stream)
        {
            byte[] buffer = new byte[bufferSize];
            while (true)
            {
                int read = stream.Read(buffer, 0, bufferSize);
                for (int i = 0; i < readers.Count; i++)
                    readers[i].Write(buffer, 0, read);
                Thread.Sleep(sleepInterval);
            }
        }

        protected override void Reset()
        {
            foreach (Stream reader in readers)
                reader.Close();
            readers.Clear();
        }
    }
}
