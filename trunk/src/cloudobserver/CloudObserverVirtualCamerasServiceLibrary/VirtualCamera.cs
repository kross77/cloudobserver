using System;
using System.Net;
using System.Timers;
using System.Collections.Generic;
using System.ServiceModel;
using CloudObserverBroadcastServiceLibrary;

namespace CloudObserverVirtualCamerasServiceLibrary
{
    class VirtualCamera
    {
        int cameraID;
        int sources = 0;
        int position = 0;
        int cyclePosition = 0;
        int framesCounter = 0;
        List<string> uri;
        List<int> framesPerCycle;
        Timer broadcastingTimer;
        ICloudObserverBroadcastService client;

        public VirtualCamera(int cameraID, string cloudObserverBroadcastServiceUri)
        {
            this.cameraID = cameraID;

            uri = new List<string>();
            framesPerCycle = new List<int>();

            client = ChannelFactory<ICloudObserverBroadcastService>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(cloudObserverBroadcastServiceUri));

            broadcastingTimer = new Timer(1000);
            broadcastingTimer.Elapsed += new ElapsedEventHandler(broadcastingTimer_Elapsed);
        }

        void broadcastingTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            framesCounter++;
            HttpWebRequest httpWebRequest = (HttpWebRequest)HttpWebRequest.Create(uri[position]);
            WebClient webClient = new WebClient();
            HttpWebResponse httpWebResponse = (HttpWebResponse)httpWebRequest.GetResponse();
            if (httpWebResponse.ContentType == "image/jpeg")
                client.WriteFrame(cameraID, webClient.DownloadData(uri[position]));
            httpWebResponse.Close();
            position = (position + 1) % sources;
            //cyclePosition++;
            //if (cyclePosition > framesPerCycle[position])
            //{
            //    position++;
            //    if (position > sources) position = 0;
            //    cyclePosition = 0;
            //}
        }

        public void AddSource(string uri, int framesPerCycle)
        {
            sources++;
            this.uri.Add(uri);
            this.framesPerCycle.Add(framesPerCycle);
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

        public string[] GetSources()
        {
            return uri.ToArray();
        }

        public int GetFramesCounter()
        {
            return framesCounter;
        }
    }
}