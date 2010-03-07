using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface ICloudController
    {
        [OperationContract]
        void Test();
    }
}