using System;
using System.ServiceModel;
using CloudObserver.Services;

namespace CloudObserver.ConsoleApps.Test
{
    class Program
    {
        static int Main(string[] args)
        {
            if ((args.Length > 0) && (args[0] == "/?"))
            {
                Console.Write("Usage: CloudObserver.ConsoleApps.Test <serviceName> <controllerServiceUri>");
                return 0;
            }
            string serviceName;
            string controllerServiceUri;
            if (args.Length == 2)
            {
                serviceName = args[0];
                controllerServiceUri = args[1];
            }
            else
            {
                Console.Write("Service name: ");
                serviceName = Console.ReadLine();
                Console.Write("Controller Service URI: ");
                controllerServiceUri = Console.ReadLine();
            }
            Console.Write("Testing " + serviceName + "... ");
            try
            {
                ControllerServiceContract controllerServiceClient = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceUri));
                AbstractServiceContract serviceClient = ChannelFactory<AbstractServiceContract>.CreateChannel(new BasicHttpBinding(),
                    new EndpointAddress(controllerServiceClient.GetServiceUri(ServiceHoster.GetServiceType(serviceName))));
                if (serviceClient.GetControllerServiceUri() != controllerServiceUri) throw new Exception();
                Console.WriteLine("OK");
                return 0;
            }
            catch (Exception)
            {
                Console.WriteLine("failed");
                return 1;
            }
        }
    }
}