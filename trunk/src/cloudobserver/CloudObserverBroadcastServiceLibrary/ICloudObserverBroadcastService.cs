using System;
using System.ServiceModel;

namespace CloudObserverBroadcastServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverBroadcastService
    {
        [OperationContract]
        void BindMeToCamera(int clientID, int cameraID, string UID);

        [OperationContract]
        void SetMeAsCamera(int cameraID, string UID);

        [OperationContract]
        byte[] GetNextFrame(int cameraID, string UID);

        [OperationContract]
        void SetNextFrame(byte[] frame, string UID);
    }
}