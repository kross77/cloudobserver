using System;
using System.IO;
using System.Text;
using System.Windows;
using System.Threading;
using System.ServiceModel;
using Microsoft.Win32;

using CloudObserver.Services;
using CloudObserver.Formats;
using CloudObserver.Formats.Audio;

namespace SoundStreaming.FileSender
{
    public partial class WindowMain : Window
    {
        #region Fields
        private bool connected = false;
        private bool sending = false;
        private long dataSent = 0;
        private Thread sendingThread;
        private FileStream fileStream;
        private string fileLengthString;
        private StreamingServiceClient streamingServiceClient;

        private bool truncateWaveRiffHeader;
        private bool truncateMp3Id3Tags;
        #endregion Fields

        #region Constants
        private const int maxChunkSize = 32768;

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
                buttonSendFile.IsEnabled = value;
                if (connected)
                {
                    streamingServiceClient = new StreamingServiceClient(new InstanceContext(new StreamingServiceCallback()),
                        new InternalNetTcpBinding(), new EndpointAddress(textBoxStreamingServiceUri.Text));
                }
                else
                {
                    if (Sending) Sending = false;
                    ResetDianostics();
                    streamingServiceClient.Close();
                    streamingServiceClient = null;
                }
            }
        }

        public bool Sending
        {
            get { return sending; }
            set
            {
                sending = value;
                buttonSendFile.Content = value ? "Abort" : "Send File";
                if (value)
                {
                    ResetDianostics();
                    sendingThread = new Thread(new ThreadStart(SendFile));
                    sendingThread.IsBackground = true;
                    sendingThread.Start();
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
            dataSent = 0;
            textBlockDataSent.Text = "Data sent: 0 KB (0 B) of 0 KB (0 B).";
        }

        private void UpdateDiagnostics()
        {
            double value = dataSent;
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
            textBlockDataSent.Text = "Data sent: " + value.ToString("0.00") + " " + suffix + " (" + dataSent.ToString("0,0") + " B) of " + fileLengthString + ".";
        }

        private void SetFileLength(long fileLength)
        {
            double value = fileLength;
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
            fileLengthString = value.ToString("0.00") + " " + suffix + " (" + fileLength.ToString("0,0") + " B)";
        }

        private void SendCompleted()
        {
            Sending = false;
        }

        private void SendFile()
        {
            int read = 0;
            byte[] byteArray = new byte[maxChunkSize];
            while (Sending)
            {
                //if (truncateMp3Id3Tags)
                //{
                //    int patternOffset = 0;
                //    do
                //    {
                //        read = fileStream.Read(byteArray, 0, maxChunkSize);
                //        patternOffset = BitTools.FindBitPattern(byteArray, new byte[2] { 255, 240 }, new byte[2] { 255, 240 });
                //    }
                //    while ((read > 0) && (patternOffset < 0));
                //    if (read <= 0) Dispatcher.Invoke(new ThreadStart(SendCompleted));
                //    byte[] newByteArray = new byte[maxChunkSize];
                //    Array.Copy(byteArray, patternOffset, newByteArray, 0, byteArray.Length - patternOffset);
                //    byteArray = newByteArray;
                //    read = byteArray.Length - patternOffset;
                //    truncateMp3Id3Tags = false;
                //}
                //else
                read = fileStream.Read(byteArray, 0, maxChunkSize);
                if (truncateWaveRiffHeader)
                {
                    int riffChunkPos = BitTools.FindBytePattern(byteArray, riffChunk);
                    int waveChunkPos = BitTools.FindBytePattern(byteArray, waveChunk);
                    int fmtChunkPos = BitTools.FindBytePattern(byteArray, fmtChunk);
                    int dataChunkPos = BitTools.FindBytePattern(byteArray, dataChunk);
                    byte[] waveFormatEx = new byte[dataChunkPos - fmtChunkPos - 8];
                    Array.Copy(byteArray, fmtChunkPos + 8, waveFormatEx, 0, dataChunkPos - fmtChunkPos - 8);
                    byte[] response = new byte[4 + waveFormatEx.Length];
                    Array.Copy(Encoding.UTF8.GetBytes(FormatIdentifiers.FormatPcm), response, 4);
                    Array.Copy(waveFormatEx, 0, response, 4, waveFormatEx.Length);
                    streamingServiceClient.SetSubscriptionResponse(response);
                    byte[] newByteArray = new byte[maxChunkSize];
                    Array.Copy(byteArray, dataChunkPos + 8, newByteArray, 0, read - dataChunkPos - 8);
                    byteArray = newByteArray;
                    read -= dataChunkPos + 8;
                    truncateWaveRiffHeader = false;
                }

                if (read <= 0) Dispatcher.Invoke(new ThreadStart(SendCompleted));
                
                if (read == maxChunkSize)
                    streamingServiceClient.Send(byteArray);
                else
                {
                    byte[] buffer = new byte[read];
                    Array.Copy(byteArray, buffer, read);
                    streamingServiceClient.Send(buffer);
                }
                dataSent += read;
                Dispatcher.Invoke(new ThreadStart(UpdateDiagnostics));
            }
        }
        #endregion Private Methods

        #region Event Handlers
        private void buttonConnectDisconnect_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            Connected = !Connected;
        }

        private void buttonSendFile_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (Sending)
            {
                Sending = false;
                return;
            }
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Wave Files (*.wav; *.wave)|*.wav;*.wave|MP3 Files (*.mp3)|*.mp3|All Files (*.*)|*.*";
            bool? result = openFileDialog.ShowDialog();
            if (result == true)
            {
                fileStream = File.OpenRead(openFileDialog.FileName);
                SetFileLength(fileStream.Length);
                if (checkBoxDetectAudioFormat.IsChecked.Value)
                {
                    int extPosition = openFileDialog.SafeFileName.LastIndexOf('.');
                    switch (openFileDialog.SafeFileName.Substring(extPosition + 1).ToLower())
                    {
                        case "wav":
                        case "wave":
                            truncateWaveRiffHeader = checkBoxTruncateWaveRiffHeader.IsChecked.Value;
                            truncateMp3Id3Tags = false;
                            break;
                        case "mp3":
                            truncateWaveRiffHeader = false;
                            truncateMp3Id3Tags = checkBoxTruncateMp3Id3Tags.IsChecked.Value;
                            streamingServiceClient.SetSubscriptionResponse(Encoding.UTF8.GetBytes(FormatIdentifiers.FormatMp3));
                            break;
                        default:
                            streamingServiceClient.SetSubscriptionResponse(Encoding.UTF8.GetBytes(FormatIdentifiers.FormatNone));
                            break;
                    }
                }
                Sending = true;
            }
        }
        #endregion Event Handlers
    }
}