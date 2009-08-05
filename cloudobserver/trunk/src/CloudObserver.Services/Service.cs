using System;

namespace CloudObserver.Services
{
    public abstract class Service : ServiceContract
    {
        protected string controllerServiceUri;

        public void SetControllerServiceUri(string controllerServiceUri)
        {
            this.controllerServiceUri = controllerServiceUri;
        }
    }
}