using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Windows.Threading;
using CloudObserverUserInterface.CloudObserverBroadcastServiceReference;

namespace CloudObserverUserInterface
{
	public partial class CameraViewer : UserControl
	{
        CloudObserverBroadcastServiceClient client;

        private string UID;
        private DispatcherTimer framesTimer;

		public CameraViewer()
		{
			InitializeComponent();

            client = new CloudObserverBroadcastServiceClient();
            UID = "unic";
            framesTimer = new DispatcherTimer();
            framesTimer.Interval = new TimeSpan(0, 0, 0, 0, 250);
            framesTimer.Tick += new EventHandler(framesTimer_Tick);
		}

        void framesTimer_Tick(object sender, EventArgs e)
        {
            client.GetNextFrameAsync(Int32.Parse(CameraIDTextBox.Text), UID);
        }

        private void StopButton_Click(object sender, RoutedEventArgs e)
        {
            framesTimer.Stop();
        }

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            UID = UIDTextBox.Text;
            client.BindMeToCameraCompleted += new EventHandler<System.ComponentModel.AsyncCompletedEventArgs>(client_BindMeToCameraCompleted);
            client.BindMeToCameraAsync(Int32.Parse(UserIDTextBox.Text), Int32.Parse(CameraIDTextBox.Text), UID);
            client.GetNextFrameCompleted += new EventHandler<GetNextFrameCompletedEventArgs>(client_GetNextFrameCompleted);
            framesTimer.Start();
        }

        void client_GetNextFrameCompleted(object sender, GetNextFrameCompletedEventArgs e)
        {
            byte[] receivedImage = e.Result;
            BitmapImage bitmapImage = new BitmapImage();
            bitmapImage.SetSource(new MemoryStream(receivedImage));
            ImageBox.Source = bitmapImage;
        }

        void client_BindMeToCameraCompleted(object sender, System.ComponentModel.AsyncCompletedEventArgs e)
        {
            new MessageWindow("Binded to camera.", "Debug message", new TimeSpan(0, 0, 1));
        }
	}
}