using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface IGateway
    {
        [OperationContract]
        void Test();
    }
}