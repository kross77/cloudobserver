using System;
using System.IO;
using System.Timers;
using System.ServiceModel;
using CloudObserver.Services;

namespace CloudObserver.Broadcaster
{
    public class Broadcast
    {
        private int cameraID;
        private BroadcastType broadcastType;
        private BroadcastFormat broadcastFormat;
        private BroadcastSource broadcastSource;
        private int maxFPS;
        private bool running;

        private int currentFrame;
        private Timer broadcastingTimer;
        private ControllerServiceContract controllerServiceClient;
        private BroadcastServiceContract broadcastServiceClient;
        private IPCamerasServiceContract ipCamerasServiceClient;

        public bool Running
        {
            get { return running; }
        }

        public Broadcast(int cameraID, BroadcastType broadcastType, BroadcastFormat broadcastFormat, BroadcastSource broadcastSource, int maxFPS)
        {
            this.cameraID = cameraID;
            this.broadcastType = broadcastType;
            this.broadcastFormat = broadcastFormat;
            this.broadcastSource = broadcastSource;
            this.maxFPS = maxFPS;
        }

        public int GetCameraID()
        {
            return cameraID;
        }

        public BroadcastType GetBroadcastType()
        {
            return broadcastType;
        }

        public BroadcastFormat GetBroadcastFormat()
        {
            return broadcastFormat;
        }

        public BroadcastSource GetBroadcastSource()
        {
            return broadcastSource;
        }

        public int GetMaxFPS()
        {
            return maxFPS;
        }

        public void SetControllerServiceClient(ControllerServiceContract controllerServiceClient)
        {
            this.controllerServiceClient = controllerServiceClient;
        }

        public void Start()
        {
            broadcastServiceClient = ChannelFactory<BroadcastServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceClient.GetServiceUri(ServiceType.BroadcastService)));
            if (broadcastType == BroadcastType.VirtualClientService)
                ipCamerasServiceClient = ChannelFactory<IPCamerasServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceClient.GetServiceUri(ServiceType.IPCamerasService)));
            switch (broadcastSource.GetBroadcastSourceType())
            {
                case BroadcastSourceType.LocalStorage:
                    StartLocalStorageBroadcasting();
                    break;
                case BroadcastSourceType.CloudObserverCamera:
                    StartCloudObserverCameraBroadcasting();
                    break;
                case BroadcastSourceType.IPCamera:
                    StartIPCameraBroadcasting();
                    break;
            }
            running = true;
        }

        public void Stop()
        {
            switch (broadcastSource.GetBroadcastSourceType())
            {
                case BroadcastSourceType.LocalStorage:
                    StopLocalStorageBroadcasting();
                    break;
                case BroadcastSourceType.CloudObserverCamera:
                    StopCloudObserverCameraBroadcasting();
                    break;
                case BroadcastSourceType.IPCamera:
                    StopIPCameraBroadcasting();
                    break;
            }
            running = false;
        }

        private void StartLocalStorageBroadcasting()
        {
            currentFrame = 0;
            broadcastingTimer = new Timer(1000 / maxFPS);
            broadcastingTimer.Elapsed += new ElapsedEventHandler(broadcastingTimer_Elapsed);
            broadcastingTimer.Start();
        }

        private void broadcastingTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            broadcastServiceClient.WriteFrame(cameraID, File.ReadAllBytes(broadcastSource.Frames[currentFrame]));
            currentFrame = (currentFrame + 1) % broadcastSource.Frames.Length;
        }

        private void StopLocalStorageBroadcasting()
        {
            broadcastingTimer.Stop();
        }

        private void StartCloudObserverCameraBroadcasting()
        {
            switch (broadcastType)
            {
                case BroadcastType.DirectBroadcasting:
                    break;
                case BroadcastType.VirtualClientService:
                    break;
            }
        }

        private void StopCloudObserverCameraBroadcasting()
        {
        }

        private void StartIPCameraBroadcasting()
        {
            switch (broadcastType)
            {
                case BroadcastType.DirectBroadcasting:
                    break;
                case BroadcastType.VirtualClientService:
                    //ipCamerasServiceClient.SetSource(cameraID, broadcastType, broadcastSource.Uri);
                    if (broadcastSource.ProvideCredentials) ipCamerasServiceClient.SetCredentials(cameraID, broadcastSource.UserName, broadcastSource.Password);
                    ipCamerasServiceClient.SetFPSLimit(cameraID, maxFPS);
                    ipCamerasServiceClient.StartBroadcasting(cameraID);
                    break;
            }
        }

        private void StopIPCameraBroadcasting()
        {
            switch (broadcastType)
            {
                case BroadcastType.DirectBroadcasting:
                    break;
                case BroadcastType.VirtualClientService:
                    ipCamerasServiceClient.StopBroadcasting(cameraID);
                    break;
            }
        }
    }
}