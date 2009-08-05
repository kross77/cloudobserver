using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class VirtualCamerasService : Service, VirtualCamerasServiceContract
    {
        Dictionary<int, VirtualCamera> virtualCameras;

        private ControllerServiceContract controllerService;
        private string broadcastServiceUri;
        
        public VirtualCamerasService()
        {
            virtualCameras = new Dictionary<int, VirtualCamera>();
        }

        public new void SetControllerServiceUri(string controllerServiceUri)
        {
            base.SetControllerServiceUri(controllerServiceUri);
            controllerService = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceUri));
            broadcastServiceUri = controllerService.GetServiceUri(ServiceType.BroadcastService);
        }

        public void SetSource(int cameraID, string source)
        {
            if (!virtualCameras.ContainsKey(cameraID))
                virtualCameras[cameraID] = new VirtualCamera(cameraID, broadcastServiceUri);
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