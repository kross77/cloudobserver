using System.ServiceModel;

namespace CloudObserver.Services.RM
{
    [ServiceContract]
    public interface IResourceManager
    {
        [OperationContract]
        bool StartCloudObserverInstance(string gatewayAddress);

        [OperationContract]
        string CreateWorkBlock();
    }
}
