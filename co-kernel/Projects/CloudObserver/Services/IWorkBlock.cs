using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface IWorkBlock
    {
        [OperationContract]
        void Test();
    }
}