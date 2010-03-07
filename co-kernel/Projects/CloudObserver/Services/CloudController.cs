using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudController : ICloudController
    {
        public void Test()
        {
        }
    }
}