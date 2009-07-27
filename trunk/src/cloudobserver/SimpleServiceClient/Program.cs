using System;
using System.ServiceModel;
using CloudObserverAuthorizationServiceLibrary;

namespace SimpleServiceClient
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Port: ");
            string port = Console.ReadLine();
            ICloudObserverAuthorizationService client = new ChannelFactory<ICloudObserverAuthorizationService>(new BasicHttpBinding(), "http://localhost:" + port + "/CloudObserverService").CreateChannel();
            Console.Write("Email: ");
            Console.Write("This email " + (client.UserIsEmailAvailable(Console.ReadLine()) ? "is" : "is not") + " available.");
            Console.ReadKey();
        }
    }
}