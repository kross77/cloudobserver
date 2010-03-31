using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Service : IService
    {
        protected string cloudControllerUri;

        public void ConnectToCloud(string cloudControllerUri)
        {
            this.cloudControllerUri = cloudControllerUri;
        }

        public string GetCloudControllerUri()
        {
            return this.cloudControllerUri;
        }
    }
}
