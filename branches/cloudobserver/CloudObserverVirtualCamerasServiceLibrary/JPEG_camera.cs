using System;
using System.Collections.Generic;
using System.Text;
using System.Timers;
using System.ServiceModel;
using CloudObserverBroadcastServiceLibrary;
using System.Net;

namespace CloudObserverVirtualCamerasServiceLibrary
{
    class JPEG_camera : VirtualCamera
    {
        int cameraID;
        string source;
        string userName;
        string password;
        int framesCounter = 0;
        Timer broadcastingTimer;
        ICloudObserverBroadcastService broadcastServiceClient;

        public JPEG_camera(int cameraID, string cloudObserverBroadcastServiceUri)
        {
            this.cameraID = cameraID;

            broadcastServiceClient = ChannelFactory<ICloudObserverBroadcastService>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(cloudObserverBroadcastServiceUri));

            broadcastingTimer = new Timer(1000);
            broadcastingTimer.Elapsed += new ElapsedEventHandler(broadcastingTimer_Elapsed);
        }

        private void broadcastingTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            //HttpWebRequest httpWebRequest = (HttpWebRequest)HttpWebRequest.Create(source);
            //httpWebRequest.Credentials = new NetworkCredential(userName, password);
            WebClient webClient = new WebClient();
            webClient.Credentials = new NetworkCredential(userName, password);
            //HttpWebResponse httpWebResponse = (HttpWebResponse)httpWebRequest.GetResponse();
            //if (httpWebRequest.ContentType == "image/jpeg")
            broadcastServiceClient.WriteFrame(cameraID, webClient.DownloadData(source),DateTime.Now,false);
            //httpWebResponse.Close();
            framesCounter++;
        }

        public override void SetSource(string source)
        {
            this.source = source;
        }

        public override void SetCredentials(string userName, string password)
        {
            this.userName = userName;
            this.password = password;
        }

        public override void SetFPS(int fps)
        {
            broadcastingTimer.Interval = 1000 / fps;
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
