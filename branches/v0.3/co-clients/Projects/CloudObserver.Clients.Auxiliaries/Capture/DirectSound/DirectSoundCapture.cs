using System;
using System.Threading;

using CloudObserver.Clients.Auxiliaries.Formats.Audio;

namespace CloudObserver.Clients.Auxiliaries.Capture.DirectSound
{
    /// <summary>
    /// Captures raw PCM audio data using Microsoft DirectSound API.
    /// </summary>
    public class DirectSoundCapture : ICapture
    {
        /// <summary>
        /// An indicator of whether audio data is capturing.
        /// </summary>
        private bool capturing;

        /// <summary>
        /// A PCM audio format in which data is captured.
        /// </summary>
        private PcmAudioFormat pcmAudioFormat;

        /// <summary>
        /// Microsoft DirectSound device to capture audio data.
        /// </summary>
        private DirectSoundCaptureDevice directSoundCaptureDevice;

        /// <summary>
        /// Size of a chunk of audio data.
        /// </summary>
        private int chunkSize;

        /// <summary>
        /// Size of a capture buffer.
        /// </summary>
        private int captureBufferSize;

        /// <summary>
        /// A buffer to store captured audio data.
        /// </summary>
        private Microsoft.DirectX.DirectSound.CaptureBuffer captureBuffer;

        /// <summary>
        /// Microsoft.DirectX.DirectSound.WaveFormat in which data is captured.
        /// </summary>
        private Microsoft.DirectX.DirectSound.WaveFormat? cachedWaveFormat;

        /// <summary>
        /// A thread to process notifications sent by DirectSound API.
        /// </summary>
        private Thread notificationListenerThread;

        /// <summary>
        /// An event object representing notification arrival.
        /// </summary>
        private AutoResetEvent notificationArrivalEvent;

        /// <summary>
        /// Occurs when the new chunk of data has been captured.
        /// </summary>
        public event EventHandler<ChunkCapturedEventArgs> ChunkCaptured;

        /// <summary>
        /// The number of notification positions in the capture buffer.
        /// </summary>
        private const int notificationPositions = 16;

        /// <summary>
        /// Retrieves a CloudObserver.Formats.Audio.PcmAudioFormat converted into Microsoft.DirectX.DirectSound.WaveFormat.
        /// </summary>
        private Microsoft.DirectX.DirectSound.WaveFormat CaptureFormat
        {
            get
            {
                if (!cachedWaveFormat.HasValue)
                {
                    Microsoft.DirectX.DirectSound.WaveFormat waveFormat = new Microsoft.DirectX.DirectSound.WaveFormat();
                    waveFormat.FormatTag = Microsoft.DirectX.DirectSound.WaveFormatTag.Pcm;
                    waveFormat.Channels = pcmAudioFormat.Channels;
                    waveFormat.BitsPerSample = pcmAudioFormat.BitsPerSample;
                    waveFormat.SamplesPerSecond = pcmAudioFormat.SamplesPerSecond;
                    waveFormat.BlockAlign = pcmAudioFormat.BlockAlign;
                    waveFormat.AverageBytesPerSecond = pcmAudioFormat.AverageBytesPerSecond;
                    chunkSize = waveFormat.AverageBytesPerSecond / 8;
                    captureBufferSize = chunkSize * notificationPositions;

                    cachedWaveFormat = waveFormat;
                }
                return cachedWaveFormat.Value;
            }
        }

        /// <summary>
        /// Initializes a new instance of the CloudObserver.Capture.DirectSound.DirectSoundCapture class
        /// with the operating system default audio capture device and 22050 Hz, 16 bit, Mono audio format.
        /// </summary>
        public DirectSoundCapture() : this(PcmAudioFormat.Pcm22kHz16bitMono, DirectSoundCaptureDevice.Default) { }

        /// <summary>
        /// Initializes a new instance of the CloudObserver.Capture.DirectSound.DirectSoundCapture class
        /// with the provided PCM audio format and Microsoft DirectSound device.
        /// </summary>
        /// <param name="pcmAudioFormat">A PCM audio format in which data will be captured.</param>
        /// <param name="directSoundCaptureDevice">Microsoft DirectSound device to capture audio data.</param>
        public DirectSoundCapture(PcmAudioFormat pcmAudioFormat, DirectSoundCaptureDevice directSoundCaptureDevice)
        {
            this.pcmAudioFormat = pcmAudioFormat;
            this.directSoundCaptureDevice = directSoundCaptureDevice;
        }

        /// <summary>
        /// Starts capturing.
        /// </summary>
        public void Start()
        {
            capturing = true;
            InitializeDirectSound();
            captureBuffer.Start(true);
        }

        /// <summary>
        /// Stops capturing.
        /// </summary>
        public void Stop()
        {
            capturing = false;
            if (captureBuffer != null)
                captureBuffer.Stop();
        }

        /// <summary>
        /// Initializes Microsoft DirectSound capture buffer, sets notifications on it and starts notification listener thread.
        /// </summary>
        private void InitializeDirectSound()
        {
            Microsoft.DirectX.DirectSound.Capture captureDevice = (directSoundCaptureDevice == DirectSoundCaptureDevice.Default) ?
                new Microsoft.DirectX.DirectSound.Capture() : new Microsoft.DirectX.DirectSound.Capture(directSoundCaptureDevice.DriverGuid);
            Microsoft.DirectX.DirectSound.CaptureBufferDescription captureBufferDescription = new Microsoft.DirectX.DirectSound.CaptureBufferDescription();
            captureBufferDescription.Format = CaptureFormat;
            captureBufferDescription.BufferBytes = captureBufferSize;
            captureBuffer = new Microsoft.DirectX.DirectSound.CaptureBuffer(captureBufferDescription, captureDevice);

            notificationArrivalEvent = new AutoResetEvent(false);
            Microsoft.DirectX.DirectSound.BufferPositionNotify[] positionNotifies = new Microsoft.DirectX.DirectSound.BufferPositionNotify[notificationPositions];
            for (int i = 0; i < notificationPositions; i++)
            {
                positionNotifies[i].Offset = chunkSize * (i + 1) - 1;
                positionNotifies[i].EventNotifyHandle = notificationArrivalEvent.SafeWaitHandle.DangerousGetHandle();
            }

            Microsoft.DirectX.DirectSound.Notify applicationNotify = new Microsoft.DirectX.DirectSound.Notify(captureBuffer);
            applicationNotify.SetNotificationPositions(positionNotifies, notificationPositions);

            notificationListenerThread = new Thread(new ThreadStart(ListenDirectSoundNotifications));
            notificationListenerThread.IsBackground = true;
            notificationListenerThread.Start();
        }

        /// <summary>
        /// Listens Microsoft DirectSound capture buffer notifications and invokes ChunkCaptured event when a new data is captured.
        /// </summary>
        private void ListenDirectSoundNotifications()
        {
            try
            {
                int offset = 0;
                while (capturing)
                {
                    notificationArrivalEvent.WaitOne(Timeout.Infinite, true);
                    ChunkCaptured.Invoke(this, new ChunkCapturedEventArgs((byte[])captureBuffer.Read(offset, typeof(byte),
                        Microsoft.DirectX.DirectSound.LockFlag.None, chunkSize)));
                    offset = (offset + chunkSize) % captureBufferSize;
                }
            }
            finally
            {
                capturing = false;
            }
        }
    }
}
