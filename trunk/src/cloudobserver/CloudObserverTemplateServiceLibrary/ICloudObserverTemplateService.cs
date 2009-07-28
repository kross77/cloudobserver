using System;
using System.ServiceModel;

namespace CloudObserverTemplateServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverTemplateService
    {
        [OperationContract]
        string Echo(string input);
    }
}