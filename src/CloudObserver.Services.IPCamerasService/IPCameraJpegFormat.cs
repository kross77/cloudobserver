using System;
using System.Net;
using System.Timers;
using System.ServiceModel;
using System.Collections.Generic;

namespace CloudObserver.Services
{
    public class IPCameraJpegFormat : IPCamera
    {
        int cameraID;
        string sourceUri;
        string userName = "";
        string password = "";
        int framesCounter = 0;
        Timer broadcastingTimer;
        BroadcastServiceContract broadcastServiceClient;

        public IPCameraJpegFormat(int cameraID, string broadcastServiceUri)
        {
            this.cameraID = cameraID;

            broadcastServiceClient = ChannelFactory<BroadcastServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(broadcastServiceUri));

            broadcastingTimer = new Timer(1000);
            broadcastingTimer.Elapsed += new ElapsedEventHandler(broadcastingTimer_Elapsed);
        }

        private void broadcastingTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            try
            {
                WebClient webClient = new WebClient();
                webClient.Credentials = new NetworkCredential(userName, password);
                broadcastServiceClient.WriteFrame(cameraID, webClient.DownloadData(sourceUri));
                framesCounter++;
            }
            catch (Exception)
            {
            }
        }

        public override void SetSource(string sourceUri)
        {
            this.sourceUri = sourceUri;
        }

        public override void SetCredentials(string userName, string password)
        {
            this.userName = userName;
            this.password = password;
        }

        public override void SetFPSLimit(int fpsLimit)
        {
            broadcastingTimer.Interval = 1000 / fpsLimit;
        }

        public override void StartBroadcasting()
        {
            broadcastingTimer.Start();
        }

        public override void StopBroadcasting()
        {
            broadcastingTimer.Stop();
        }

        public override int GetFramesCounter()
        {
            return framesCounter;
        }
    }
}