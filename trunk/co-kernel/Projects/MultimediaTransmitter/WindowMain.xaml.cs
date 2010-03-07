using System;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

using Multimedia;
using CloudObserver.Formats;
using CloudObserver.Formats.Audio;
using CloudObserver.Formats.Audio.Mp3;
using CloudObserver.Capture.DirectSound;

namespace MultimediaTransmitter
{
    public partial class WindowMain : Window
    {
        private bool transmitting = false;
        private int connections = 0;
        private Transmitter transmitter;

        private bool Transmitting
        {
            get { return transmitting; }
            set
            {
                transmitting = value;
                comboBoxCaptureDevice.IsEnabled = !value;
                comboBoxAudioFormat.IsEnabled = !value;
                comboBoxBitRate.IsEnabled = !value;
                buttonStartStopTransmission.Content = value ? "Stop Transmission" : "Start Transmission";
                if (value)
                {
                    PcmAudioFormat pcmAudioFormat = (PcmAudioFormat)comboBoxAudioFormat.SelectedItem;
                    Mp3BitRate mp3BitRate = (Mp3BitRate)comboBoxBitRate.SelectedItem;
                    DirectSoundCaptureDevice directSoundCaptureDevice = (DirectSoundCaptureDevice)comboBoxCaptureDevice.SelectedItem;
                    transmitter = new Transmitter();
                    transmitter.ConnectionsUpdated += new ConnectionsUpdatedEventHandler(transmitter_ConnectionsUpdated);
                    transmitter.Start(directSoundCaptureDevice, pcmAudioFormat, mp3BitRate);
                }
                else
                    transmitter.Stop();
            }
        }

        private void transmitter_ConnectionsUpdated(object sender, ConnectionsUpdatedEventArgs e)
        {
            connections = e.Connections;
            Dispatcher.Invoke(new ThreadStart(UpdateConnections));
        }

        public WindowMain()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            foreach (DirectSoundCaptureDevice soundCaptureDevice in DirectSoundCaptureDevice.AllAvailable)
                comboBoxCaptureDevice.Items.Add(soundCaptureDevice);
            comboBoxCaptureDevice.SelectedIndex = 0;

            foreach (PcmAudioFormat format in Mp3AudioFormat.AllSourceFormats)
                comboBoxAudioFormat.Items.Add(format);
            comboBoxAudioFormat.SelectedItem = PcmAudioFormat.Pcm44kHz16bitStereo;
            comboBoxBitRate.SelectedItem = Mp3BitRate.BitRate192;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (Transmitting)
                Transmitting = false;
        }

        private void comboBoxAudioFormat_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (comboBoxAudioFormat.SelectedItem != null)
                LoadAvailableBitRates();
        }

        private void buttonStartStopTransmission_Click(object sender, RoutedEventArgs e)
        {
            Transmitting = !Transmitting;
        }

        private void LoadAvailableBitRates()
        {
            comboBoxBitRate.Items.Clear();
            PcmAudioFormat pcmAudioFormat = (PcmAudioFormat)comboBoxAudioFormat.SelectedItem;
            foreach (Mp3BitRate mp3BitRate in pcmAudioFormat.GetCompatibleMp3BitRates())
                comboBoxBitRate.Items.Add(mp3BitRate);
            comboBoxBitRate.SelectedIndex = 0;
        }

        private void UpdateConnections()
        {
            textBlockConnections.Text = "Connections: " + connections.ToString();
        }
    }
}