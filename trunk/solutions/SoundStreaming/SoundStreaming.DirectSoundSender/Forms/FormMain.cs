using System;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.Windows.Forms;
using Microsoft.DirectX.DirectSound;

using CloudObserver.Services.StreamingService;

namespace SoundStreaming.DirectSoundSender
{
    public partial class FormMain : Form
    {
        #region Fields

        private bool capturing;
        private bool addNoise;
        private string serviceUri;

        private int bufferSize;
        private Thread capturingThread;
        private CaptureBuffer captureBuffer;
        private AutoResetEvent notificationEvent;
        private Random random = new Random();
        private StreamingServiceClient streamingServiceClient;

        #endregion

        #region Constants

        private const short channels = 1;
        private const short bitsPerSample = 16;
        private const int samplesPerSecond = 44100;
        private const int bytesPerSecond = samplesPerSecond * channels * bitsPerSample / 8;
        private const int blockSize = bytesPerSecond / 5;
        private const int bufferPositions = 2;

        private const int maxReceivedMessageSize = 2147483647;
        private const int maxArrayLength = 2147483647;

        #endregion

        #region Properties

        public bool Capturing
        {
            get { return capturing; }
            set
            {
                capturing = value;
                if (value)
                {
                    textBoxServiceUri.ReadOnly = true;
                    buttonStartStopCapture.Text = "Stop Capture";
                    InitializeStreamingServiceProxy();
                    capturingThread = new Thread(new ThreadStart(CaptureProcess));
                    capturingThread.IsBackground = true;
                    capturingThread.Start();
                }
                else
                {
                    textBoxServiceUri.ReadOnly = false;
                    buttonStartStopCapture.Text = "Start Capture";
                    ReleaseStreamingServiceProxy();
                }
            }
        }

        public bool AddNoise
        {
            get { return addNoise; }
            set
            {
                addNoise = value;
                checkBoxAddNoise.Checked = value;
            }
        }

        public string ServiceUri
        {
            get { return serviceUri; }
            set
            {
                serviceUri = value;
                textBoxServiceUri.Text = value;
            }
        }

        #endregion

        #region Constructors

        public FormMain()
        {
            InitializeComponent();

            Capturing = false;
            ServiceUri = "http://127.0.0.1:9000/StreamingService";
            InitializeCapture();
        }

        #endregion

        #region Private Methods

        private void InitializeCapture()
        {
            CheckForIllegalCrossThreadCalls = false;

            WaveFormat waveFormat = new WaveFormat();
            waveFormat.FormatTag = WaveFormatTag.Pcm;
            waveFormat.Channels = channels;
            waveFormat.BitsPerSample = bitsPerSample;
            waveFormat.SamplesPerSecond = samplesPerSecond;
            waveFormat.BlockAlign = (short)(channels * (bitsPerSample / 8));
            waveFormat.AverageBytesPerSecond = bytesPerSecond;
            bufferSize = blockSize;

            Capture captureDevice = new Capture();
            CaptureBufferDescription captureBufferDescription = new CaptureBufferDescription();
            captureBufferDescription.BufferBytes = bufferPositions * bufferSize;
            captureBufferDescription.Format = waveFormat;
            captureBuffer = new CaptureBuffer(captureBufferDescription, captureDevice);

            notificationEvent = new AutoResetEvent(false);
            BufferPositionNotify[] bufferPositionNotifies = new BufferPositionNotify[bufferPositions];
            for (int i = 0; i < bufferPositions; i++)
            {
                bufferPositionNotifies[i].Offset = bufferSize * (i + 1) - 1;
                bufferPositionNotifies[i].EventNotifyHandle = notificationEvent.SafeWaitHandle.DangerousGetHandle();
            }
            Notify notify = new Notify(captureBuffer);
            notify.SetNotificationPositions(bufferPositionNotifies, bufferPositions);
        }

        private void InitializeStreamingServiceProxy()
        {
            BasicHttpBinding binding = new BasicHttpBinding();
            binding.BypassProxyOnLocal = true;
            binding.MaxReceivedMessageSize = maxReceivedMessageSize;
            binding.OpenTimeout = TimeSpan.FromMinutes(5);
            binding.CloseTimeout = TimeSpan.FromMinutes(5);
            binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
            binding.SendTimeout = TimeSpan.FromMinutes(30);
            binding.ReaderQuotas.MaxArrayLength = maxArrayLength;
            binding.TransferMode = TransferMode.Streamed;

            streamingServiceClient = new StreamingServiceClient(binding, new EndpointAddress(ServiceUri));
        }

        private void ReleaseStreamingServiceProxy()
        {
            if (streamingServiceClient != null) streamingServiceClient.Close();
            streamingServiceClient = null;
        }

        private void CaptureProcess()
        {
            try
            {
                captureBuffer.Start(true);

                int offset = 0;
                while (Capturing)
                {
                    notificationEvent.WaitOne(Timeout.Infinite, true);

                    byte[] buffer = (byte[])captureBuffer.Read(offset, typeof(byte), LockFlag.None, bufferSize);
                    if (AddNoise)
                        for (int i = 0; i < bufferSize; i++)
                            buffer[i] += (byte)random.Next(byte.MinValue, byte.MaxValue);
                    streamingServiceClient.Write(new MemoryStream(buffer));

                    offset = (offset + bufferSize) % (bufferPositions * bufferSize);
                }
            }
            catch (Exception)
            {
                Capturing = false;
            }
        }

        #endregion

        #region Event Handlers

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            Capturing = false;
        }

        private void textBoxServiceUri_TextChanged(object sender, EventArgs e)
        {
            ServiceUri = textBoxServiceUri.Text;
        }

        private void buttonStartStopCapture_Click(object sender, EventArgs e)
        {
            Capturing = !Capturing;
        }

        private void checkBoxAddNoise_CheckedChanged(object sender, EventArgs e)
        {
            AddNoise = checkBoxAddNoise.Checked;
        }

        #endregion
    }
}