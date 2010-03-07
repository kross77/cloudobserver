using System;
using System.ServiceModel;
using System.ServiceModel.Description;

using CloudObserver.Services;

namespace CloudObserver
{
    /// <summary>
    /// Represents an application that hosts a single service.
    /// </summary>
    public static class ServiceHostApplication
    {
        /// <summary>
        /// The entry point of the application.
        /// </summary>
        /// <param name="args">The input arguments of the application. The first argument should be a valid http address. The second argument should be a valid service type.</param>
        public static void Main(string[] args)
        {
            // Check the amount of the arguments.
            if (args.Length < 2)
            {
                Console.Write("Not enough arguments. Expected 2, recieved " + args.Length + ".");
                return;
            }

            // Try to get the service uri.
            Uri serviceUri = null;
            try
            {
                serviceUri = new Uri(args[0]);
            }
            catch (UriFormatException)
            {
                Console.Write("Invalid service address.");
                return;
            }

            // Get the service type.
            string serviceType = args[1];

            // Try to get the service contract and to create an instance of the service.
            Type serviceContract = null;
            Object serviceInstance = null;
            try
            {
                serviceContract = ServicesHelper.GetServiceContract(serviceType);
                serviceInstance = ServicesHelper.CreateServiceInstance(serviceType);
            }
            catch (ArgumentException)
            {
                Console.Write("Invalid service type.");
                return;
            }

            // Create the service host.
            using (ServiceHost serviceHost = new ServiceHost(serviceInstance, serviceUri))
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
                serviceHost.AddServiceEndpoint(serviceContract, new BasicHttpBinding(), String.Empty);

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
                Console.WriteLine("The " + serviceType + " service is hosted at " + serviceUri.ToString());
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