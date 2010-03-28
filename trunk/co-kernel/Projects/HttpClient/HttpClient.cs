using System;
using System.Text;
using System.Net.Sockets;

namespace HttpServerPrototype.HttpClient
{
    public class HttpClient
    {
        private const int bufferSize = 1024;

        public static void Main(string[] args)
        {
            Console.Write("Hostname: ");
            string hostname = Console.ReadLine();
            Console.Write("Port: ");
            int port = Int32.Parse(Console.ReadLine());
            Console.Write("Resource: ");
            string resource = Console.ReadLine();

            TcpClient tcpClient = new TcpClient();
            tcpClient.Connect(hostname, port);
            NetworkStream networkStream = tcpClient.GetStream();
            byte[] request = Encoding.UTF8.GetBytes("GET " + resource + " HTTP/1.0\r\n\r\n");
            networkStream.Write(request, 0, request.Length);
            networkStream.Flush();

            byte[] buffer = new byte[bufferSize];
            int read = networkStream.Read(buffer, 0, bufferSize);
            while (read > 0)
            {
                Console.Write(Encoding.UTF8.GetString(buffer, 0, read));
                Console.ReadKey();
                read = networkStream.Read(buffer, 0, bufferSize);
            }

            networkStream.Close();
            tcpClient.Close();
            Console.ReadKey();
        }
    }
}
