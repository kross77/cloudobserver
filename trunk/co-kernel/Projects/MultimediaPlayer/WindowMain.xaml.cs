using System;
using System.IO;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;

using Mp3Sharp;
using Microsoft.DirectX.DirectSound;

namespace MultimediaPlayer
{
    public partial class WindowMain : Window
    {
        private Device device;
        private StreamedMp3Sound streamedMp3Sound = null;
        private bool playing = false;

        public WindowMain()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            device = new Device();
            device.SetCooperativeLevel(new WindowInteropHelper(this).Handle, CooperativeLevel.Priority);
        }

        private void buttonEldoradioPlayStop_Click(object sender, RoutedEventArgs e)
        {
            if (buttonEldoradioPlayStop.Content.ToString() == "Play")
            {
                if (playing)
                    streamedMp3Sound.Stop();
                buttonEldoradioPlayStop.Content = "Stop";
                buttonLoveRadioPlayStop.Content = "Play";
                buttonKCDXPlayStop.Content = "Play";
                buttonOtherPlayStop.Content = "Play";
                streamedMp3Sound = new StreamedMp3Sound(device, new Mp3Stream(WebRequest.Create(textBoxEldoradioUri.Text).GetResponse().GetResponseStream()));
                streamedMp3Sound.Play();
                playing = true;
            }
            else
            {
                buttonEldoradioPlayStop.Content = "Play";
                streamedMp3Sound.Stop();
                playing = false;
            }
        }

        private void buttonLoveRadioPlayStop_Click(object sender, RoutedEventArgs e)
        {
            if (buttonLoveRadioPlayStop.Content.ToString() == "Play")
            {
                if (playing)
                    streamedMp3Sound.Stop();
                buttonEldoradioPlayStop.Content = "Play";
                buttonLoveRadioPlayStop.Content = "Stop";
                buttonKCDXPlayStop.Content = "Play";
                buttonOtherPlayStop.Content = "Play";
                streamedMp3Sound = new StreamedMp3Sound(device, new Mp3Stream(WebRequest.Create(textBoxLoveRadioUri.Text).GetResponse().GetResponseStream()));
                streamedMp3Sound.Play();
                playing = true;
            }
            else
            {
                buttonLoveRadioPlayStop.Content = "Play";
                streamedMp3Sound.Stop();
                playing = false;
            }
        }

        private void buttonKCDXPlayStop_Click(object sender, RoutedEventArgs e)
        {
            if (buttonKCDXPlayStop.Content.ToString() == "Play")
            {
                if (playing)
                    streamedMp3Sound.Stop();
                buttonEldoradioPlayStop.Content = "Play";
                buttonLoveRadioPlayStop.Content = "Play";
                buttonKCDXPlayStop.Content = "Stop";
                buttonOtherPlayStop.Content = "Play";
                streamedMp3Sound = new StreamedMp3Sound(device, new Mp3Stream(WebRequest.Create(textBoxKCDXUri.Text).GetResponse().GetResponseStream()));
                streamedMp3Sound.Play();
                playing = true;
            }
            else
            {
                buttonKCDXPlayStop.Content = "Play";
                streamedMp3Sound.Stop();
                playing = false;
            }
        }

        private void buttonOtherPlayStop_Click(object sender, RoutedEventArgs e)
        {
            if (buttonOtherPlayStop.Content.ToString() == "Play")
            {
                if (playing)
                    streamedMp3Sound.Stop();
                buttonEldoradioPlayStop.Content = "Play";
                buttonLoveRadioPlayStop.Content = "Play";
                buttonKCDXPlayStop.Content = "Play";
                buttonOtherPlayStop.Content = "Stop";
                textBoxOtherUri.IsReadOnly = true;
                streamedMp3Sound = new StreamedMp3Sound(device, new Mp3Stream(WebRequest.Create(textBoxOtherUri.Text).GetResponse().GetResponseStream()));
                streamedMp3Sound.Play();
                playing = true;
            }
            else
            {
                buttonOtherPlayStop.Content = "Play";
                textBoxOtherUri.IsReadOnly = false;
                streamedMp3Sound.Stop();
                playing = false;
            }
        }
    }
}