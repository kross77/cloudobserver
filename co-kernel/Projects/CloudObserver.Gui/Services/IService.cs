using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface IService
    {
        [OperationContract]
        void ConnectToCloud(string cloudControllerUri);

        [OperationContract]
        string GetCloudControllerUri();
    }
}