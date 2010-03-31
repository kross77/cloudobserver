using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudController : Service, ICloudController
    {
        private string name;
        private string defaultGatewayUri;

        private Dictionary<string, ServiceType> services;

        public CloudController()
        {
            services = new Dictionary<string, ServiceType>();
        }

        public void Initialize(string name)
        {
            this.name = name;
        }

        public void RegisterService(string serviceUri, ServiceType serviceType)
        {
            services[serviceUri] = serviceType;
        }

        public void SetDefaultGateway(string defaultGatewayUri)
        {
            this.defaultGatewayUri = defaultGatewayUri;
        }
    }
}
