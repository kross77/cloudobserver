using System;
using System.Net;
using System.Timers;
using System.ServiceModel;
using CloudObserverBroadcastServiceLibrary;

namespace CloudObserverRemoteCamerasServiceLibrary
{
    class RemoteCamera
    {
        int cameraID;
        string source;
        string userName;
        string password;
        int framesCounter = 0;
        Timer broadcastingTimer;
        ICloudObserverBroadcastService broadcastServiceClient;

        public RemoteCamera(int cameraID, string cloudObserverBroadcastServiceUri)
        {
            this.cameraID = cameraID;

            broadcastServiceClient = ChannelFactory<ICloudObserverBroadcastService>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(cloudObserverBroadcastServiceUri));

            broadcastingTimer = new Timer(1000);
            broadcastingTimer.Elapsed += new ElapsedEventHandler(broadcastingTimer_Elapsed);
        }

        private void broadcastingTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            HttpWebRequest httpWebRequest = (HttpWebRequest)HttpWebRequest.Create(source);
            httpWebRequest.Credentials = new NetworkCredential(userName, password);
            WebClient webClient = new WebClient();
            HttpWebResponse httpWebResponse = (HttpWebResponse)httpWebRequest.GetResponse();
            if (httpWebRequest.ContentType == "image/jpeg")
                broadcastServiceClient.WriteFrame(cameraID, webClient.DownloadData(source));
            httpWebResponse.Close();
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