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

        int realFPS;
        private DispatcherTimer framesTimer;
        private DispatcherTimer fpsCounter;

		public CameraViewer()
		{
            client = new CloudObserverBroadcastServiceClient();
            client.ReadFrameCompleted += new EventHandler<ReadFrameCompletedEventArgs>(client_ReadFrameCompleted);
            framesTimer = new DispatcherTimer();
            framesTimer.Interval = new TimeSpan(0, 0, 0, 0, 40);
            framesTimer.Tick += new EventHandler(framesTimer_Tick);
            fpsCounter = new DispatcherTimer();
            fpsCounter.Interval = new TimeSpan(0, 0, 1);
            fpsCounter.Tick += new EventHandler(fpsCounter_Tick);

			InitializeComponent();
		}

        void fpsCounter_Tick(object sender, EventArgs e)
        {
            LabelRealFPS.Content = "Real FPS: " + realFPS;
            realFPS = 0;
        }

        void framesTimer_Tick(object sender, EventArgs e)
        {
            client.ReadFrameAsync(Int32.Parse(TextBoxCameraID.Text));
            realFPS++;
        }

        void client_ReadFrameCompleted(object sender, ReadFrameCompletedEventArgs e)
        {
            byte[] receivedImage = e.Result;
            BitmapImage bitmapImage = new BitmapImage();
            bitmapImage.SetSource(new MemoryStream(receivedImage));
            ImageFrame.Source = bitmapImage;
        }

        private void NumericUpDownFPS_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            framesTimer.Interval = new TimeSpan(0, 0, 0, 0, (int)(1000 / e.NewValue));
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