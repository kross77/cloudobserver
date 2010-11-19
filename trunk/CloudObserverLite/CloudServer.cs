using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace CloudObserverLite
{
    public class CloudServer
    {
        private const string DEFAULT_NAME = "Cloud Observer Lite 1.0.0";
        private const ushort DEFAULT_PORT = 4773;

        private TcpListener listener;
        private Thread thread;

        private string name;
        private ushort port;
        private uint clientsCount;
        private LogWriter logWriter;

        public Hashtable streams;

        public string Name
        {
            get
            {
                return this.name;
            }
        }

        public CloudServer() : this(DEFAULT_NAME, DEFAULT_PORT) { }

        public CloudServer(string name) : this(name, DEFAULT_PORT) { }

        public CloudServer(ushort port) : this(DEFAULT_NAME, port) { }

        public CloudServer(string name, ushort port)
        {
            this.name = name;
            this.port = port;
            this.clientsCount = 0;
            this.logWriter = LogWriter.GetInstance();
            this.streams = new Hashtable();
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
                    CloudClient client = new CloudClient(this, ++this.clientsCount, this.listener.AcceptTcpClient());
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
