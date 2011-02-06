using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.ServiceModel;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;

using CloudObserver.Clients.Auxiliaries.Capture;
using CloudObserver.Clients.Auxiliaries.Capture.DirectSound;
using CloudObserver.Clients.Auxiliaries.Formats;
using CloudObserver.Clients.Auxiliaries.Formats.Audio;
using CloudObserver.Clients.Auxiliaries.Formats.Audio.Mp3;
using CloudObserver.Clients.Auxiliaries.Services;

using Microsoft.DirectX.DirectSound;

namespace CloudObserver.Clients.Writer
{
    public partial class WindowMain : Window
    {
        private bool transmitting = false;
        private NetworkStream networkStream;
        private DirectSoundCapture directSoundCapture = null;
        private Device device;

        private uint m_hLameStream = 0;
        private uint m_InputSamples = 0;
        private uint m_OutBufferSize = 0;
        private byte[] m_OutBuffer = null;

        private bool Transmitting
        {
            get { return transmitting; }
            set
            {
                int contentId;
                if (!Int32.TryParse(textBoxContentId.Text, out contentId))
                {
                    MessageBox.Show("Invalid content id.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                string workBlockServiceAddress;
                using (ChannelFactory<ICloudController> channelFactory = new ChannelFactory<ICloudController>(new BasicHttpBinding(), textBoxGatewayAddress.Text))
                {
                    ICloudController gateway = channelFactory.CreateChannel();
                    try
                    {
                        workBlockServiceAddress = gateway.GetWorkBlock();
                    }
                    catch (Exception exception)
                    {
                        Console.Write("An error occured while communicating with the gateway service. Details: " + exception.Message);
                        return;
                    }
                    finally
                    {
                        try
                        {
                            ((IClientChannel)gateway).Close();
                        }
                        catch (Exception)
                        {
                            ((IClientChannel)gateway).Abort();
                        }
                    }
                }

                string tcpStreamAddress;
                using (ChannelFactory<IWorkBlock> channelFactory = new ChannelFactory<IWorkBlock>(new BasicHttpBinding(), workBlockServiceAddress))
                {
                    IWorkBlock workBlock = channelFactory.CreateChannel();
                    try
                    {
                        tcpStreamAddress = workBlock.IWannaWrite(contentId, "audio/mpeg");
                    }
                    catch (Exception exception)
                    {
                        Console.Write("An error occured while communicating with the work block service. Details: " + exception.Message);
                        return;
                    }
                    finally
                    {
                        try
                        {
                            ((IClientChannel)workBlock).Close();
                        }
                        catch (Exception)
                        {
                            ((IClientChannel)workBlock).Abort();
                        }
                    }
                }

                transmitting = value;
                comboBoxCaptureDevice.IsEnabled = !value;
                comboBoxAudioFormat.IsEnabled = !value;
                comboBoxBitRate.IsEnabled = !value;
                textBoxGatewayAddress.IsReadOnly = value;
                textBoxContentId.IsReadOnly = value;
                buttonStartStop.Content = value ? "Stop Transmission" : "Start Transmission";
                if (value)
                {
                    PcmAudioFormat pcmAudioFormat = (PcmAudioFormat)comboBoxAudioFormat.SelectedItem;
                    WaveFormatEx waveFormat = new WaveFormatEx(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels);
                    Mp3BitRate mp3BitRate = (Mp3BitRate)comboBoxBitRate.SelectedItem;
                    Lame_encDll.beInitStream(new BE_CONFIG(new CloudObserver.Clients.Auxiliaries.Formats.Audio.WaveFormat(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels),
                        mp3BitRate, LAME_QUALITY_PRESET.LQP_NORMAL_QUALITY), ref m_InputSamples, ref m_OutBufferSize, ref m_hLameStream);
                    m_OutBuffer = new byte[m_OutBufferSize];

                    Uri targetUri = new Uri(tcpStreamAddress);
                    TcpClient tcpClient = new TcpClient();
                    tcpClient.Connect(targetUri.Host, targetUri.Port);
                    networkStream = tcpClient.GetStream();

                    DirectSoundCaptureDevice directSoundCaptureDevice = (DirectSoundCaptureDevice)comboBoxCaptureDevice.SelectedItem;
                    directSoundCapture = new DirectSoundCapture(pcmAudioFormat, directSoundCaptureDevice);
                    directSoundCapture.ChunkCaptured += new EventHandler<ChunkCapturedEventArgs>(ChunkCaptured);
                    directSoundCapture.Start();
                }
                else
                    if (directSoundCapture != null)
                    {
                        directSoundCapture.Stop();
                        directSoundCapture = null;
                        networkStream.Close();
                    }
            }
        }

        public WindowMain()
        {
            InitializeComponent();
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
            if (Transmitting)
                Transmitting = false;
        }

        private void comboBoxAudioFormat_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (comboBoxAudioFormat.SelectedItem != null)
                LoadAvailableBitRates();
        }

        private void buttonStartStop_Click(object sender, RoutedEventArgs e)
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

        private void ChunkCaptured(object sender, ChunkCapturedEventArgs e)
        {
            uint EncodedSize = 0;
            if (Lame_encDll.EncodeChunk(m_hLameStream, e.ChunkData, m_OutBuffer, ref EncodedSize) == Lame_encDll.BE_ERR_SUCCESSFUL)
                if (EncodedSize > 0)
                {
                    try
                    {
                            networkStream.Write(m_OutBuffer, 0, (int)EncodedSize);
                    }
                    catch (Exception)
                    {
                    }
                }
        }
    }
}
