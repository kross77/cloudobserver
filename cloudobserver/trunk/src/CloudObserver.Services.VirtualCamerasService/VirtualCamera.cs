using System;
using System.Net;
using System.Timers;
using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserver.Services
{
    class VirtualCamera
    {
        int cameraID;
        string source;
        string userName;
        string password;
        int framesCounter = 0;
        Timer broadcastingTimer;
        BroadcastServiceContract broadcastService;

        public VirtualCamera(int cameraID, string broadcastServiceUri)
        {
            this.cameraID = cameraID;

            broadcastService = ChannelFactory<BroadcastServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(broadcastServiceUri));

            broadcastingTimer = new Timer(1000);
            broadcastingTimer.Elapsed += new ElapsedEventHandler(broadcastingTimer_Elapsed);
        }

        private void broadcastingTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            WebClient webClient = new WebClient();
            webClient.Credentials = new NetworkCredential(userName, password);
            broadcastService.WriteFrame(cameraID, webClient.DownloadData(source));
            framesCounter++;
        }

        public void SetSource(string source)
        {
            this.source = source;
        }

        public void SetCredentials(string userName, string password)
        {
            this.userName = userName;
            this.password = password;
        }

        public void SetFPS(int fps)
        {
            broadcastingTimer.Interval = 1000 / fps;
        }

        public void StartBroadcasting()
        {
            broadcastingTimer.Start();
        }

        public void StopBroadcasting()
        {
            broadcastingTimer.Stop();
        }

        public int GetFramesCounter()
        {
            return framesCounter;
        }
    }
}