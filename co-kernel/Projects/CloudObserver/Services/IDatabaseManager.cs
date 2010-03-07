using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface IDatabaseManager
    {
        [OperationContract]
        void Test();
    }
}