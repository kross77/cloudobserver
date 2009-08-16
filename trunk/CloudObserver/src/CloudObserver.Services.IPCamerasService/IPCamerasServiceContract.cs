using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface IPCamerasServiceContract : AbstractServiceContract
    {
        [OperationContract]
        void SetSource(int cameraID, string sourceType, string sourceUri);

        [OperationContract]
        void SetFPSLimit(int cameraID, int fpsLimit);

        [OperationContract]
        void SetCredentials(int cameraID, string userName, string password);

        [OperationContract]
        void StartBroadcasting(int cameraID);

        [OperationContract]
        void StopBroadcasting(int cameraID);

        [OperationContract]
        int GetFramesCounter(int cameraID);
    }
}