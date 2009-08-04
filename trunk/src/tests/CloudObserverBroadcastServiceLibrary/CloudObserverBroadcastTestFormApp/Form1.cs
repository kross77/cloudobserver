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

        public static returnProxy()
        {
            string BaseAddress = "net.tcp://" + Environment.MachineName + ":8002/Service";
            Uri baseUri =  new Uri(BaseAddress);
            ServiceHost TcpServiceHost = new ServiceHost(typeof(ServiceClassLibrary.TcpService),baseUri);
            TcpServiceHost.AddServiceEndpoint(typeof(ITcpService), GetBinding(), "ITcpService");
            TcpServiceHost.Open();
            ChannelFactory<ServiceClassLibrary.ITcpService> factory = new ChannelFactory<ITcpService>(GetBinding(), new EndpointAddress(BaseAddress + "/ITCPService"));
            ServiceClassLibrary.ITcpService proxy = factory.CreateChannel();
            Console.WriteLine(proxy.ping());
            Console.ReadLine();
            ((IClientChannel)proxy).Close();
            factory.Close();
            TcpServiceHost.Close();
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

            int endpointsNumber = 6;
            string[] endpointNames = new string[endpointsNumber];
            endpointNames[0] = "WSHttpBinding_ICloudObserverBroadcastService";
            endpointNames[1] = "WSHttpBinding_ICloudObserverBroadcastService1";
            endpointNames[2] = "NetTcpBinding_ICloudObserverBroadcastService";
            endpointNames[3] = "NetTcpBinding_ICloudObserverBroadcastService1";
            endpointNames[4] = "NetTcpBinding_ICloudObserverBroadcastService2";
            endpointNames[5] = "NetTcpBinding_ICloudObserverBroadcastService3";

            for (int endpoint = 3; endpoint <= (endpointsNumber - 1); endpoint++)
            {

                CloudObserverBroadcastService.CloudObserverBroadcastServiceClient cameraProxy = new CloudObserverBroadcastService.CloudObserverBroadcastServiceClient(endpointNames[endpoint]);
                CloudObserverBroadcastService.CloudObserverBroadcastServiceClient client1proxy = new CloudObserverBroadcastService.CloudObserverBroadcastServiceClient(endpointNames[endpoint]);
                CloudObserverBroadcastService.CloudObserverBroadcastServiceClient client2proxy = new CloudObserverBroadcastService.CloudObserverBroadcastServiceClient(endpointNames[endpoint]);

                int cameraIdent = (endpoint + 1) * 10 + 1;
                int client1Ident = (endpoint + 2) * 10 + 4;
                int client2Ident = (endpoint + 3) * 10 + 5;



                cameraProxy.setMeAsCamera(1, cameraIdent);
                client1proxy.bindMeToCamera(1, 1, client1Ident);
                client2proxy.bindMeToCamera(2, 1,client2Ident);


                //Now we try to send sequence of pictures by selected endpoint and quality.

                for (int qual = 0; qual <= 2; qual++)
                {
                    string quality = "";

                    switch (qual)
                    {
                        case 0: 
                            quality = "High";
                            break;
                        case 1: 
                            quality = "Middle";
                            break;
                        case 2:
                            quality = "Low";
                            break;
                    }

                    int averSize = 0;

                    DateTime startTime = DateTime.Now;

                    for (int i = 0; (i <= 9) && (i >= 0); i++)
                    {
                        Bitmap cameraImage = new Bitmap("F:\\pictures" + quality + "\\snapshot" + i.ToString() + ".bmp");

                        byte[] cameraImageToArray;
                        cameraImageToArray = BmpToBytes(cameraImage);
                        //averSize = sizeof(cameraImageToArray);

                        cameraProxy.setNextFrame(cameraImageToArray,cameraIdent);

                        Bitmap Client1Image = BmpFromBytes(client1proxy.getNextFrame(1, client1Ident));
                        Bitmap Client2Image = BmpFromBytes(client1proxy.getNextFrame(1, client2Ident));

                        pictureBox1.Image = (Image)(Client1Image);
                        pictureBox2.Image = (Image)(Client2Image);

                        averSize = cameraImageToArray.Length;

                        pictureBox1.Refresh();
                        pictureBox2.Refresh();
                    }

                    DateTime finishTime = DateTime.Now;
                    TimeSpan deltaTime = finishTime - startTime;
                    long Time = (long)deltaTime.TotalMilliseconds;

                    textBox1.Text += "START_OF_SECTION:\r\n";
                    textBox1.Text += "\tUsed Time for transfer(milliseconds) : " + Time.ToString() + "; \r\n";
                    textBox1.Text += "\tAverage picture size(B) : " + averSize.ToString() + "; \r\n";
                    textBox1.Text += "\tAverage data transfered(B) : " + (averSize * 3).ToString() + "; \r\n";
                    textBox1.Text += "\tEndpointName : " + cameraProxy.Endpoint.Name + "; \r\n";
                    textBox1.Text += "\tBinding name : " + cameraProxy.Endpoint.Binding.Name + "; \r\n";
                    textBox1.Text += "END_OF_SECTION\r\n";
                    textBox1.Refresh();

                }

                cameraProxy.clean();
                client1proxy.clean();
                client1proxy.clean();

                cameraProxy.Close();
                client1proxy.Close();
                client2proxy.Close();
            }
        }
    }
}
