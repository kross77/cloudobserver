using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Text;

namespace CloudObserver.Kernel.Contents
{
    public abstract class Content
    {
        private string contentType;
        private byte[] header;
        private byte[] notFoundResponse;

        private TcpListener receiver;
        private Thread receiverThread;
        private bool receiverConnected;
        private string receiverAddress;
        public string ReceiverAddress
        {
            get { return receiverAddress; }
        }

        private TcpListener sender;
        private Thread senderThread;
        private string senderAddress;
        public string SenderAddress
        {
            get { return senderAddress; }
        }

        public Content(int id, string contentType, string ipAddress, int receiverPort, int senderPort)
        {
            this.contentType = contentType;

            string responseHeader = "HTTP/1.0 200 OK\r\nContent-type: " + contentType + "\r\nCache-Control: no-cache\r\n\r\n";
            header = Encoding.UTF8.GetBytes(responseHeader);

            string notFound = "HTTP/1.0 404 Not Found\r\n\r\n";
            notFoundResponse = Encoding.UTF8.GetBytes(notFound);

            receiverAddress = "http://" + ipAddress + ":" + receiverPort + "/";
            receiver = new TcpListener(new IPEndPoint(IPAddress.Any, receiverPort));
            receiverThread = new Thread(ReceiverLoop);
            receiverThread.IsBackground = true;
            receiverConnected = false;

            senderAddress = "http://" + ipAddress + ":" + senderPort + "/";
            sender = new TcpListener(new IPEndPoint(IPAddress.Any, senderPort));
            senderThread = new Thread(SenderLoop);
            senderThread.IsBackground = true;
        }

        public void Open()
        {
            receiver.Start();
            receiverThread.Start();

            sender.Start();
            senderThread.Start();
        }

        public void Close()
        {
            receiver.Stop();
            receiverThread.Abort();

            sender.Stop();
            senderThread.Abort();
        }

        private void ReceiverLoop()
        {
            while (true)
            {
                try
                {
                    TcpClient writer = receiver.AcceptTcpClient();
                    NetworkStream writerStream = writer.GetStream();
                    receiverConnected = true;
                    OnWriterConnected(writerStream);
                }
                catch (Exception)
                {
                    receiverConnected = false;
                    Reset();
                }
            }
        }

        private void SenderLoop()
        {
            while (true)
            {
                try
                {
                    TcpClient reader = sender.AcceptTcpClient();
                    NetworkStream readerStream = reader.GetStream();
                    if (!receiverConnected)
                    {
                        readerStream.Write(notFoundResponse, 0, notFoundResponse.Length);
                        readerStream.Close();
                        continue;
                    }
                    readerStream.Write(header, 0, header.Length);
                    OnReaderConnected(readerStream);
                }
                catch (Exception)
                {
                }
            }
        }

        protected abstract void Reset();

        protected abstract void OnReaderConnected(Stream stream);

        protected abstract void OnWriterConnected(Stream stream);
    }
}
