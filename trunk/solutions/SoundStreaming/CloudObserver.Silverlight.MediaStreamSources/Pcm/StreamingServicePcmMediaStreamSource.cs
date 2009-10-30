using System;
using System.IO;
using System.ServiceModel;
using System.Globalization;
using System.Windows.Media;
using System.Collections.Generic;

using CloudObserver.Silverlight.Services.Bindings;
using CloudObserver.Silverlight.Formats.Audio;
using CloudObserver.Silverlight.Formats.Audio.Mp3;

namespace CloudObserver.Silverlight.MediaStreamSources.Pcm
{
    public class StreamingServicePcmMediaStreamSource : MediaStreamSource
    {
        private bool opened = false;
        private WaveFormatEx waveFormat;
        private MediaStreamDescription mediaStreamDescription;
        private long currentPosition;
        private long startPosition;
        private long currentTimeStamp;
        private MemoryStream stream;
        private Dictionary<MediaSampleAttributeKeys, string> emptySampleDict = new Dictionary<MediaSampleAttributeKeys, string>();

        private int readPosition;
        private int blockSize;
        private string streamingServiceUri;
        private StreamingServiceClient streamingServiceClient;

        public StreamingServicePcmMediaStreamSource(PcmAudioFormat pcmAudioFormat, string streamingServiceUri)
        {
            waveFormat = new WaveFormatEx();
            waveFormat.Channels = pcmAudioFormat.Channels;
            waveFormat.BitsPerSample = pcmAudioFormat.BitsPerSample;
            waveFormat.SamplesPerSec = pcmAudioFormat.SamplesPerSecond;
            waveFormat.AvgBytesPerSec = pcmAudioFormat.AverageBytesPerSecond;
            waveFormat.FormatTag = WaveFormatEx.FormatPCM;
            waveFormat.BlockAlign = (short)(pcmAudioFormat.Channels * pcmAudioFormat.BitsPerSample / 8);
            waveFormat.Size = 0;
            waveFormat.ext = null;
            blockSize = pcmAudioFormat.AverageBytesPerSecond / 8;

            stream = new MemoryStream();
            this.streamingServiceUri = streamingServiceUri;

            streamingServiceClient = new StreamingServiceClient(new ClientHttpBinding(), new EndpointAddress(streamingServiceUri));
            streamingServiceClient.SynchronizeCompleted += new EventHandler<SynchronizeCompletedEventArgs>(streamingServiceClient_SynchronizeCompleted);
            streamingServiceClient.ReadCompleted += new EventHandler<ReadCompletedEventArgs>(streamingServiceProxy_ReadCompleted);
        }

        protected override void OpenMediaAsync()
        {
            Synchronize();
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
            streamingServiceClient.ReadAsync(blockSize, readPosition, false);
        }

        protected override void SeekAsync(long seekToTime)
        {
            ReportSeekCompleted(seekToTime);
        }

        protected override void SwitchMediaStreamAsync(MediaStreamDescription mediaStreamDescription)
        {
            throw new NotImplementedException();
        }

        public void Synchronize()
        {
            streamingServiceClient.SynchronizeAsync();
        }

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
    }
}