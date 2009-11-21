using System;
using System.IO;
using System.Text;
using System.ServiceModel;
using System.Globalization;
using System.Windows.Media;
using System.Collections.Generic;

using CloudObserver.Tools;
using CloudObserver.Services;
using CloudObserver.Formats;
using CloudObserver.Formats.Audio;
using CloudObserver.Formats.Audio.Mp3;

namespace CloudObserver.Silverlight
{
    public class StreamingServiceMediaStreamSource : MediaStreamSource
    {
        private MemoryStream mediaStream;
        private WaveFormatEx waveFormat;
        private string streamingServiceUri;
        private StreamingServiceClient streamingServiceClient;
        private string formatIdentifier = "";
        private byte[] formatData;

        private bool opening = false;
        private long currentFrameStartPosition;
        private int currentFrameSize;
        private long currentTimeStamp;
        private MediaStreamDescription mediaStreamDescription;
        private Dictionary<MediaSampleAttributeKeys, string> emptySampleDict = new Dictionary<MediaSampleAttributeKeys, string>();

        public event EventHandler NeedsReloading;

        public StreamingServiceMediaStreamSource(string streamingServiceUri)
        {
            mediaStream = new MemoryStream();
            this.streamingServiceUri = streamingServiceUri;

            streamingServiceClient = new StreamingServiceClient(new ExternalPollingDuplexHttpBinding(), new EndpointAddress(streamingServiceUri));
            streamingServiceClient.DataCallbackReceived += new EventHandler<DataCallbackReceivedEventArgs>(streamingServiceClient_DataCallbackReceived);
            streamingServiceClient.SubscriptionResponseReceived += new EventHandler<SubscriptionResponseReceivedEventArgs>(streamingServiceClient_SubscriptionResponseReceived);
        }

        void streamingServiceClient_DataCallbackReceived(object sender, DataCallbackReceivedEventArgs e)
        {
            long currentPosition = mediaStream.Position;
            mediaStream.Seek(0, SeekOrigin.End);
            mediaStream.Write(e.data, 0, e.data.Length);
            mediaStream.Position = currentPosition;
            if (opening) OpenMedia();
        }

        private void OpenMedia()
        {
            Dictionary<MediaStreamAttributeKeys, string> mediaStreamAttributes = new Dictionary<MediaStreamAttributeKeys, string>();
            Dictionary<MediaSourceAttributesKeys, string> mediaSourceAttributes = new Dictionary<MediaSourceAttributesKeys, string>();
            List<MediaStreamDescription> mediaStreamDescriptions = new List<MediaStreamDescription>();

            switch (formatIdentifier)
            {
                case FormatIdentifiers.FormatPcm:
                    waveFormat = new WaveFormatEx(formatData);

                    mediaStreamAttributes[MediaStreamAttributeKeys.CodecPrivateData] = waveFormat.ToHexString();
                    mediaStreamDescription = new MediaStreamDescription(MediaStreamType.Audio, mediaStreamAttributes);
                    mediaStreamDescriptions.Add(mediaStreamDescription);

                    mediaSourceAttributes[MediaSourceAttributesKeys.Duration] = TimeSpan.FromMinutes(0).Ticks.ToString(CultureInfo.InvariantCulture);
                    mediaSourceAttributes[MediaSourceAttributesKeys.CanSeek] = Boolean.FalseString;

                    currentTimeStamp = 0;

                    ReportOpenMediaCompleted(mediaSourceAttributes, mediaStreamDescriptions);
                    opening = false;
                    break;
                case FormatIdentifiers.FormatMp3:
                    byte[] audioData = new byte[mediaStream.Length];
                    mediaStream.Read(audioData, 0, audioData.Length);

                    int result = BitTools.FindBitPattern(audioData, new byte[2] { 255, 240 }, new byte[2] { 255, 240 });
                    if (result != -1)
                    {
                        mediaStream.Position = result;
                        MpegFrame mpegLayer3Frame = new MpegFrame(mediaStream);
                        MpegLayer3WaveFormatEx mpegLayer3WaveFormatEx = new MpegLayer3WaveFormatEx();
                        mpegLayer3WaveFormatEx.WaveFormatExtensible = new WaveFormatEx();
                        mpegLayer3WaveFormatEx.WaveFormatExtensible.FormatTag = 85;
                        mpegLayer3WaveFormatEx.WaveFormatExtensible.Channels = (short)((mpegLayer3Frame.Channels == Channel.SingleChannel) ? 1 : 2);
                        mpegLayer3WaveFormatEx.WaveFormatExtensible.SamplesPerSec = mpegLayer3Frame.SamplingRate;
                        mpegLayer3WaveFormatEx.WaveFormatExtensible.AverageBytesPerSecond = mpegLayer3Frame.Bitrate / 8;
                        mpegLayer3WaveFormatEx.WaveFormatExtensible.BlockAlign = 1;
                        mpegLayer3WaveFormatEx.WaveFormatExtensible.BitsPerSample = 0;
                        mpegLayer3WaveFormatEx.WaveFormatExtensible.Size = 12;
                        mpegLayer3WaveFormatEx.Id = 1;
                        mpegLayer3WaveFormatEx.BitratePaddingMode = 0;
                        mpegLayer3WaveFormatEx.FramesPerBlock = 1;
                        mpegLayer3WaveFormatEx.BlockSize = (short)mpegLayer3Frame.FrameSize;
                        mpegLayer3WaveFormatEx.CodecDelay = 0;

                        mediaStreamAttributes[MediaStreamAttributeKeys.CodecPrivateData] = mpegLayer3WaveFormatEx.ToHexString();
                        mediaStreamDescription = new MediaStreamDescription(MediaStreamType.Audio, mediaStreamAttributes);
                        mediaStreamDescriptions.Add(mediaStreamDescription);

                        mediaSourceAttributes[MediaSourceAttributesKeys.Duration] = TimeSpan.FromMinutes(5).Ticks.ToString(CultureInfo.InvariantCulture);
                        mediaSourceAttributes[MediaSourceAttributesKeys.CanSeek] = Boolean.FalseString;

                        currentTimeStamp = 0;
                        currentFrameStartPosition = result;
                        currentFrameSize = mpegLayer3Frame.FrameSize;

                        ReportOpenMediaCompleted(mediaSourceAttributes, mediaStreamDescriptions);
                        opening = false;
                    }
                    break;
                case FormatIdentifiers.FormatNone:
                default:
                    opening = false;
                    break;
            }
        }

        void streamingServiceClient_SubscriptionResponseReceived(object sender, SubscriptionResponseReceivedEventArgs e)
        {
            if (formatIdentifier != "")
            {
                NeedsReloading.Invoke(this, EventArgs.Empty);
                return;
            }
            formatIdentifier = Encoding.UTF8.GetString(e.response, 0, 4);
            if (e.response.Length > 4)
            {
                formatData = new byte[e.response.Length - 4];
                Array.Copy(e.response, 4, formatData, 0, e.response.Length - 4);
            }
            opening = true;
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
            MediaStreamSample mediaStreamSample;
            switch (formatIdentifier)
            {
                case FormatIdentifiers.FormatPcm:
                    mediaStreamSample = new MediaStreamSample(mediaStreamDescription, mediaStream, 0, mediaStream.Length, currentTimeStamp, emptySampleDict);
                    currentTimeStamp += waveFormat.AudioDurationFromBufferSize((uint)mediaStream.Length);
                    ReportGetSampleCompleted(mediaStreamSample);

                    mediaStream = new MemoryStream();
                    break;
                case FormatIdentifiers.FormatMp3:
                    if (currentFrameStartPosition + currentFrameSize >= mediaStream.Length)
                        return;
                    mediaStreamSample = new MediaStreamSample(mediaStreamDescription, mediaStream, currentFrameStartPosition, currentFrameSize, 0, emptySampleDict);
                    ReportGetSampleCompleted(mediaStreamSample);

                    MpegFrame nextFrame = new MpegFrame(mediaStream);
                    if (nextFrame.Version == 1 && nextFrame.Layer == 3)
                    {
                        this.currentFrameStartPosition = mediaStream.Position - 4;
                        this.currentFrameSize = nextFrame.FrameSize;
                    }
                    break;
            }
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