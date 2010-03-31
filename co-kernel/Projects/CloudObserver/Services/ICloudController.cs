using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface ICloudController : IService
    {
        [OperationContract]
        void Initialize(string name);

        [OperationContract]
        void RegisterService(string serviceUri, ServiceType serviceType);

        [OperationContract]
        void SetDefaultGateway(string defaultGatewayUri);
    }
}
