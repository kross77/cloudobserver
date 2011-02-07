using System;
using System.ServiceModel;

namespace CloudObserverContentServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverContentService
    {
        [OperationContract]
        string Echo(string input);

        [OperationContract]
        void LoadTranslation(DateTime start, DateTime stop, int frequency,int fromCamera, int toCamera);
    }
}