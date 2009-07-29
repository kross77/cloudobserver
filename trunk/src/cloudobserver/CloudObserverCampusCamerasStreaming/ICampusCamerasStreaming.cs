using System;
using System.ServiceModel;

namespace CloudObserverCampusCamerasStreaming
{
    [ServiceContract]
    public interface ICloudObserverCampusCamerasStreaming
    {
        [OperationContract]
        void startService();
    }
}