using CloudObserver.Services.GW;
using System;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace CloudObserver
{
    /// <summary>
    /// Represents an application that starts the Cloud Observer system.
    /// </summary>
    public static class CloudStart
    {
        /// <summary>
        /// The entry point of the application.
        /// </summary>
        public static void Main()
        {
            // Get the IP address.
            Console.Write("IP Address: ");
            string ipAddress = Console.ReadLine();

            // Construct the service address.
            string serviceAddress = "http://" + ipAddress + ":4773/";

            // Check the service address.
            Uri serviceUri = null;
            try
            {
                serviceUri = new Uri(serviceAddress);
            }
            catch (UriFormatException)
            {
                Console.Write("Invalid address.");
                return;
            }

            // Create the service host.
            using (ServiceHost serviceHost = new ServiceHost(new Gateway(ipAddress), serviceUri))
            {
                // Configure the service metadata behavior.
                ServiceMetadataBehavior serviceMetadataBehavior = serviceHost.Description.Behaviors.Find<ServiceMetadataBehavior>();
                if (serviceMetadataBehavior == null)
                {
                    serviceMetadataBehavior = new ServiceMetadataBehavior();
                    serviceMetadataBehavior.HttpGetEnabled = true;
                    serviceHost.Description.Behaviors.Add(serviceMetadataBehavior);
                }
                else
                    serviceMetadataBehavior.HttpGetEnabled = true;

                // Configure the service debug behavior.
                ServiceDebugBehavior serviceDebugBehavior = serviceHost.Description.Behaviors.Find<ServiceDebugBehavior>();
                if (serviceDebugBehavior == null)
                {
                    serviceDebugBehavior = new ServiceDebugBehavior();
                    serviceDebugBehavior.IncludeExceptionDetailInFaults = true;
                    serviceHost.Description.Behaviors.Add(serviceDebugBehavior);
                }
                else
                    serviceDebugBehavior.IncludeExceptionDetailInFaults = true;

                // Configure the service endpoints.
                serviceHost.AddServiceEndpoint(typeof(IGateway), new BasicHttpBinding(), String.Empty);

                // Try to start the service.
                try
                {
                    serviceHost.Open();
                }
                catch (Exception exception)
                {
                    Console.Write("Cannot start the service. Details: " + exception.Message);
                    try
                    {
                        if (serviceHost != null)
                            serviceHost.Close();
                    }
                    catch (Exception)
                    {
                        try
                        {
                            serviceHost.Abort();
                        }
                        finally
                        {
                        }
                    }
                    return;
                }

                // Notify the user about successful service start.
                Console.WriteLine("The service is hosted at " + serviceAddress.ToString());
                Console.WriteLine("Press any key to stop hosting...");
                Console.ReadKey();

                // Try to stop the service.
                try
                {
                    serviceHost.Close();
                }
                catch (Exception exception)
                {
                    Console.Write("An error occurred while stopping the service. Details: " + exception.Message);
                    try
                    {
                        serviceHost.Abort();
                    }
                    finally
                    {
                    }
                }
                finally
                {
                    Console.Write("The service hosting has been stopped.");
                }
            }
        }
    }
}
