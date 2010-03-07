using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Gateway : IGateway
    {
        public void Test()
        {
        }
    }
}