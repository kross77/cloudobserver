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

        public void SetSource(int cameraID, string source)
        {
            if (!virtualCameras.ContainsKey(cameraID))
                virtualCameras[cameraID] = new VirtualCamera(cameraID, "http://localhost:9000/CloudObserverBroadcastService");
            virtualCameras[cameraID].SetSource(source);
        }

        public void SetCredentials(int cameraID, string userName, string password)
        {
            virtualCameras[cameraID].SetCredentials(userName, password);
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
            virtualCameras[cameraID].StartBroadcasting();
        }

        public int GetFramesCounter(int cameraID)
        {
            return virtualCameras[cameraID].GetFramesCounter();
        }
    }
}