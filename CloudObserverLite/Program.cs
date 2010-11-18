using System;

namespace CloudObserverLite
{
    public class Program
    {
        private const ushort DEFAULT_PORT = 4773;
        private const ushort MIN_PORT = 1024;
        private const ushort MAX_PORT = 65535;

        public static void Main(string[] args)
        {
            Console.WriteLine("Cloud Observer Lite 1.0.0");
            Console.WriteLine("by CloudForever (c) team");
            Console.WriteLine();

            bool useDefaultPort = true;
            ushort port = DEFAULT_PORT;

            if (args.Length > 0)
                if (UInt16.TryParse(args[0], out port))
                    if ((port >= MIN_PORT) && (port <= MAX_PORT))
                    {
                        useDefaultPort = false;
                        Console.WriteLine("Using specified port: " + port.ToString());
                    }
                    else
                        Console.WriteLine("The first command line argument presents and parsed as an unsigned short "
                            + port.ToString() + ", but it exceeds permitted port range [" + MIN_PORT.ToString() + "-" + MAX_PORT.ToString() + "].");
                else
                    Console.WriteLine("The first command line argument presents, but it cannot be parsed as an unsigned short.");
            else
                Console.WriteLine("No command line arguments provided.");

            if (useDefaultPort)
            {
                port = DEFAULT_PORT;
                Console.WriteLine("Using default port: " + DEFAULT_PORT.ToString());
            }

            CloudServer server = new CloudServer(port);
            Console.WriteLine("Cloud Observer is now starting. Press any key to stop and exit...");
            Console.WriteLine();
            server.Start();
            Console.ReadKey();
            server.Stop();
        }
    }
}
