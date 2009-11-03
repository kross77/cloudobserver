using System;
using System.Threading;
using Microsoft.DirectX.DirectSound;

using CloudObserver.Formats.Audio;

namespace CloudObserver.Capture.DirectSound
{
    /// <summary>
    /// This class captures raw PCM audio data using DirectSound technology.
    /// </summary>
    public class DirectSoundCapture : ICapture
    {
        #region Fields
        private bool capturing;
        private PcmAudioFormat pcmAudioFormat;
        private DirectSoundCaptureDevice directSoundCaptureDevice;

        private int notifySize;
        private int captureBufferSize;
        private CaptureBuffer captureBuffer;
        private Microsoft.DirectX.DirectSound.WaveFormat? cachedWaveFormat;
        private Thread notificationListenerThread;
        private AutoResetEvent notificationArrivalEvent;
        #endregion

        #region Events
        public event EventHandler<ChunkCapturedEventArgs> ChunkCaptured;
        #endregion

        #region Constants
        private const int notifyPositions = 16;
        #endregion

        #region Constructors
        public DirectSoundCapture() : this(PcmAudioFormat.Pcm22kHz16bitMono, DirectSoundCaptureDevice.Default) { }

        public DirectSoundCapture(PcmAudioFormat pcmAudioFormat, DirectSoundCaptureDevice directSoundCaptureDevice)
        {
            this.pcmAudioFormat = pcmAudioFormat;
            this.directSoundCaptureDevice = directSoundCaptureDevice;
        }
        #endregion

        #region Public Methods
        public void Start()
        {
            capturing = true;
            InitializeDirectSound();
            captureBuffer.Start(true);
        }

        public void Stop()
        {
            capturing = false;
            if (captureBuffer != null)
                captureBuffer.Stop();
        }
        #endregion

        #region Private Methods
        /// <summary>
        /// Converts PcmAudioFormat to DirectX WaveFormat.
        /// </summary>
        private Microsoft.DirectX.DirectSound.WaveFormat CaptureFormat
        {
            get
            {
                if (!cachedWaveFormat.HasValue)
                {
                    Microsoft.DirectX.DirectSound.WaveFormat waveFormat = new Microsoft.DirectX.DirectSound.WaveFormat();
                    waveFormat.FormatTag = WaveFormatTag.Pcm;
                    waveFormat.Channels = pcmAudioFormat.Channels;
                    waveFormat.BitsPerSample = pcmAudioFormat.BitsPerSample;
                    waveFormat.SamplesPerSecond = pcmAudioFormat.SamplesPerSecond;
                    waveFormat.BlockAlign = pcmAudioFormat.BlockAlign;
                    waveFormat.AverageBytesPerSecond = pcmAudioFormat.AverageBytesPerSecond;
                    notifySize = waveFormat.AverageBytesPerSecond / 8;
                    captureBufferSize = notifySize * notifyPositions;

                    cachedWaveFormat = waveFormat;
                }
                return cachedWaveFormat.Value;
            }
        }

        private void InitializeDirectSound()
        {
            Microsoft.DirectX.DirectSound.Capture captureDevice = (directSoundCaptureDevice == DirectSoundCaptureDevice.Default) ?
                new Microsoft.DirectX.DirectSound.Capture() : new Microsoft.DirectX.DirectSound.Capture(directSoundCaptureDevice.DriverGuid);
            CaptureBufferDescription captureBufferDescription = new CaptureBufferDescription();
            captureBufferDescription.Format = CaptureFormat;
            captureBufferDescription.BufferBytes = captureBufferSize;
            captureBuffer = new CaptureBuffer(captureBufferDescription, captureDevice);

            notificationArrivalEvent = new AutoResetEvent(false);
            BufferPositionNotify[] positionNotifies = new BufferPositionNotify[notifyPositions];
            for (int i = 0; i < notifyPositions; i++)
            {
                positionNotifies[i].Offset = notifySize * (i + 1) - 1;
                positionNotifies[i].EventNotifyHandle = notificationArrivalEvent.SafeWaitHandle.DangerousGetHandle();
            }

            Notify applicationNotify = new Notify(captureBuffer);
            applicationNotify.SetNotificationPositions(positionNotifies, notifyPositions);

            notificationListenerThread = new Thread(new ThreadStart(ListenDirectSoundNotifications));
            notificationListenerThread.IsBackground = true;
            notificationListenerThread.Start();
        }

        private void ListenDirectSoundNotifications()
        {
            try
            {
                int offset = 0;
                while (capturing)
                {
                    notificationArrivalEvent.WaitOne(Timeout.Infinite, true);
                    ChunkCaptured.Invoke(this, new ChunkCapturedEventArgs((byte[])captureBuffer.Read(offset, typeof(byte), LockFlag.None, notifySize)));
                    offset = (offset + notifySize) % captureBufferSize;
                }
            }
            finally
            {
                capturing = false;
            }
        }
        #endregion
    }
}