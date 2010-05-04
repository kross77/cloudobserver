using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Text;

namespace CloudObserver.Services.GW
{
    public class Content
    {
        private const int bufferSize = 8192;
        private const int sleepInterval = 100;

        private TcpListener receiver;
        private Thread receiverThread;
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

        private string contentType;
        public string ContentType
        {
            get { return contentType; }
            set { contentType = value; }
        }

        private List<TcpClient> readers;
        private List<NetworkStream> readersStreams;

        public Content(int contentId, string ipAddress, ref int port)
        {
            receiverAddress = "http://" + ipAddress + ":" + port + "/";
            receiver = new TcpListener(new IPEndPoint(IPAddress.Any, port++));
            receiverThread = new Thread(ReceiverLoop);
            receiverThread.IsBackground = true;

            senderAddress = "http://" + ipAddress + ":" + port + "/";
            sender = new TcpListener(new IPEndPoint(IPAddress.Any, port++));
            senderThread = new Thread(SenderLoop);
            senderThread.IsBackground = true;

            readers = new List<TcpClient>();
            readersStreams = new List<NetworkStream>();
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
                    while (true)
                    {
                        if (writerStream.DataAvailable)
                        {
                            byte[] buffer = new byte[bufferSize];
                            int read = writerStream.Read(buffer, 0, bufferSize);
                            for (int i = 0; i < readersStreams.Count; i++)
                                readersStreams[i].Write(buffer, 0, read);
                        }
                        Thread.Sleep(sleepInterval);
                    }
                }
                catch (Exception)
                {
                }
            }
        }

        private void SenderLoop()
        {
            while (true)
            {
                TcpClient reader = sender.AcceptTcpClient();
                readers.Add(reader);

                NetworkStream readerStream = reader.GetStream();
                readersStreams.Add(readerStream);
                string responseHeader = "HTTP/1.0 200 OK\r\nContent-Type: " + contentType + "\r\nCache-Control: no-cache\r\n\r\n";
                byte[] header = Encoding.UTF8.GetBytes(responseHeader);
                readerStream.Write(header, 0, header.Length);
            }
        }
    }
}
