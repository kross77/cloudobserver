using System;
using System.ServiceModel;
using CloudObserver.Services;

namespace CloudObserver.Services
{
    [ServiceContract]
    [ServiceKnownType(typeof(ServiceType))]
    public interface ControllerServiceContract
    {
        [OperationContract]
        string GetServiceUri(ServiceType serviceType);

        [OperationContract]
        void SetServiceUri(ServiceType serviceType, string serviceUri);
    }
}