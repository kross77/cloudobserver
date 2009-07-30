using System;
using System.ServiceModel;

namespace CloudObserverBroadcastServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverBroadcastService
    {
        [OperationContract]
        byte[] ReadFrame(int cameraID);

        [OperationContract]
        void WriteFrame(int cameraID, byte[] frame);
    }
}