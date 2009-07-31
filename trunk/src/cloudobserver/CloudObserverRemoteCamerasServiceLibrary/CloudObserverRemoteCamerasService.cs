using System;
using System.Net;
using System.Timers;
using System.Collections.Generic;
using System.ServiceModel;
using CloudObserverBroadcastServiceLibrary;

namespace CloudObserverRemoteCamerasServiceLibrary
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudObserverRemoteCamerasService : ICloudObserverRemoteCamerasService
    {
        Dictionary<int, RemoteCamera> remoteCameras;

        public CloudObserverRemoteCamerasService()
        {
            remoteCameras = new Dictionary<int, RemoteCamera>();
        }

        public void SetSource(int cameraID, string source)
        {
            if (!remoteCameras.ContainsKey(cameraID))
                remoteCameras[cameraID] = new RemoteCamera(cameraID, "http://localhost:9000/CloudObserverBroadcastService");
            remoteCameras[cameraID].SetSource(source);
        }

        public void SetCredentials(int cameraID, string userName, string password)
        {
            remoteCameras[cameraID].SetCredentials(userName, password);
        }

        public void SetFPS(int cameraID, int fps)
        {
            remoteCameras[cameraID].SetFPS(fps);
        }

        public void StartBroadcasting(int cameraID)
        {
            remoteCameras[cameraID].StartBroadcasting();
        }

        public void StopBroadcasting(int cameraID)
        {
            remoteCameras[cameraID].StartBroadcasting();
        }

        public int GetFramesCounter(int cameraID)
        {
            return remoteCameras[cameraID].GetFramesCounter();
        }
    }
}