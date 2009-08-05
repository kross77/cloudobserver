using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface ServiceContract
    {
        void SetControllerServiceUri(string controllerServiceUri);
    }
}