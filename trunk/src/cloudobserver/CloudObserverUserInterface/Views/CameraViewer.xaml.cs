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
            client.ReadFrameCompleted += new EventHandler<ReadFrameCompletedEventArgs>(client_ReadFrameCompleted);
            framesTimer = new DispatcherTimer();
            framesTimer.Interval = new TimeSpan(0, 0, 0, 0, 250);
            framesTimer.Tick += new EventHandler(framesTimer_Tick);
		}

        void framesTimer_Tick(object sender, EventArgs e)
        {
            client.ReadFrameAsync(Int32.Parse(TextBoxCameraID.Text));
        }

        void client_ReadFrameCompleted(object sender, ReadFrameCompletedEventArgs e)
        {
            byte[] receivedImage = e.Result;
            BitmapImage bitmapImage = new BitmapImage();
            bitmapImage.SetSource(new MemoryStream(receivedImage));
            ImageFrame.Source = bitmapImage;
        }

        private void ButtonStart_Click(object sender, RoutedEventArgs e)
        {
            framesTimer.Start();
        }

        private void ButtonStop_Click(object sender, RoutedEventArgs e)
        {
            framesTimer.Stop();
        }
	}
}