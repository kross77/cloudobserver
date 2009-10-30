using System;
using System.ServiceModel;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

using CloudObserver.Formats.Audio;
using CloudObserver.Formats.Audio.Mp3;
using CloudObserver.Formats.Audio.Mp3.LameEncoder;
using CloudObserver.Capture.DirectSound;
using CloudObserver.Services;
using CloudObserver.Services.Bindings;

namespace SoundStreaming.DirectSoundSender
{
    public partial class WindowMain : Window
    {
        #region Fields
        private bool capturing = false;
        private DirectSoundCapture directSoundCapture;
        private StreamingServiceClient streamingServiceClient;
        private Random random = new Random();
        private byte noiseLevel = 0;

        private uint m_hLameStream = 0;
        private uint m_InputSamples = 0;
        private uint m_OutBufferSize = 0;
        private byte[] m_OutBuffer = null;
        private bool mp3Compression = false;
        #endregion

        #region Properties
        public bool Capturing
        {
            get { return capturing; }
            set
            {
                capturing = value;
                textBoxStreamingServiceUri.IsEnabled = !value;
                comboBoxDirectSoundCaptureDevice.IsEnabled = !value;
                comboBoxAudioFormat.IsEnabled = !value;
                comboBoxSampling.IsEnabled = !value;
                comboBoxBitRate.IsEnabled = !value;
                if (capturing)
                {
                    buttonStartStopCapture.Content = "Stop Capture";

                    streamingServiceClient = new StreamingServiceClient(new ClientHttpBinding(), new EndpointAddress(textBoxStreamingServiceUri.Text));

                    PcmAudioFormat pcmAudioFormat = (PcmAudioFormat)comboBoxSampling.SelectedItem;
                    if (comboBoxAudioFormat.SelectedItem.ToString().Equals("MP3"))
                    {
                        Mp3BitRate mp3BitRate = (Mp3BitRate)comboBoxBitRate.SelectedItem;
                        Lame_encDll.beInitStream(new BE_CONFIG(new WaveFormat(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels),
                            mp3BitRate, LAME_QUALITY_PRESET.LQP_NORMAL_QUALITY), ref m_InputSamples, ref m_OutBufferSize, ref m_hLameStream);
                        m_OutBuffer = new byte[m_OutBufferSize];
                        mp3Compression = true;
                    }
                    else mp3Compression = false;

                    DirectSoundCaptureDevice directSoundCaptureDevice = (DirectSoundCaptureDevice)comboBoxDirectSoundCaptureDevice.SelectedItem;
                    directSoundCapture = new DirectSoundCapture(pcmAudioFormat, directSoundCaptureDevice);
                    directSoundCapture.ChunkCaptured += new EventHandler<CloudObserver.Capture.ChunkCapturedEventArgs>(ChunkCaptured);
                    directSoundCapture.Start();
                }
                else
                {
                    buttonStartStopCapture.Content = "Start Capture";
                    if (directSoundCapture != null) directSoundCapture.Stop();
                }
            }
        }
        #endregion Properties

        #region Constructors
        public WindowMain()
        {
            InitializeComponent();
        }
        #endregion

        #region Private Methods
        private void LoadAvailableFormats(IEnumerable<PcmAudioFormat> formats)
        {
            comboBoxSampling.Items.Clear();
            foreach (PcmAudioFormat format in formats)
                comboBoxSampling.Items.Add(format);
            comboBoxSampling.SelectedIndex = 0;
        }

        private void LoadAvailableBitRates()
        {
            comboBoxBitRate.Items.Clear();
            PcmAudioFormat pcmAudioFormat = (PcmAudioFormat)comboBoxSampling.SelectedItem;
            switch (comboBoxAudioFormat.SelectedItem.ToString())
            {
                case "PCM":
                    comboBoxBitRate.Items.Add(string.Format("{0} kbit/sec", pcmAudioFormat.SamplesPerSecond * pcmAudioFormat.BitsPerSample * pcmAudioFormat.Channels / 1024));
                    comboBoxBitRate.SelectedIndex = 0;
                    break;
                case "MP3":
                    foreach (Mp3BitRate mp3BitRate in pcmAudioFormat.GetCompatibleMp3BitRates())
                        comboBoxBitRate.Items.Add(mp3BitRate);
                    break;
            }
            if (comboBoxBitRate.Items.Count > 0)
                comboBoxBitRate.SelectedIndex = 0;
        }
        #endregion

        #region Event Handlers
        void ChunkCaptured(object sender, CloudObserver.Capture.ChunkCapturedEventArgs e)
        {
            if (noiseLevel > 0)
                for (int i = 0; i < e.ChunkData.Length; i++)
                    e.ChunkData[i] += (byte)random.Next(0, noiseLevel);
            if (mp3Compression)
            {
                uint EncodedSize = 0;
                if (Lame_encDll.EncodeChunk(m_hLameStream, e.ChunkData, m_OutBuffer, ref EncodedSize) == Lame_encDll.BE_ERR_SUCCESSFUL)
                    if (EncodedSize > 0)
                    {
                        byte[] data = new byte[EncodedSize];
                        Array.Copy(m_OutBuffer, data, EncodedSize);
                        streamingServiceClient.Write(data);
                    }
            }
            else
                streamingServiceClient.Write(e.ChunkData);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            foreach (DirectSoundCaptureDevice soundCaptureDevice in DirectSoundCaptureDevice.AllAvailable)
                comboBoxDirectSoundCaptureDevice.Items.Add(soundCaptureDevice);
            comboBoxDirectSoundCaptureDevice.SelectedIndex = 0;

            comboBoxAudioFormat.Items.Add(AudioFormatBase.GetSourceFormatClassName(typeof(PcmAudioFormat)));
            comboBoxAudioFormat.Items.Add(AudioFormatBase.GetSourceFormatClassName(typeof(Mp3AudioFormat)));
            comboBoxAudioFormat.SelectedIndex = 0;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (Capturing) Capturing = false;
        }

        private void comboBoxAudioFormat_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            switch (comboBoxAudioFormat.SelectedItem.ToString())
            {
                case "PCM":
                    LoadAvailableFormats(PcmAudioFormat.StandardFormats);
                    comboBoxSampling.SelectedItem = PcmAudioFormat.Pcm44kHz16bitStereo;
                    break;
                case "MP3":
                    LoadAvailableFormats(Mp3AudioFormat.AllSourceFormats);
                    comboBoxSampling.SelectedItem = PcmAudioFormat.Pcm44kHz16bitStereo;
                    comboBoxBitRate.SelectedItem = Mp3BitRate.BitRate192;
                    break;
            }
        }

        private void comboBoxSampling_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (comboBoxSampling.SelectedItem != null)
                LoadAvailableBitRates();
        }

        private void sliderNoiseLevel_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            noiseLevel = (byte)sliderNoiseLevel.Value;
        }

        private void buttonStartStopCapture_Click(object sender, RoutedEventArgs e)
        {
            Capturing = !Capturing;
        }
        #endregion
    }
}