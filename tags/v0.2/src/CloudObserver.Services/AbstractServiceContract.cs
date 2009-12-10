using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface AbstractServiceContract
    {
        [OperationContract]
        string GetControllerServiceUri();

        [OperationContract]
        void SetControllerServiceUri(string controllerServiceUri);
    }
}