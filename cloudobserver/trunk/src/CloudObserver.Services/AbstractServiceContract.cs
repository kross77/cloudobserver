using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface AbstractServiceContract
    {
        [OperationContract]
        void SetControllerServiceUri(string controllerServiceUri);
    }
}