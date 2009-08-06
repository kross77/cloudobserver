using System;

namespace CloudObserver.Services
{
    public abstract class AbstractService : AbstractServiceContract
    {
        protected string controllerServiceUri;

        public void SetControllerServiceUri(string controllerServiceUri)
        {
            this.controllerServiceUri = controllerServiceUri;
        }
    }
}