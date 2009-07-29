using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.IO;

namespace ShowWithCameras
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        const int magicConst = 5;
        string[] UIDs = new string[magicConst];

        private string GetImageURI(int num)
        {
            return (@"http://www.campus.spbu.ru/images/webcam/camera" + num.ToString() + ".jpg");
        }

        public static Bitmap BmpFromBytes(byte[] bytes)
        {
            Bitmap bmp;
            using (MemoryStream ms = new MemoryStream())
            {
                ms.Write(bytes, 0, bytes.Length);
                bmp = new Bitmap(ms);
            }
            return bmp;
        }

        private void StartButton_Click(object sender, EventArgs e)
        {



            while (true)
            {
                for (int i = 0; i <= magicConst - 1; i++)
                {
                    string webAddress = GetImageURI(i + 1);
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
                    pictureBox.Image = (Image)BmpFromBytes(byteImage);
                    pictureBox.Refresh();
                    System.Threading.Thread.Sleep(500);
                }
            }
        }
        }
    }
