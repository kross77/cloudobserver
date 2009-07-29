using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using CloudObserverUserInterface.CloudObserverBroadcastServiceReference;
using System.Windows.Media.Imaging;
using System.IO;

namespace CloudObserverUserInterface
{
	public partial class cameraViewer : UserControl
	{
        private bool cameraConnected;
        private string UID;
        CloudObserverBroadcastServiceReference.CloudObserverBroadcastServiceClient proxy;

		public cameraViewer()
		{
			// Required to initialize variables
			InitializeComponent();
            cameraConnected = false;
            UID = "unic";
		}

        private void StopButton_Click(object sender, RoutedEventArgs e)
        {
            cameraConnected = false;
        }

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            proxy = new CloudObserverBroadcastServiceClient();
            UID = UIDTextBox.Text;
            proxy.GetNextFrameCompleted += new EventHandler<GetNextFrameCompletedEventArgs>(client_GetNextFrameCompleted);
            proxy.BindMeToCameraCompleted += new EventHandler<System.ComponentModel.AsyncCompletedEventArgs>(proxy_BindMeToCameraCompleted);
            proxy.BindMeToCameraAsync(Convert.ToInt32(UserIDTextBox.Text),Convert.ToInt32(CameraIDTextBox.Text),UID);
            cameraConnected = true;
            while (cameraConnected)
            {
                System.Threading.Thread.Sleep(250);
                proxy.GetNextFrameAsync(Convert.ToInt32(CameraIDTextBox.Text), UID);
            }
        }

        void proxy_BindMeToCameraCompleted(object sender, System.ComponentModel.AsyncCompletedEventArgs e)
        {
            CameraIDTextBox.Text = "cameraBinded";
            throw new NotImplementedException();
        }

        private void client_GetNextFrameCompleted(object sender, GetNextFrameCompletedEventArgs e)
        {
            byte[] receivedImage = e.Result;
            BitmapImage bmi = new BitmapImage();
            System.IO.Stream s = new System.IO.MemoryStream(receivedImage);
            bmi.SetSource(s);
            ImageBox.Source = bmi;
        }
	}
}