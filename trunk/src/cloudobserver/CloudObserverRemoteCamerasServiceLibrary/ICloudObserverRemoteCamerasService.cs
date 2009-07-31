using System;
using System.ServiceModel;

namespace CloudObserverRemoteCamerasServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverRemoteCamerasService
    {
        [OperationContract]
        void SetSource(int cameraID, string source);

        [OperationContract]
        void SetCredentials(int cameraID, string userName, string password);

        [OperationContract]
        void SetFPS(int cameraID, int fps);

        [OperationContract]
        void StartBroadcasting(int cameraID);

        [OperationContract]
        void StopBroadcasting(int cameraID);

        [OperationContract]
        int GetFramesCounter(int cameraID);
    }
}