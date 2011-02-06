using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public abstract class AbstractService : AbstractServiceContract
    {
        protected string controllerServiceUri;

        public string GetControllerServiceUri()
        {
            return controllerServiceUri;
        }

        public void SetControllerServiceUri(string controllerServiceUri)
        {
            this.controllerServiceUri = controllerServiceUri;
        }
    }
}