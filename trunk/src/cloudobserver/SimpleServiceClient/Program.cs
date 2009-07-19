using System;
using System.ServiceModel;
using CloudObserverServiceLibrary;

namespace SimpleServiceClient
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Port: ");
            string port = Console.ReadLine();
            ICloudObserverService client = new ChannelFactory<ICloudObserverService>(new BasicHttpBinding(), "http://localhost:" + port + "/CloudObserverService").CreateChannel();
            Console.Write("Email: ");
            Console.Write("This email " + (client.UserIsEmailAvailable(Console.ReadLine()) ? "is" : "is not") + " available.");
            Console.ReadKey();
        }
    }
}