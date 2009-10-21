using System;
using System.IO;
using System.ServiceModel;
using System.Globalization;
using System.Windows.Media;
using System.Collections.Generic;

using CloudObserver.Services.StreamingService;

namespace SoundStreaming.SilverlightReceiver
{
    public class StreamingServicePcmMediaStreamSource : MediaStreamSource
    {
        #region Fields

        private bool opened = false;
        private WaveFormatEx waveFormat;
        private MediaStreamDescription mediaStreamDescription;
        private long currentPosition;
        private long startPosition;
        private long currentTimeStamp;
        private MemoryStream stream;
        private Random random = new Random();
        private Dictionary<MediaSampleAttributeKeys, string> emptySampleDict = new Dictionary<MediaSampleAttributeKeys, string>();

        private int readPosition;
        private string streamingServiceUri;
        private StreamingServiceClient streamingServiceClient;

        #endregion

        #region Constants

        private const short channels = 1;
        private const short bitsPerSample = 16;
        private const int samplesPerSecond = 44100;
        private const int bytesPerSecond = samplesPerSecond * channels * bitsPerSample / 8;
        private const int blockSize = bytesPerSecond / 2;

        private const int maxReceivedMessageSize = 2147483647;
        private const int maxArrayLength = 2147483647;

        #endregion

        #region Constructors

        public StreamingServicePcmMediaStreamSource(string streamingServiceUri)
        {
            waveFormat = new WaveFormatEx();
            waveFormat.Channels = channels;
            waveFormat.BitsPerSample = bitsPerSample;
            waveFormat.SamplesPerSec = samplesPerSecond;
            waveFormat.AvgBytesPerSec = bytesPerSecond;
            waveFormat.FormatTag = WaveFormatEx.FormatPCM;
            waveFormat.BlockAlign = channels * bitsPerSample / 8;
            waveFormat.Size = 0;
            waveFormat.ext = null;
            waveFormat.ValidateWaveFormat();

            stream = new MemoryStream();
            this.streamingServiceUri = streamingServiceUri;
        }

        #endregion

        #region Overrides

        protected override void OpenMediaAsync()
        {
            BasicHttpBinding binding = new BasicHttpBinding();
            binding.MaxReceivedMessageSize = maxReceivedMessageSize;
            binding.MaxBufferSize = maxArrayLength;
            binding.OpenTimeout = TimeSpan.FromMinutes(5);
            binding.CloseTimeout = TimeSpan.FromMinutes(5);
            binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
            binding.SendTimeout = TimeSpan.FromMinutes(30);
            streamingServiceClient = new StreamingServiceClient(binding, new EndpointAddress(streamingServiceUri));
            streamingServiceClient.SynchronizeCompleted += new EventHandler<SynchronizeCompletedEventArgs>(streamingServiceClient_SynchronizeCompleted);
            streamingServiceClient.ReadCompleted += new EventHandler<ReadCompletedEventArgs>(streamingServiceProxy_ReadCompleted);
            streamingServiceClient.SynchronizeAsync();
        }

        protected override void CloseMedia()
        {
            startPosition = currentPosition = 0;
            mediaStreamDescription = null;
            streamingServiceClient.CloseAsync();
        }

        protected override void GetDiagnosticAsync(MediaStreamSourceDiagnosticKind diagnosticKind)
        {
            throw new NotImplementedException();
        }

        protected override void GetSampleAsync(MediaStreamType mediaStreamType)
        {
            streamingServiceClient.ReadAsync(0, blockSize, readPosition, false);
        }

        protected override void SeekAsync(long seekToTime)
        {
            ReportSeekCompleted(seekToTime);
        }

        protected override void SwitchMediaStreamAsync(MediaStreamDescription mediaStreamDescription)
        {
            throw new NotImplementedException();
        }

        #endregion

        #region Public Methods

        public void Synchronize()
        {
            streamingServiceClient.SynchronizeAsync();
        }

        #endregion

        #region Private Methods

        private void streamingServiceClient_SynchronizeCompleted(object sender, SynchronizeCompletedEventArgs e)
        {
            readPosition = e.Result;

            if (!opened)
            {
                startPosition = currentPosition = 0;

                Dictionary<MediaStreamAttributeKeys, string> streamAttributes = new Dictionary<MediaStreamAttributeKeys, string>();
                Dictionary<MediaSourceAttributesKeys, string> sourceAttributes = new Dictionary<MediaSourceAttributesKeys, string>();
                List<MediaStreamDescription> availableStreams = new List<MediaStreamDescription>();

                streamAttributes[MediaStreamAttributeKeys.CodecPrivateData] = waveFormat.ToHexString();
                mediaStreamDescription = new MediaStreamDescription(MediaStreamType.Audio, streamAttributes);
                availableStreams.Add(mediaStreamDescription);

                sourceAttributes[MediaSourceAttributesKeys.Duration] = TimeSpan.FromMinutes(0).Ticks.ToString(CultureInfo.InvariantCulture);
                sourceAttributes[MediaSourceAttributesKeys.CanSeek] = false.ToString();

                ReportOpenMediaCompleted(sourceAttributes, availableStreams);
                opened = true;
            }
        }

        private void streamingServiceProxy_ReadCompleted(object sender, ReadCompletedEventArgs e)
        {
            stream.Write(e.buffer, 0, e.Result);
            readPosition = e.position;
            MediaStreamSample mediaStreamSample = new MediaStreamSample(mediaStreamDescription, stream, currentPosition, e.Result, currentTimeStamp, emptySampleDict);
            currentTimeStamp += waveFormat.AudioDurationFromBufferSize((uint)e.Result);
            currentPosition += e.Result;

            ReportGetSampleCompleted(mediaStreamSample);
        }

        #endregion
    }
}