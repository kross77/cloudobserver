using System;
using System.Reflection;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace SimpleServiceHoster
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Console.Write("Absolute DLL path: ");
                string dllPath = Console.ReadLine();
                Console.Write("Service name: ");
                string name = Console.ReadLine();
                Console.Write("Service port: ");
                string port = Console.ReadLine();

                Assembly serviceDLL = Assembly.LoadFile(dllPath);
                Type serviceContractType = serviceDLL.GetType(name + "Library.I" + name);
                Type serviceType = serviceDLL.GetType(name + "Library." + name);

                string path = "http://localhost:" + port + "/" + name;
                ServiceHost svcHost = new ServiceHost(serviceType, new Uri(path));
                ServiceMetadataBehavior mexBehavior = new ServiceMetadataBehavior();
                mexBehavior.HttpGetEnabled = true;
                svcHost.Description.Behaviors.Add(mexBehavior);
                svcHost.AddServiceEndpoint(serviceContractType, new BasicHttpBinding(), "");
                svcHost.Open();
                Console.WriteLine("Service hosted at " + path);
                Console.Write("Press any key to stop hosting...");
                Console.ReadKey();
                svcHost.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                Console.ReadKey();
            }
        }
    }
}