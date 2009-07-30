using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserverVirtualCamerasServiceLibrary
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudObserverVirtualCamerasService : ICloudObserverVirtualCamerasService
    {
        Dictionary<int, VirtualCamera> virtualCameras;

        public CloudObserverVirtualCamerasService()
        {
            virtualCameras = new Dictionary<int, VirtualCamera>();
        }

        public void AddSource(int cameraID, string uri, int framesPerCycle)
        {
            if (!virtualCameras.ContainsKey(cameraID))
                virtualCameras[cameraID] = new VirtualCamera(cameraID, "http://localhost:9000/CloudObserverBroadcastService");
            virtualCameras[cameraID].AddSource(uri, framesPerCycle);
        }

        public void SetFPS(int cameraID, int fps)
        {
            virtualCameras[cameraID].SetFPS(fps);
        }

        public void StartBroadcasting(int cameraID)
        {
            virtualCameras[cameraID].StartBroadcasting();
        }

        public void StopBroadcasting(int cameraID)
        {
            virtualCameras[cameraID].StopBroadcasting();
        }
        public string[] GetSources(int cameraID)
        {
            return virtualCameras[cameraID].GetSources();
        }

        public int GetFramesCounter(int cameraID)
        {
            return virtualCameras[cameraID].GetFramesCounter();
        }
    }
}