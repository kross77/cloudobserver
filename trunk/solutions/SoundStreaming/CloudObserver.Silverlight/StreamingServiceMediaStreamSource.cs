using System;
using System.IO;
using System.Text;
using System.ServiceModel;
using System.Globalization;
using System.Windows.Media;
using System.Collections.Generic;

using CloudObserver.Services;
using CloudObserver.Formats;
using CloudObserver.Formats.Audio;

namespace CloudObserver.Silverlight
{
    public class StreamingServiceMediaStreamSource : MediaStreamSource
    {
        private MemoryStream stream;
        private WaveFormatEx waveFormat;
        private string streamingServiceUri;
        private StreamingServiceClient streamingServiceClient;

        private bool opened = false;
        private long currentTimeStamp;
        private MediaStreamDescription mediaStreamDescription;
        private Dictionary<MediaSampleAttributeKeys, string> emptySampleDict = new Dictionary<MediaSampleAttributeKeys, string>();

        public event EventHandler NeedsReloading;

        public StreamingServiceMediaStreamSource(string streamingServiceUri)
        {
            stream = new MemoryStream();
            this.streamingServiceUri = streamingServiceUri;

            streamingServiceClient = new StreamingServiceClient(new ExternalPollingDuplexHttpBinding(), new EndpointAddress(streamingServiceUri));
            streamingServiceClient.DataCallbackReceived += new EventHandler<DataCallbackReceivedEventArgs>(streamingServiceClient_DataCallbackReceived);
            streamingServiceClient.SubscriptionResponseReceived += new EventHandler<SubscriptionResponseReceivedEventArgs>(streamingServiceClient_SubscriptionResponseReceived);
        }

        void streamingServiceClient_DataCallbackReceived(object sender, DataCallbackReceivedEventArgs e)
        {
            if (opened)
                stream.Write(e.data, 0, e.data.Length);
        }

        void streamingServiceClient_SubscriptionResponseReceived(object sender, SubscriptionResponseReceivedEventArgs e)
        {
            if (opened)
            {
                NeedsReloading.Invoke(this, EventArgs.Empty);
                return;
            }
            if ((e.response != null) && (e.response.Length >= 4))
            {
                string formatIdentifier = Encoding.UTF8.GetString(e.response, 0, 4);
                switch (formatIdentifier)
                {
                    case FormatIdentifiers.FormatPcm:
                        byte[] waveFormatBytes = new byte[e.response.Length - 4];
                        Array.Copy(e.response, 4, waveFormatBytes, 0, e.response.Length - 4);
                        waveFormat = new WaveFormatEx(waveFormatBytes);

                        Dictionary<MediaStreamAttributeKeys, string> streamAttributes = new Dictionary<MediaStreamAttributeKeys, string>();
                        Dictionary<MediaSourceAttributesKeys, string> sourceAttributes = new Dictionary<MediaSourceAttributesKeys, string>();
                        List<MediaStreamDescription> availableStreams = new List<MediaStreamDescription>();

                        streamAttributes[MediaStreamAttributeKeys.CodecPrivateData] = waveFormat.ToHexString();
                        mediaStreamDescription = new MediaStreamDescription(MediaStreamType.Audio, streamAttributes);
                        availableStreams.Add(mediaStreamDescription);

                        sourceAttributes[MediaSourceAttributesKeys.Duration] = TimeSpan.FromMinutes(0).Ticks.ToString(CultureInfo.InvariantCulture);
                        sourceAttributes[MediaSourceAttributesKeys.CanSeek] = Boolean.FalseString;

                        currentTimeStamp = 0;

                        ReportOpenMediaCompleted(sourceAttributes, availableStreams);

                        opened = true;
                        break;
                }
            }
        }

        protected override void OpenMediaAsync()
        {
            streamingServiceClient.SubscribeAsync(TimeSpan.FromMinutes(10));
        }

        protected override void CloseMedia()
        {
            mediaStreamDescription = null;
            streamingServiceClient.UnsubscribeAsync();
            streamingServiceClient.CloseAsync();
        }

        protected override void GetDiagnosticAsync(MediaStreamSourceDiagnosticKind diagnosticKind)
        {
            throw new NotImplementedException();
        }

        protected override void GetSampleAsync(MediaStreamType mediaStreamType)
        {
            MediaStreamSample mediaStreamSample = new MediaStreamSample(mediaStreamDescription, stream, 0, stream.Length, currentTimeStamp, emptySampleDict);
            currentTimeStamp += waveFormat.AudioDurationFromBufferSize((uint)stream.Length);
            ReportGetSampleCompleted(mediaStreamSample);

            stream = new MemoryStream();
        }

        protected override void SeekAsync(long seekToTime)
        {
            ReportSeekCompleted(seekToTime);
        }

        protected override void SwitchMediaStreamAsync(MediaStreamDescription mediaStreamDescription)
        {
            throw new NotImplementedException();
        }
    }
}