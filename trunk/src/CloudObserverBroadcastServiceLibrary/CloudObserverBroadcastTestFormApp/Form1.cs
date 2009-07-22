using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.IO;

namespace CloudObserverBroadcastTestFormApp
{
    public partial class Form1 : Form
    {
        public static byte[] BmpToBytes(Bitmap bmp)
        {
            byte[] data = new byte[0];
            using (MemoryStream ms = new MemoryStream())
            {
                bmp.Save(ms, ImageFormat.Bmp);
                ms.Seek(0, 0);
                data = ms.ToArray();
            }
            return data;
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

        public Form1()
        {
            InitializeComponent();
            label1.Text = "From 1 user";
            label2.Text = "From 2 user";
            pictureBox1.Show();
            pictureBox2.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //We have user 1 and user 2. One comera which takes pictures from /pictures/snapshotX and send it to service.
            //two users try to receive that images.
            //They have IDs camera - 1 and user 1 and 2.

            CloudObserverBroadcastService.CloudObserverBroadcastServiceClient cameraProxy = new CloudObserverBroadcastService.CloudObserverBroadcastServiceClient();
            CloudObserverBroadcastService.CloudObserverBroadcastServiceClient client1proxy = new CloudObserverBroadcastService.CloudObserverBroadcastServiceClient();
            CloudObserverBroadcastService.CloudObserverBroadcastServiceClient client2proxy = new CloudObserverBroadcastService.CloudObserverBroadcastServiceClient();

            cameraProxy.setMeAsCamera(1);
            client1proxy.bindMeToCamera(1, 1);
            client2proxy.bindMeToCamera(2, 1);

            //Now we try to send endless sequence of pictures.

            for (int i = 0; (i <= 9) && (i >= 0); i++)
            {
                Bitmap cameraImage = new Bitmap("F:\\pictures\\snapshot" + i.ToString() + ".bmp");

                byte[] cameraImageToArray = new byte[0];
                cameraImageToArray = BmpToBytes(cameraImage);

                cameraProxy.setNextFrame(cameraImageToArray);

                //Let us wait
                //System.Threading.Thread.Sleep(50);

                Bitmap Client1Image = BmpFromBytes(client1proxy.getNextFrame(1));
                Bitmap Client2Image = BmpFromBytes(client1proxy.getNextFrame(1));

                pictureBox1.Image = (Image)(Client1Image);
                pictureBox2.Image = (Image)(Client2Image);

                pictureBox1.Refresh();
                pictureBox2.Refresh();

                if (i == 9)
                {
                    i = 0;
                }
            }
        }



    }
}
