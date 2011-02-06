using System;
using System.Reflection;
using System.ServiceModel;
using System.Windows.Forms;
using CloudObserver.Services;

namespace CloudObserver.ConsoleApps.Host
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            if ((args.Length > 0) && (args[0] == "/?"))
            {
                Console.Write("Usage: CloudObserver.ConsoleApps.Host <serviceName> <serviceDll> <serviceIP> <servicePort> <controllerServiceUri>");
                return;
            }
            string serviceName;
            string serviceDll;
            string serviceIP;
            int servicePort;
            string controllerServiceUri;
            if (args.Length == 5)
            {
                serviceName = args[0];
                Console.WriteLine("Service name: " + serviceName);
                serviceDll = args[1];
                serviceIP = args[2];
                Console.WriteLine("Service IP: " + serviceIP);
                servicePort = Int32.Parse(args[3]);
                Console.WriteLine("Service port: " + servicePort);
                controllerServiceUri = args[4];
                Console.WriteLine("Controller Service URI: " + controllerServiceUri);
            }
            else
            {
                OpenFileDialog openFileDialogServiceDll = new OpenFileDialog();
                openFileDialogServiceDll.Filter = "Dynamic Link Library (*.dll)|*.dll";
                if (openFileDialogServiceDll.ShowDialog() != DialogResult.OK) return;
                serviceName = openFileDialogServiceDll.SafeFileName.Substring(23, openFileDialogServiceDll.SafeFileName.Length - 27);
                serviceDll = openFileDialogServiceDll.FileName;
                Console.WriteLine("Service name: " + serviceName);
                Console.Write("Service IP: ");
                serviceIP = Console.ReadLine();
                Console.Write("Service port: ");
                servicePort = Int32.Parse(Console.ReadLine());
                Console.Write("Controller Service URI: ");
                controllerServiceUri = Console.ReadLine();
            }
            try
            {
                Console.WriteLine();
                Assembly serviceDllAssembly = Assembly.LoadFile(serviceDll);
                Type serviceType = serviceDllAssembly.GetType("CloudObserver.Services." + serviceName);
                Type serviceContractType = serviceDllAssembly.GetType("CloudObserver.Services." + serviceName + "Contract");
                string serviceUri = @"http://" + serviceIP + ":" + servicePort + @"/" + serviceName;
                ServiceHost serviceHost = ServiceHoster.CreateServiceHost(serviceType, serviceContractType, serviceUri);
                serviceHost.Open();
                if (serviceName != "ControllerService")
                {
                    ControllerServiceContract controllerServiceClient = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceUri));
                    controllerServiceClient.SetServiceUri(ServiceHoster.GetServiceType(serviceName), serviceUri);
                    ChannelFactory<AbstractServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(serviceUri)).SetControllerServiceUri(controllerServiceUri);
                }
                Console.WriteLine("Service hosted at " + serviceUri);
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