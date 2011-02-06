using System;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace CloudObserver.Services
{
    public class ServiceHoster
    {
        private const int MAX_RECEIVED_MESSAGE_SIZE = 2147483647;
        private const int MAX_ARRAY_LENGTH = 2147483647;

        public static ServiceHost CreateServiceHost(Type serviceType, Type serviceContractType, string serviceUri)
        {
            ServiceHost serviceHost = new ServiceHost(serviceType, new Uri(serviceUri));

            ServiceMetadataBehavior serviceMetadataBehavior = serviceHost.Description.Behaviors.Find<ServiceMetadataBehavior>();
            if (serviceMetadataBehavior == null)
            {
                serviceMetadataBehavior = new ServiceMetadataBehavior();
                serviceMetadataBehavior.HttpGetEnabled = true;
                serviceHost.Description.Behaviors.Add(serviceMetadataBehavior);
            }
            else
                serviceMetadataBehavior.HttpGetEnabled = true;

            ServiceDebugBehavior serviceDebugBehavior = serviceHost.Description.Behaviors.Find<ServiceDebugBehavior>();
            if (serviceDebugBehavior == null)
            {
                serviceDebugBehavior = new ServiceDebugBehavior();
                serviceDebugBehavior.IncludeExceptionDetailInFaults = true;
                serviceHost.Description.Behaviors.Add(serviceDebugBehavior);
            }
            else
                serviceDebugBehavior.IncludeExceptionDetailInFaults = true;

            BasicHttpBinding binding = new BasicHttpBinding();
            binding.BypassProxyOnLocal = true;
            binding.MaxReceivedMessageSize = MAX_RECEIVED_MESSAGE_SIZE;
            binding.OpenTimeout = TimeSpan.FromMinutes(5);
            binding.CloseTimeout = TimeSpan.FromMinutes(5);
            binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
            binding.SendTimeout = TimeSpan.FromMinutes(30);
            binding.ReaderQuotas.MaxArrayLength = MAX_ARRAY_LENGTH;
            serviceHost.AddServiceEndpoint(serviceContractType, binding, "");
            return serviceHost;
        }

        public static ServiceType GetServiceType(string serviceName)
        {
            switch (serviceName)
            {
                case "AccountsService":
                    return ServiceType.AccountsService;
                case "AuthenticationService":
                    return ServiceType.AuthenticationService;
                case "BroadcastService":
                    return ServiceType.BroadcastService;
                case "StorageService":
                    return ServiceType.StorageService;
                case "IPCamerasService":
                    return ServiceType.IPCamerasService;
                case "TestSoundService":
                    return ServiceType.TestSoundService;
                default:
                    return ServiceType.UnknownService;
            }
        }
    }
}