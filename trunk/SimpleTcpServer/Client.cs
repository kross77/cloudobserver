using System;
using System.IO;
using System.Net.Sockets;
using System.Threading;

namespace SimpleTcpServer
{
    public class Client
    {
        private uint clientNumber;
        private TcpClient client;
        private StreamWriter logWriter;

        public Client(uint clientNumber, TcpClient client)
        {
            this.clientNumber = clientNumber;
            this.client = client;
            this.logWriter = new StreamWriter(File.Create("client-" + this.clientNumber.ToString() + "-log.txt"));
        }

        public void Process()
        {
            this.WriteLog("Client " + this.clientNumber.ToString() + " connected.");

            FileStream fileStream = File.Create("client-" + this.clientNumber.ToString() + ".dat");
            NetworkStream networkStream = this.client.GetStream();

            int totalBytesReceived = 0;
            byte[] buffer = new byte[this.client.ReceiveBufferSize];

            try
            {
                do
                {
                    int bytesReceived = 0;
                    do
                    {
                        int bytesRead = networkStream.Read(buffer, 0, buffer.Length);
                        bytesReceived += bytesRead;
                        fileStream.Write(buffer, 0, bytesRead);
                    }
                    while (networkStream.DataAvailable);

                    if (bytesReceived > 0)
                    {
                        this.WriteLog("Client " + this.clientNumber.ToString() + " received " + bytesReceived.ToString() + ((bytesReceived == 1) ? " byte" : " bytes"));
                        totalBytesReceived += bytesReceived;
                    }
                    else
                        this.client.Close();
                } while (client.Connected);
            }
            catch (IOException)
            {
            }
            catch (Exception e)
            {
                this.WriteLog("Client " + this.clientNumber.ToString() + " caught " + e.ToString());
            }
            finally
            {
                this.WriteLog("Client " + this.clientNumber.ToString() + " disconnected. Total bytes received: " + totalBytesReceived.ToString());

                networkStream.Close();
                fileStream.Close();
                this.logWriter.Close();
                this.client.Close();
                Thread.CurrentThread.Abort();
            }
        }

        private void WriteLog(string message)
        {
            message = DateTime.Now.ToString() + ": " + message;

            this.logWriter.WriteLine(message);
            Console.WriteLine(message);
        }
    }
}
