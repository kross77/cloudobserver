using System;
using System.IO;
using System.ServiceModel;

namespace SoundStreaming.FileReceiver
{
    class Program
    {
        static void Main(string[] args)
        {
            const int chunkSize = 1024;
            const string serviceUri = "http://127.0.0.1:9000/StreamingService";
            const int maxReceivedMessageSize = 2147483647;
            const int maxArrayLength = 2147483647;

            BasicHttpBinding binding = new BasicHttpBinding();
            binding.BypassProxyOnLocal = true;
            binding.MaxReceivedMessageSize = maxReceivedMessageSize;
            binding.OpenTimeout = TimeSpan.FromMinutes(5);
            binding.CloseTimeout = TimeSpan.FromMinutes(5);
            binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
            binding.SendTimeout = TimeSpan.FromMinutes(30);
            binding.ReaderQuotas.MaxArrayLength = maxArrayLength;
            binding.TransferMode = TransferMode.Streamed;

            Console.WriteLine("Connecting...");
            StreamingServiceClient streamingServiceClient = new StreamingServiceClient(binding, new EndpointAddress(serviceUri));

            Console.WriteLine("Working...");
            byte[] buffer = new byte[chunkSize];
            FileStream fs = File.Create("temp.mp3");

            int readPosition = 0;

            int received = -1;
            while (received != 0)
            {
                received = streamingServiceClient.Read(out buffer, chunkSize, ref readPosition, false);
                fs.Write(buffer, 0, received);
            }
            Console.WriteLine("Done!");
            fs.Close();
        }
    }
}