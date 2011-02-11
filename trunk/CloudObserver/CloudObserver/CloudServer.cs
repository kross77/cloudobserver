using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.ServiceProcess;
using System.Threading;
using CloudObserver.Properties;

namespace CloudObserver
{
    public sealed class CloudServer : ServiceBase
    {
        public const string SERVICE_NAME = "Cloud Observer";

        private TcpListener listener;
        private Thread thread;
        private uint clientsCount = 0;

        public Hashtable streams = new Hashtable();

        public CloudServer()
        {
            this.ServiceName = SERVICE_NAME;
        }

        private void Listen()
        {
            this.listener = new TcpListener(IPAddress.Any, Settings.Default.ServerPort);
            this.listener.Start();
            this.EventLog.WriteEntry("Server started. Waiting for connections...");

            while (true)
            {
                try
                {
                    CloudClient client = new CloudClient(this, ++this.clientsCount, this.listener.AcceptTcpClient());
                    Thread clientThread = new Thread(new ThreadStart(client.Process));
                    clientThread.Name = "Client " + this.clientsCount.ToString();
                    clientThread.IsBackground = true;
                    clientThread.Start();
                }
                catch (Exception exception)
                {
                    this.EventLog.WriteEntry(exception.ToString());
                }
            }
        }

        protected override void OnStart(string[] args)
        {
            this.thread = new Thread(new ThreadStart(this.Listen));
            this.thread.Name = "Server";
            this.thread.IsBackground = true;
            this.thread.Start();
        }

        protected override void OnStop()
        {
            this.listener.Stop();
            this.thread.Abort();
        }

        public static void Main()
        {
            ServiceBase.Run(new CloudServer());
        }
    }
}
