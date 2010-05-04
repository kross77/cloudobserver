using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace CloudObserver
{
    /// <summary>
    /// Represents an application that redirects stream from one http server to another one.
    /// </summary>
    public static class StreamProxy
    {
        private const int bufferSize = 8192;

        /// <summary>
        /// The entry point of the application.
        /// </summary>
        /// <param name="args">The input arguments of the application. The first argument should be a valid http address of the source server. The second argument should be a valid http address of the destination server.</param>
        public static void Main(string[] args)
        {
            // Check the amount of the arguments.
            if (args.Length < 2)
            {
                Console.Write("Not enough arguments. Expected 2, recieved " + args.Length + ".");
                return;
            }

            // Try to get the source server URI.
            Uri sourceUri;
            try
            {
                sourceUri = new Uri(args[0]);
            }
            catch (UriFormatException)
            {
                Console.Write("Invalid source server address.");
                return;
            }

            // Try to get the destination server URI.
            Uri destinationUri;
            try
            {
                destinationUri = new Uri(args[1]);
            }
            catch (UriFormatException)
            {
                Console.Write("Invalid destination server address.");
                return;
            }

            // Try to connect to the source server.
            Stream sourceStream;
            try
            {
                sourceStream = WebRequest.Create(sourceUri).GetResponse().GetResponseStream();
            }
            catch (Exception exception)
            {
                Console.Write("Cannot connect to the source server. Details: " + exception.Message);
                return;
            }

            // Try to connect to the destination server.
            NetworkStream destinationStream;
            try
            {
                destinationStream = new TcpClient(destinationUri.Host, destinationUri.Port).GetStream();
            }
            catch (Exception exception)
            {
                Console.Write("Cannot connect to the destination server. Details: " + exception.Message);
                return;
            }

            // Start redirecting the data.
            int read = 0;
            byte[] buffer = new byte[bufferSize];
            do
            {
                try
                {
                    read = sourceStream.Read(buffer, 0, bufferSize);
                }
                catch (Exception exception)
                {
                    Console.Write("An error occurred while receiving data from the source server. Details: " + exception.Message);
                    return;
                }

                try
                {
                    destinationStream.Write(buffer, 0, read);
                }
                catch (Exception exception)
                {
                    Console.Write("An error occurred while sending data to the destination server. Details: " + exception.Message);
                    return;
                }
            }
            while (read > 0);

            Console.Write("All data redirected.");
        }
    }
}
