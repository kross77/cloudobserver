using System;
using System.Windows.Controls;

using CloudObserver.Services.StreamingService;

namespace SoundStreaming.SilverlightReceiver
{
    public partial class MainPage : UserControl
    {
        #region Fields

        StreamingServicePcmMediaStreamSource streamingServicePcmMediaStreamSource;

        #endregion

        #region Constructors

        public MainPage()
        {
            InitializeComponent();

            streamingServicePcmMediaStreamSource = new StreamingServicePcmMediaStreamSource("http://127.0.0.1:9000/StreamingService");
            PlaybackMediaElement.SetSource(streamingServicePcmMediaStreamSource);
        }

        #endregion

        #region Event Handlers

        private void buttonConnect_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            streamingServicePcmMediaStreamSource = new StreamingServicePcmMediaStreamSource(textBoxStreamingServiceUri.Text);
            PlaybackMediaElement.SetSource(streamingServicePcmMediaStreamSource);
        }

        private void buttonPlayStop_Click(object sender, System.Windows.RoutedEventArgs e)
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

        #endregion
    }
}