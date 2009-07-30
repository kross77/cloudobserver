using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CloudObserverCampusCamerasStreaming.CloudObserverBroadcastServiceReference;
using System.Drawing;
using System.Net;
using System.ServiceModel;
using System.Threading;

namespace CloudObserverCampusCamerasStreamingServiceLibrary
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudObserverCampusCamerasStreamingService : ICloudObserverCampusCamerasStreamingService
    {
        private const int magicConst = 5;
        private string[] UIDs = new string[magicConst];
        private bool started = false;

        private string GetImageURI(int num)
        {
            return (@"http://www.campus.spbu.ru/images/webcam/camera" + num.ToString() + ".jpg");
        }

        private void fillUIDs()
        {
            for (int i = 0; i <= magicConst-1; i++)
            {
                UIDs[i] = "fuck" + i.ToString();
            }
        }

        public void startService()
        {
            started = true;
            new Thread(transmission).Start();         
        }

        public void stopService()
        {
            started = false;
        }

        private void transmission()
        {
            CloudObserverBroadcastServiceClient proxy = new CloudObserverBroadcastServiceClient();
            fillUIDs();
            for (int i = 0; i <= magicConst - 1; i++)
            {
                proxy.SetMeAsCamera(1000 + i, UIDs[i]);
            }
            while (started)
            {
                for (int i = 0; (i <= magicConst - 1) & started; i++)
                {
                    string webAddress = GetImageURI(i + 1);
                    byte[] byteImage = new byte[0];
                    // Two object for receiving of infomation about downloaded image
                    HttpWebRequest httpWReq = (HttpWebRequest)WebRequest.Create(webAddress);
                    WebClient httpClient = new WebClient();
                    HttpWebResponse httpWResp = (HttpWebResponse)httpWReq.GetResponse();
                    // Check, If there is a picture really
                    if (httpWResp.ContentType == "image/jpeg")
                    {
                        try
                        {
                            // Download
                            byteImage = httpClient.DownloadData(webAddress);
                        }
                        catch (WebException ex)
                        {

                        }
                    }
                    httpWResp.Close();
                    proxy.SetNextFrame(byteImage, UIDs[i]);
                    System.Threading.Thread.Sleep(500);
                }
            }
            proxy.Close();
        }
    }
}
