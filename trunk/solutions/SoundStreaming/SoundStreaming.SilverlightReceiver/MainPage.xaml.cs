using System;
using System.ServiceModel;
using System.Windows;
using System.Windows.Controls;

using CloudObserver.Silverlight;

namespace SoundStreaming.SilverlightReceiver
{
    public partial class MainPage : UserControl
    {
        StreamingServiceMediaStreamSource streamingServiceMediaStreamSource;

        public MainPage()
        {
            InitializeComponent();

            SetMediaStreamSource(this, EventArgs.Empty);
        }

        void SetMediaStreamSource(object sender, EventArgs e)
        {
            streamingServiceMediaStreamSource = new StreamingServiceMediaStreamSource(textBoxStreamingServiceUri.Text);
            streamingServiceMediaStreamSource.NeedsReloading += new EventHandler(SetMediaStreamSource);
            PlaybackMediaElement.SetSource(streamingServiceMediaStreamSource);
        }

        private void buttonPlayStop_Click(object sender, RoutedEventArgs e)
        {
            switch (buttonPlayStop.Content.ToString())
            {
                case "Play":
                    PlaybackMediaElement.Play();
                    buttonPlayStop.Content = "Stop";
                    break;
                case "Stop":
                    PlaybackMediaElement.Pause();
                    buttonPlayStop.Content = "Play";
                    break;
            }
        }
    }
}