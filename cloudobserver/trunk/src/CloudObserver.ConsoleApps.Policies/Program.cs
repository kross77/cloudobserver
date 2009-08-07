using System;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.ServiceModel.Description;
using CloudObserver.Policies;

namespace CloudObserver.ConsoleApps.Policies
{
    class Program
    {
        static void Main(string[] args)
        {
            string serviceIP;
            int servicePort;
            if (args.Length == 2)
            {
                serviceIP = args[0];
                servicePort = Int32.Parse(args[1]);
            }
            else
            {
                if (args.Length > 0)
                {
                    Console.Write("Usage: CloudObserver.ConsoleApps.Policies <serviceIP> <servicePort>");
                    Console.ReadKey();
                    return;
                }
                Console.Write("Service IP: ");
                serviceIP = Console.ReadLine();
                Console.Write("Service port: ");
                servicePort = Int32.Parse(Console.ReadLine());
            }
            try
            {
                string serviceUri = @"http://" + serviceIP + ":" + servicePort + "/";
                ServiceHost serviceHost = new ServiceHost(typeof(PolicyRetriever), new Uri(serviceUri));
                serviceHost.AddServiceEndpoint(typeof(PolicyRetrieverContract), new WebHttpBinding(), "").Behaviors.Add(new WebHttpBehavior());
                serviceHost.Open();
                Console.WriteLine("Policies hosted at " + serviceUri);
                Console.Write("Press any key to stop hosting...");
                Console.ReadKey();
                serviceHost.Close();
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.ToString());
                Console.ReadKey();
            }
        }
    }
}