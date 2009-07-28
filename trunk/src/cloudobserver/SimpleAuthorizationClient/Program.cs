using System;
using System.ServiceModel;
using CloudObserverAuthorizationServiceLibrary;

namespace SimpleAuthorizationClient
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
                string serviceAddress = @"http://localhost:" + servicePort + "/CloudObserverAuthorizationService";
                Console.WriteLine("Connecting to Cloud Observer Authorization service at " + serviceAddress);
                ICloudObserverAuthorizationService client = new ChannelFactory<ICloudObserverAuthorizationService>(new BasicHttpBinding(), serviceAddress).CreateChannel();
                Console.WriteLine("Connection succeed. Preparing login procedure...");
                Console.Write("Email: ");
                string email = Console.ReadLine();
                Console.Write("Password: ");
                string password = Console.ReadLine();
                Console.WriteLine(client.UserLogin(email, password) ? "Login succeed." : "Login failed. Invalid email or password.");
                Console.Write("Press any key to exit...");
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }
            Console.ReadKey();
        }
    }
}