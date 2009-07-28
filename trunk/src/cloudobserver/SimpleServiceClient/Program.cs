using System;
using System.ServiceModel;
using CloudObserverTemplateServiceLibrary;

namespace SimpleServiceClient
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Console.Write("Port (1024-65535): ");
                int servicePort = Int32.Parse(Console.ReadLine());
                if ((servicePort < 1024) || (servicePort > 65535)) throw new Exception("Port out of range.");
                string serviceAddress = @"http://localhost:" + servicePort + "/CloudObserverTemplateService";
                Console.WriteLine("Connecting to Cloud Observer Template service at " + serviceAddress);
                ICloudObserverTemplateService client = new ChannelFactory<ICloudObserverTemplateService>(new BasicHttpBinding(), serviceAddress).CreateChannel();
                Console.Write(client.Echo("Connection succeed. Press any key to exit..."));
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }
            Console.ReadKey();
        }
    }
}