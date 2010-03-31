using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Gateway : Service, IGateway
    {
        public string GetWorkBlock()
        {
            return this.cloudControllerUri.Replace("cc-0", "wb-0");
        }
    }
}
