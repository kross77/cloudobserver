using System;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.Windows.Forms;
using Microsoft.DirectX.DirectSound;
using CloudObserver.Services;

namespace CloudObserver.Client
{
    public partial class FormMain : Form
    {
        private const short CHANNELS = 1;
        private const short BITS_PER_SAMPLE = 16;
        private const int SAMPLES_PER_SECOND = 44100;
        private const int BUFFER_POSITIONS = 2;

        private const int MAX_RECEIVED_MESSAGE_SIZE = 2147483647;
        private const int MAX_ARRAY_LENGTH = 2147483647;

        private bool capturing = false;
        private bool playing = false;
        private Thread capturingThread;
        private Thread playingThread;
        private int bufferSize;
        private CaptureBuffer captureBuffer;
        private AutoResetEvent notificationEvent;
        private SecondaryBuffer playbackBuffer;

        private Random random = new Random();

        private ControllerServiceContract controllerServiceClient;
        private TestSoundServiceContract testSoundServiceClient;

        public FormMain()
        {
            InitializeComponent();

            Initialize();
        }

        private void Initialize()
        {
            CheckForIllegalCrossThreadCalls = false;

            WaveFormat waveFormat = new WaveFormat();
            waveFormat.FormatTag = WaveFormatTag.Pcm;
            waveFormat.Channels = CHANNELS;
            waveFormat.BitsPerSample = BITS_PER_SAMPLE;
            waveFormat.SamplesPerSecond = SAMPLES_PER_SECOND;
            waveFormat.BlockAlign = (short)(CHANNELS * (BITS_PER_SAMPLE / 8));
            waveFormat.AverageBytesPerSecond = waveFormat.BlockAlign * SAMPLES_PER_SECOND;
            bufferSize = waveFormat.AverageBytesPerSecond;

            Capture captureDevice = new Capture();
            CaptureBufferDescription captureBufferDescription = new CaptureBufferDescription();
            captureBufferDescription.BufferBytes = BUFFER_POSITIONS * bufferSize;
            captureBufferDescription.Format = waveFormat;
            captureBuffer = new CaptureBuffer(captureBufferDescription, captureDevice);

            notificationEvent = new AutoResetEvent(false);
            BufferPositionNotify[] bufferPositionNotifies = new BufferPositionNotify[BUFFER_POSITIONS];
            for (int i = 0; i < BUFFER_POSITIONS; i++)
            {
                bufferPositionNotifies[i].Offset = bufferSize * (i + 1) - 1;
                bufferPositionNotifies[i].EventNotifyHandle = notificationEvent.SafeWaitHandle.DangerousGetHandle();
            }
            Notify notify = new Notify(captureBuffer);
            notify.SetNotificationPositions(bufferPositionNotifies, BUFFER_POSITIONS);

            Device playbackDevice = new Device();
            playbackDevice.SetCooperativeLevel(this, CooperativeLevel.Priority);
            BufferDescription playbackBufferDescription = new BufferDescription();
            playbackBufferDescription.BufferBytes = bufferSize;
            playbackBufferDescription.Format = waveFormat;
            playbackBufferDescription.DeferLocation = true;
            playbackBufferDescription.GlobalFocus = true;
            playbackBuffer = new SecondaryBuffer(playbackBufferDescription, playbackDevice);
        }

        private void CaptureSoundData()
        {
            captureBuffer.Start(true);

            int offset = 0;
            while (capturing)
            {
                notificationEvent.WaitOne(Timeout.Infinite, true);

                byte[] soundData = (byte[])captureBuffer.Read(offset, typeof(byte), LockFlag.None, bufferSize);
                if (checkBoxAddNoise.Checked)
                    for (int i = 0; i < bufferSize; i++)
                        soundData[i] += (byte)random.Next(byte.MinValue, byte.MaxValue);
                testSoundServiceClient.WriteSoundData(soundData);

                offset = (offset + bufferSize) % (BUFFER_POSITIONS * bufferSize);
            }
        }

        private void PlaySoundData()
        {
            while (playing)
            {
                if (testSoundServiceClient.IsSoundDataUpdated())
                {
                    playbackBuffer.Write(0, testSoundServiceClient.ReadSoundData(), LockFlag.None);
                    playbackBuffer.SetCurrentPosition(0);
                    playbackBuffer.Play(0, BufferPlayFlags.Default); 
                }
            }
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            capturing = false;
            playing = false;
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            try
            {
                controllerServiceClient = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(),
                        new EndpointAddress(textBoxControllerServiceUri.Text));
            }
            catch (Exception)
            {
                MessageBox.Show("Can't access controller service.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            try
            {
                BasicHttpBinding binding = new BasicHttpBinding();
                binding.BypassProxyOnLocal = true;
                binding.MaxReceivedMessageSize = MAX_RECEIVED_MESSAGE_SIZE;
                binding.OpenTimeout = TimeSpan.FromMinutes(5);
                binding.CloseTimeout = TimeSpan.FromMinutes(5);
                binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
                binding.SendTimeout = TimeSpan.FromMinutes(30);
                binding.ReaderQuotas.MaxArrayLength = MAX_ARRAY_LENGTH;

                testSoundServiceClient = ChannelFactory<TestSoundServiceContract>.CreateChannel(binding,
                        new EndpointAddress(controllerServiceClient.GetServiceUri(ServiceType.TestSoundService)));
            }
            catch (Exception)
            {
                MessageBox.Show("Can't access test sound service service.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            textBoxControllerServiceUri.ReadOnly = true;
            buttonConnect.Enabled = false;
            buttonStartStopCapturing.Enabled = true;
            buttonStartStopPlaying.Enabled = true;
        }

        private void buttonStartStopCapturing_Click(object sender, EventArgs e)
        {
            switch (buttonStartStopCapturing.Text)
            {
                case "Start Capturing":
                    capturing = true;
                    capturingThread = new Thread(new ThreadStart(CaptureSoundData));
                    capturingThread.IsBackground = true;
                    capturingThread.Start();

                    buttonStartStopCapturing.Text = "Stop Capturing";
                    break;
                case "Stop Capturing":
                    capturing = false;

                    buttonStartStopCapturing.Text = "Start Capturing";
                    break;
            }
        }

        private void buttonStartStopPlaying_Click(object sender, EventArgs e)
        {
            switch (buttonStartStopPlaying.Text)
            {
                case "Start Playing":
                    playing = true;
                    playingThread = new Thread(new ThreadStart(PlaySoundData));
                    playingThread.IsBackground = true;
                    playingThread.Start();

                    buttonStartStopPlaying.Text = "Stop Playing";
                    break;
                case "Stop Playing":
                    playing = false;

                    buttonStartStopPlaying.Text = "Start Playing";
                    break;
            }
        }
    }
}