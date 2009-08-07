using System;
using System.ServiceModel;
using System.Collections.Generic;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class IPCamerasService : AbstractService, IPCamerasServiceContract
    {
        Dictionary<int, IPCamera> ipCameras;

        private ControllerServiceContract controllerService;
        private string broadcastServiceUri;
        
        public IPCamerasService()
        {
            ipCameras = new Dictionary<int, IPCamera>();
        }

        public new void SetControllerServiceUri(string controllerServiceUri)
        {
            base.SetControllerServiceUri(controllerServiceUri);
            controllerService = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceUri));
            broadcastServiceUri = controllerService.GetServiceUri(ServiceType.BroadcastService);
        }

        public void SetSource(int cameraID, string sourceType, string sourceUri)
        {
            if (!ipCameras.ContainsKey(cameraID))
            {
                if (sourceType.Equals("JPEG"))
                    ipCameras[cameraID] = new IPCameraJpegFormat(cameraID, broadcastServiceUri);
                if (sourceType.Equals("MJPG"))
                    ipCameras[cameraID] = new IPCameraMjpegFormat(cameraID, broadcastServiceUri);
            }
            ipCameras[cameraID].SetSource(sourceUri);
        }

        public void SetFPSLimit(int cameraID, int fpsLimit)
        {
            ipCameras[cameraID].SetFPSLimit(fpsLimit);
        }

        public void SetCredentials(int cameraID, string userName, string password)
        {
            ipCameras[cameraID].SetCredentials(userName, password);
        }

        public void StartBroadcasting(int cameraID)
        {
            ipCameras[cameraID].StartBroadcasting();
        }

        public void StopBroadcasting(int cameraID)
        {
            ipCameras[cameraID].StartBroadcasting();
        }

        public int GetFramesCounter(int cameraID)
        {
            return ipCameras[cameraID].GetFramesCounter();
        }
    }
}