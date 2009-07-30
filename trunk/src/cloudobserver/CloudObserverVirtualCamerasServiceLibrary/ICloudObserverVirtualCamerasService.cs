using System;
using System.ServiceModel;

namespace CloudObserverVirtualCamerasServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverVirtualCamerasService
    {
        [OperationContract]
        void AddSource(int cameraID, string uri, int framesPerCycle);

        [OperationContract]
        void SetFPS(int cameraID, int fps);

        [OperationContract]
        void StartBroadcasting(int cameraID);

        [OperationContract]
        void StopBroadcasting(int cameraID);

        [OperationContract]
        string[] GetSources(int cameraID);

        [OperationContract]
        int GetFramesCounter(int cameraID);
    }
}