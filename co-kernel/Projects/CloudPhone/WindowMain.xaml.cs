using System;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;

using Multimedia;
using CloudObserver.Formats;
using CloudObserver.Formats.Audio;
using CloudObserver.Formats.Audio.Mp3;
using CloudObserver.Capture.DirectSound;

using Mp3Sharp;
using Microsoft.DirectX.DirectSound;

namespace CloudObserver.CloudPhone
{
    public partial class WindowMain : Window
    {
        private const int port = 4773;
        private const string responseHeader = "HTTP/1.0 200 OK\r\nContent-Type: audio/mpeg\r\n\r\n";

        private bool listening = false;
        private int connections = 0;
        private Thread listenerThread = null;
        private TcpListener listener = null;
        private List<NetworkStream> clients = null;
        private DirectSoundCapture directSoundCapture = null;
        private Device device;

        private uint m_hLameStream = 0;
        private uint m_InputSamples = 0;
        private uint m_OutBufferSize = 0;
        private byte[] m_OutBuffer = null;

        private bool Listening
        {
            get { return listening; }
            set
            {
                listening = value;
                comboBoxCaptureDevice.IsEnabled = !value;
                comboBoxAudioFormat.IsEnabled = !value;
                comboBoxBitRate.IsEnabled = !value;
                buttonStartStopListening.Content = value ? "Stop Listening" : "Start Listening";
                if (value)
                {
                    PcmAudioFormat pcmAudioFormat = (PcmAudioFormat)comboBoxAudioFormat.SelectedItem;
                    WaveFormatEx waveFormat = new WaveFormatEx(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels);
                    Mp3BitRate mp3BitRate = (Mp3BitRate)comboBoxBitRate.SelectedItem;
                    Lame_encDll.beInitStream(new BE_CONFIG(new CloudObserver.Formats.Audio.WaveFormat(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels),
                        mp3BitRate, LAME_QUALITY_PRESET.LQP_NORMAL_QUALITY), ref m_InputSamples, ref m_OutBufferSize, ref m_hLameStream);
                    m_OutBuffer = new byte[m_OutBufferSize];

                    DirectSoundCaptureDevice directSoundCaptureDevice = (DirectSoundCaptureDevice)comboBoxCaptureDevice.SelectedItem;
                    directSoundCapture = new DirectSoundCapture(pcmAudioFormat, directSoundCaptureDevice);
                    directSoundCapture.ChunkCaptured += new EventHandler<CloudObserver.Capture.ChunkCapturedEventArgs>(ChunkCaptured);
                    directSoundCapture.Start();

                    listener.Start();
                    listenerThread.Start();
                }
                else
                    if (directSoundCapture != null)
                    {
                        directSoundCapture.Stop();
                        directSoundCapture = null;
                        foreach (NetworkStream client in clients)
                            client.Close();
                        clients.Clear();
                        listener.Stop();
                        listenerThread = new Thread(new ThreadStart(ListenerLoop));
                    }
            }
        }

        private int Connections
        {
            get { return connections; }
            set
            {
                connections = value;
                Dispatcher.Invoke(new ThreadStart(UpdateConnections));
            }
        }

        public WindowMain()
        {
            InitializeComponent();

            listener = new TcpListener(IPAddress.Any, port);
            clients = new List<NetworkStream>();
            listenerThread = new Thread(new ThreadStart(ListenerLoop));
            listenerThread.IsBackground = true;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            device = new Device();
            device.SetCooperativeLevel(new WindowInteropHelper(this).Handle, CooperativeLevel.Priority);

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
            if (Listening)
                Listening = false;
        }

        private void comboBoxAudioFormat_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (comboBoxAudioFormat.SelectedItem != null)
                LoadAvailableBitRates();
        }

        private void buttonStartStopListening_Click(object sender, RoutedEventArgs e)
        {
            Listening = !Listening;
        }

        private void LoadAvailableBitRates()
        {
            comboBoxBitRate.Items.Clear();
            PcmAudioFormat pcmAudioFormat = (PcmAudioFormat)comboBoxAudioFormat.SelectedItem;
            foreach (Mp3BitRate mp3BitRate in pcmAudioFormat.GetCompatibleMp3BitRates())
                comboBoxBitRate.Items.Add(mp3BitRate);
            comboBoxBitRate.SelectedIndex = 0;
        }

        private void ChunkCaptured(object sender, CloudObserver.Capture.ChunkCapturedEventArgs e)
        {
            uint EncodedSize = 0;
            if (Lame_encDll.EncodeChunk(m_hLameStream, e.ChunkData, m_OutBuffer, ref EncodedSize) == Lame_encDll.BE_ERR_SUCCESSFUL)
                if (EncodedSize > 0)
                {
                    List<NetworkStream> deadClients = new List<NetworkStream>();
                    foreach (NetworkStream client in clients)
                        try
                        {
                            client.Write(m_OutBuffer, 0, (int)EncodedSize);
                        }
                        catch (Exception)
                        {
                            deadClients.Add(client);
                            Connections--;
                        }
                    foreach (NetworkStream deadClient in deadClients)
                        clients.Remove(deadClient);
                    deadClients.Clear();
                }
        }

        private void ListenerLoop()
        {
            while (Listening)
            {
                try
                {
                    NetworkStream client = listener.AcceptTcpClient().GetStream();
                    byte[] header = Encoding.UTF8.GetBytes(responseHeader);
                    client.Write(header, 0, header.Length);
                    clients.Add(client);
                    new StreamedMp3Sound(device, new Mp3Stream(client)).Play();
                    Connections++;
                }
                catch (Exception)
                {
                }
            }
        }

        private void UpdateConnections()
        {
            textBlockConnections.Text = "Connections: " + Connections.ToString();
        }
    }
}