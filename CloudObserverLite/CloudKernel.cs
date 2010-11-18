using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace CloudObserverLite
{
    public class CloudKernel
    {
        private TcpListener listener;
        private Thread thread;
        private ushort port;
        private uint clientsCount = 0;
        private LogWriter logWriter;

        public CloudKernel(ushort port)
        {
            this.port = port;

            this.logWriter = LogWriter.GetInstance();
        }

        public void Listen()
        {
            this.listener = new TcpListener(IPAddress.Any, this.port);
            this.listener.Start();
            this.logWriter.WriteLog("Server started. Waiting for connections...");

            while (true)
            {
                try
                {
                    CloudClient client = new CloudClient(++this.clientsCount, this.listener.AcceptTcpClient());
                    Thread clientThread = new Thread(new ThreadStart(client.Process));
                    clientThread.Name = "Client " + this.clientsCount.ToString();
                    clientThread.IsBackground = true;
                    clientThread.Start();
                }
                catch (Exception)
                {
                }
            }
        }

        public void Start()
        {
            this.thread = new Thread(new ThreadStart(this.Listen));
            this.thread.Name = "Server";
            this.thread.IsBackground = true;
            this.thread.Start();
        }

        public void Stop()
        {
            this.listener.Stop();
            this.logWriter.WriteLog("Server stopped.");
            this.logWriter.Close();

            this.thread.Abort();
        }
    }
}
