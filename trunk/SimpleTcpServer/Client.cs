using System;
using System.IO;
using System.Net.Sockets;
using System.Threading;

namespace SimpleTcpServer
{
    public class Client
    {
        private Server server;
        private TcpClient client;
        private uint clientNumber;

        public Client(Server server, TcpClient client, uint clientNumber)
        {
            this.server = server;
            this.client = client;
            this.clientNumber = clientNumber;
        }

        public void Process()
        {
            byte[] buffer = new byte[this.client.ReceiveBufferSize];

            this.server.WriteLog("Client " + this.clientNumber.ToString() + " connected. Incoming data will be written into file 'client-" + this.clientNumber.ToString() + ".dat'.");
            FileStream fileStream = File.Create("client-" + this.clientNumber.ToString() + ".dat");
            NetworkStream networkStream = this.client.GetStream();

            try
            {
                int count = 0;
                int read = 0;
                do
                {
                    read = networkStream.Read(buffer, 0, buffer.Length);
                    count += read;
                    fileStream.Write(buffer, 0, read);
                }
                while (networkStream.DataAvailable);
                this.server.WriteLog("Client " + this.clientNumber.ToString() + " disconnected. Bytes recieved: " + count.ToString());
            }
            catch (Exception e)
            {
                this.server.WriteLog("Client " + this.clientNumber.ToString() + " has an error: " + e.ToString());
            }
            finally
            {
                networkStream.Close();
                fileStream.Close();
                client.Close();
                Thread.CurrentThread.Abort();
            }
        }
    }
}
