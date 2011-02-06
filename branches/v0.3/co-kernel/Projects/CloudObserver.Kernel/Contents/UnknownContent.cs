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

        private List<Stream> readers;
        private List<Stream> disconnectedReaders;

        public UnknownContent(int id, string contentType, string ipAddress, int receiverPort, int senderPort)
            : base(id, contentType, ipAddress, receiverPort, senderPort)
        {
            readers = new List<Stream>();
            disconnectedReaders = new List<Stream>();
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
                foreach (Stream reader in readers)
                    try
                    {
                        reader.Write(buffer, 0, read);
                    }
                    catch (Exception)
                    {
                        disconnectedReaders.Add(reader);
                    }

                foreach (Stream disconnectedReader in disconnectedReaders)
                    readers.Remove(disconnectedReader);
                disconnectedReaders.Clear();
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
