using System;
using System.ServiceModel;

namespace CloudObserverCampusCamerasStreamingServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverCampusCamerasStreamingService
    {
        [OperationContract]
        void startService();

        [OperationContract]
        void stopService();
    }
}