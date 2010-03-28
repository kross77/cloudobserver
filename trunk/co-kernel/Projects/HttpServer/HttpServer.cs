using System;

namespace HttpServerPrototype.HttpServer
{
    public class HttpServer
    {
        public static void Main(string[] args)
        {
            Console.Write("Port: ");

            int port = 8080;
            if (!Int32.TryParse(Console.ReadLine(), out port))
            {
                Console.Write("Invalid port.");
                return;
            }

            TestHttpServer server = new TestHttpServer(port);
            server.Name = "TestHttpServer/1.0";
            server.Start();

            Console.WriteLine("The server is started.");
            Console.WriteLine("Press any key to stop the server...");
            Console.ReadKey();

            server.Stop();
            Console.Write("The server is stopped.");
        }
    }
}
