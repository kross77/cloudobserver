using CloudObserver.Services.CC;
using System;
using System.ServiceModel;

namespace CloudObserver.Services.RM
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class ResourceManager : Service, IResourceManager
    {
        private int workBlocksCounter = 0;

        private string baseAddress;

        public ResourceManager(string serviceAddress, string serviceType)
            : base(serviceAddress, serviceType)
        {
            baseAddress = serviceAddress.Replace("/rm", "");
        }

        public bool StartCloudObserverInstance(string gatewayAddress)
        {
            string controllerAddress = baseAddress + "/cc";
            if (!ServicesHelper.HostService(controllerAddress, "CC"))
                return false;

            if (ServicesHelper.HostService(gatewayAddress, "GW"))
                ServicesHelper.ConnectServiceToController(gatewayAddress, controllerAddress);
            else
                return false;

            ServicesHelper.ConnectServiceToController(ServiceAddress, controllerAddress);

            return true;
        }

        public string CreateWorkBlock()
        {
            string workBlockAddress = baseAddress + "/wb-" + workBlocksCounter++;
            if (ServicesHelper.HostService(workBlockAddress, "WB"))
                ServicesHelper.ConnectServiceToController(workBlockAddress, ControllerAddress);
            else
                return string.Empty;

            return workBlockAddress;
        }
    }
}
