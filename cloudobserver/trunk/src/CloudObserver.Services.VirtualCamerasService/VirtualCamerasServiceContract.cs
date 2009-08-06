using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface VirtualCamerasServiceContract : AbstractServiceContract
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