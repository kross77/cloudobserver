using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface IGateway : IService
    {
        [OperationContract]
        string GetWorkBlock();
    }
}
