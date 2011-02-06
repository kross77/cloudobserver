using System;
using System.ServiceModel;
using System.Collections.Generic;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class ControllerService : ControllerServiceContract
    {
        private Dictionary<ServiceType, List<string>> services;

        public ControllerService()
        {
            services = new Dictionary<ServiceType, List<string>>();
        }

        public string GetServiceUri(ServiceType serviceType)
        {
            return services[serviceType][0];
        }

        public void SetServiceUri(ServiceType serviceType, string serviceUri)
        {
            if (!services.ContainsKey(serviceType))
                services[serviceType] = new List<string>();
            services[serviceType].Add(serviceUri);
        }
    }
}