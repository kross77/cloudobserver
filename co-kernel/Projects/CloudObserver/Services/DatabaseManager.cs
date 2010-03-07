using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class DatabaseManager : IDatabaseManager
    {
        public void Test()
        {
        }
    }
}