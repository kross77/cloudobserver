using System;
using System.ServiceModel;

namespace CloudObserverTemplateServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverTemplateService
    {
        [OperationContract]
        void TemplateMethod();
    }
}