using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CloudObserverCampusCamerasStreaming.CloudObserverBroadcastServiceReference;
using System.Drawing;
using System.Net;

namespace CloudObserverCampusCamerasStreaming
{
    public class CampusCamerasStreaming : ICloudObserverCampusCamerasStreaming
    {
        const int magicConst = 5;
        string[] UIDs = new string[magicConst];

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

            CloudObserverBroadcastServiceClient proxy = new CloudObserverBroadcastServiceClient();
            fillUIDs();
            for (int i = 0; i <= magicConst - 1; i++)
            {
                proxy.SetMeAsCamera(1000 + i, UIDs[i]);
            }
            while (true)
            {
                for (int i = 0; i <= magicConst - 1; i++)
                {
                    string webAddress = GetImageURI(i+1);
                    byte[] byteImage = new byte[0];
                    // Два объекта для получения информации о предполагаемом скачиваемом изображении
                    HttpWebRequest httpWReq = (HttpWebRequest)WebRequest.Create(webAddress);
                    WebClient httpClient = new WebClient();
                    HttpWebResponse httpWResp = (HttpWebResponse)httpWReq.GetResponse();
                    // Проверяем,  действительно ли по данному адресу находится изображение
                    if (httpWResp.ContentType == "image/jpeg")
                    {
                        try
                        {
                            // Скачиваем
                            byteImage = httpClient.DownloadData(webAddress);
                        }
                        catch (WebException ex)
                        {

                        }
                    }
                    httpWResp.Close();
                    proxy.SetNextFrame(byteImage, UIDs[i]);
                    System.Threading.Thread.Sleep(50000);
                }
            }
        }









    }
}
