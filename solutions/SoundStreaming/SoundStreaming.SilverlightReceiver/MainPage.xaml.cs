using System;
using System.Windows.Controls;

using CloudObserver.Silverlight.Formats.Audio;
using CloudObserver.Silverlight.MediaStreamSources.Pcm;

namespace SoundStreaming.SilverlightReceiver
{
    public partial class MainPage : UserControl
    {
        StreamingServicePcmMediaStreamSource streamingServicePcmMediaStreamSource;

        public MainPage()
        {
            InitializeComponent();

            streamingServicePcmMediaStreamSource = new StreamingServicePcmMediaStreamSource(new PcmAudioFormat(44100, 16, 2), "http://127.0.0.1:9000/StreamingService");
            PlaybackMediaElement.SetSource(streamingServicePcmMediaStreamSource);
        }

        private void buttonConnect_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            streamingServicePcmMediaStreamSource = new StreamingServicePcmMediaStreamSource(new PcmAudioFormat(44100, 16, 2), textBoxStreamingServiceUri.Text);
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
    }
}