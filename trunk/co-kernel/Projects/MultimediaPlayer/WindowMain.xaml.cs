using System;
using System.IO;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;

using CloudObserver.Multimedia;
using Microsoft.DirectX.DirectSound;

namespace MultimediaPlayer
{
    public partial class WindowMain : Window
    {
        private Device device;
        private Player player;
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
                    player.Stop();
                buttonEldoradioPlayStop.Content = "Stop";
                buttonLoveRadioPlayStop.Content = "Play";
                buttonKCDXPlayStop.Content = "Play";
                buttonOtherPlayStop.Content = "Play";
                player = new Player(textBoxEldoradioUri.Text, device);
                player.Play();
                playing = true;
            }
            else
            {
                buttonEldoradioPlayStop.Content = "Play";
                player.Stop();
                playing = false;
            }
        }

        private void buttonLoveRadioPlayStop_Click(object sender, RoutedEventArgs e)
        {
            if (buttonLoveRadioPlayStop.Content.ToString() == "Play")
            {
                if (playing)
                    player.Stop();
                buttonEldoradioPlayStop.Content = "Play";
                buttonLoveRadioPlayStop.Content = "Stop";
                buttonKCDXPlayStop.Content = "Play";
                buttonOtherPlayStop.Content = "Play";
                player = new Player(textBoxLoveRadioUri.Text, device);
                player.Play();
                playing = true;
            }
            else
            {
                buttonLoveRadioPlayStop.Content = "Play";
                player.Stop();
                playing = false;
            }
        }

        private void buttonKCDXPlayStop_Click(object sender, RoutedEventArgs e)
        {
            if (buttonKCDXPlayStop.Content.ToString() == "Play")
            {
                if (playing)
                    player.Stop();
                buttonEldoradioPlayStop.Content = "Play";
                buttonLoveRadioPlayStop.Content = "Play";
                buttonKCDXPlayStop.Content = "Stop";
                buttonOtherPlayStop.Content = "Play";
                player = new Player(textBoxKCDXUri.Text, device);
                player.Play();
                playing = true;
            }
            else
            {
                buttonKCDXPlayStop.Content = "Play";
                player.Stop();
                playing = false;
            }
        }

        private void buttonOtherPlayStop_Click(object sender, RoutedEventArgs e)
        {
            if (buttonOtherPlayStop.Content.ToString() == "Play")
            {
                if (playing)
                    player.Stop();
                buttonEldoradioPlayStop.Content = "Play";
                buttonLoveRadioPlayStop.Content = "Play";
                buttonKCDXPlayStop.Content = "Play";
                buttonOtherPlayStop.Content = "Stop";
                textBoxOtherUri.IsReadOnly = true;
                player = new Player(textBoxOtherUri.Text, device);
                player.Play();
                playing = true;
            }
            else
            {
                buttonOtherPlayStop.Content = "Play";
                textBoxOtherUri.IsReadOnly = false;
                player.Stop();
                playing = false;
            }
        }
    }
}