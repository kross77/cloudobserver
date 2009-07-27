using System;
using System.ServiceModel;

namespace CloudObserverBroadcastServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverBroadcastService
    {
        [OperationContract]
        void BindMeToCamera(int clientID, int cameraID);

        [OperationContract]
        void SetMeAsCamera(int cameraID);

        [OperationContract]
        byte[] GetNextFrame(int cameraID);

        [OperationContract]
        void SetNextFrame(byte[] frame);
    }
}