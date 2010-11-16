using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace SimpleTcpServer
{
    public class Server
    {
        private TcpListener listener;
        private Thread thread;
        private ushort port;
        private uint clientsCount = 0;

        public Server(ushort port)
        {
            this.port = port;
        }

        public void Listen()
        {
            this.listener = new TcpListener(IPAddress.Loopback, this.port);
            this.listener.Start();
            WriteLog("Listening on port: " + this.port.ToString());

            while (true)
            {
                Client client = new Client(this, this.listener.AcceptTcpClient(), ++this.clientsCount);
                Thread clientThread = new Thread(new ThreadStart(client.Process));
                clientThread.Name = "Client " + this.clientsCount.ToString();
                clientThread.IsBackground = true;
                clientThread.Start();
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
            this.thread.Abort();
        }

        public void WriteLog(string message)
        {
            Console.WriteLine(message);
        }
    }
}
