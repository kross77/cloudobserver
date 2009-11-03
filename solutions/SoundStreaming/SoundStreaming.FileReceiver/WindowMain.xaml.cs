using System;
using System.IO;
using System.Windows;
using System.ServiceModel;
using Microsoft.Win32;

using CloudObserver.Services;

namespace SoundStreaming.FileReceiver
{
    public partial class WindowMain : Window
    {
        #region Fields
        private bool connected = false;
        private bool receiving = false;
        private Int64 dataReceived = 0;
        BinaryWriter binaryWriter;
        private StreamingServiceClient streamingServiceClient;
        private StreamingServiceCallback streamingServiceCallback;
        #endregion Fields

        #region Constants
        private byte[] riffChunk = { 82, 73, 70, 70 }; // 'RIFF'
        private byte[] waveChunk = { 87, 65, 86, 69 }; // 'WAVE'
        private byte[] fmtChunk = { 102, 109, 116, 32 }; // 'fmt '
        private byte[] dataChunk = { 100, 97, 116, 97 }; // 'data'
        #endregion Constants

        #region Properties
        public bool Connected
        {
            get { return connected; }
            set
            {
                connected = value;
                textBoxStreamingServiceUri.IsEnabled = !value;
                buttonConnectDisconnect.Content = value ? "Disconnect" : "Connect";
                textBoxSaveTo.IsEnabled = value;
                buttonSelectFile.IsEnabled = value;
                buttonStartStop.IsEnabled = value;
                if (value)
                {
                    streamingServiceCallback = new StreamingServiceCallback();
                    streamingServiceCallback.DataCallbackReceived += new EventHandler<DataCallbackReceivedEventArgs>(DataCallbackReceivedHandler);
                    streamingServiceCallback.SubscriptionResponseReceived += new EventHandler<SubscriptionResponseReceivedEventArgs>(SubscriptionResponseReceivedHandler);
                    streamingServiceClient = new StreamingServiceClient(new InstanceContext(streamingServiceCallback),
                        new InternalNetTcpBinding(), new EndpointAddress(textBoxStreamingServiceUri.Text));
                }
                else
                {
                    if (Receiving) Receiving = false;
                    ResetDianostics();
                    streamingServiceClient.Close();
                    streamingServiceClient = null;
                }
            }
        }

        public bool Receiving
        {
            get { return receiving; }
            set
            {
                receiving = value;
                textBoxSaveTo.IsReadOnly = value;
                buttonSelectFile.IsEnabled = !value;
                buttonStartStop.Content = value ? "Stop" : "Start";
                if (value)
                {
                    ResetDianostics();
                    binaryWriter = new BinaryWriter(File.Create(textBoxSaveTo.Text));
                    streamingServiceClient.Subscribe(TimeSpan.FromMinutes(10));
                }
                else
                {
                    streamingServiceClient.Unsubscribe();
                    binaryWriter.Seek(4, SeekOrigin.Begin); // Seek to the length descriptor of the RIFF file.
                    binaryWriter.Write((int)(dataReceived + 36)); // Write the file length, minus first 8 bytes of RIFF description.
                    binaryWriter.Seek(40, SeekOrigin.Begin); // Seek to the data length descriptor of the RIFF file.
                    binaryWriter.Write(dataReceived); // Write the length of the sample data in bytes.
                    binaryWriter.Close();
                    binaryWriter = null;
                }
            }
        }
        #endregion Properties

        #region Constructors
        public WindowMain()
        {
            InitializeComponent();
        }
        #endregion Constructors

        #region Private Methods
        private void ResetDianostics()
        {
            dataReceived = 0;
            textBlockDataReceived.Text = "Data received: 0 KB (0 B)";
        }
        #endregion Private Methods

        #region Event Handlers
        private void DataCallbackReceivedHandler(object sender, DataCallbackReceivedEventArgs e)
        {
            binaryWriter.Write(e.Data);
            dataReceived += e.Data.Length;
            double value = dataReceived;
            value /= 1024;
            string suffix = "KB";
            if (value > 999)
            {
                value /= 1024;
                suffix = "MB";
            }
            if (value > 999)
            {
                value /= 1024;
                suffix = "GB";
            }
            textBlockDataReceived.Text = "Data received: " + value.ToString("0.00") + " " + suffix + " (" + dataReceived.ToString("0,0") + " B)";
        }

        void SubscriptionResponseReceivedHandler(object sender, SubscriptionResponseReceivedEventArgs e)
        {
            if (e.Response != null)
                if (dataReceived == 0)
                {
                    // Fill in the riff info for the wave file.
                    binaryWriter.Write(riffChunk);
                    binaryWriter.Write((int)0); // File length, minus first 8 bytes of RIFF description. This will be filled in later.
                    binaryWriter.Write(waveChunk);

                    byte[] waveFormatBytes = new byte[e.Response.Length - 4];
                    Array.Copy(e.Response, 4, waveFormatBytes, 0, e.Response.Length - 4);

                    // Fill in the format info for the wave file.
                    binaryWriter.Write(fmtChunk);
                    binaryWriter.Write((int)16);
                    binaryWriter.Write(waveFormatBytes);

                    // Now fill in the data chunk.
                    binaryWriter.Write(dataChunk);
                    binaryWriter.Write((int)0); // The sample length will be written in later.
                }
                else
                    Receiving = false;
        }

        private void buttonConnectDisconnect_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            Connected = !Connected;
        }

        private void buttonSelectFile_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "All Files (*.*)|*.*";
            bool? result = saveFileDialog.ShowDialog();
            if (result == true)
                textBoxSaveTo.Text = saveFileDialog.FileName;
        }

        private void buttonStartStop_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            Receiving = !Receiving;
        }
        #endregion EventHandlers
    }
}