//using System;
//using System.Collections.Generic;
//using System.Globalization;
//using System.IO;
//using System.Windows.Media;
//using System.Windows.Threading;

//namespace CloudObserver.Silverlight.MediaStreamSources.Mp3
//{
//    /// <summary>
//    /// A Simple MediaStreamSource which can play back MP3 streams from
//    /// beginning to end.
//    /// </summary>
//    public class StreamingServiceMp3MediaStreamSource : MediaStreamSource
//    {
//        /// <summary>
//        ///  ID3 version 1 tags are 128 bytes at the end of the file.
//        ///  http://www.id3.org/ID3v1
//        /// </summary>
//        private const int Id3Version1TagSize = 128;

//        /// <summary>
//        /// Description of the Mp3 Stream being played back which includes the
//        /// MpegLayer3WaveFormat structure serialized out as a string of hex 
//        /// characters.
//        /// </summary>
//        private MediaStreamDescription audioStreamDescription;

//        /// <summary>
//        ///  The position in the stream where the current MpegFrame starts.
//        ///  For purposes of this code, the frame starts with the header and
//        ///  not after the header.
//        /// </summary>
//        private long currentFrameStartPosition;

//        /// <summary>
//        ///  The size of the MpegFrame in Bytes.
//        /// </summary>
//        private int currentFrameSize;
        
//        private MemoryStream stream;
//        private int readPosition;
//        private string streamingServiceUri;
//        private StreamingServiceClient streamingServiceClient;

//        private const int maxReceivedMessageSize = 2147483647;
//        private const int maxArrayLength = 2147483647;

//        /// <summary>
//        ///  Initializes a new instance of the Mp3MediaStreamSource class.
//        /// </summary>
//        /// <param name="audioStream">
//        /// Seekable stream containing Mp3 data
//        /// </param>
//        public StreamingServiceMp3MediaStreamSource(string streamingServiceUri)
//        {
//            stream = new MemoryStream();
//            this.streamingServiceUri = streamingServiceUri;
//        }

//        /// <summary>
//        /// Gets the MpegLayer3WaveFormat structure which represents this Mp3 file.
//        /// </summary>
//        public MpegLayer3WaveFormat MpegLayer3WaveFormat { get; private set; }

//        /// <summary>
//        /// Parses the passed in MediaStream to find the first frame and signals
//        /// to its parent MediaElement that it is ready to begin playback by calling
//        /// ReportOpenMediaCompleted.
//        /// </summary>
//        protected override void OpenMediaAsync()
//        {
//            BasicHttpBinding binding = new BasicHttpBinding();
//            binding.MaxReceivedMessageSize = maxReceivedMessageSize;
//            binding.MaxBufferSize = maxArrayLength;
//            binding.OpenTimeout = TimeSpan.FromMinutes(5);
//            binding.CloseTimeout = TimeSpan.FromMinutes(5);
//            binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
//            binding.SendTimeout = TimeSpan.FromMinutes(30);
//            streamingServiceClient = new StreamingServiceClient(binding, new EndpointAddress(streamingServiceUri));
//            streamingServiceClient.SynchronizeCompleted += new EventHandler<SynchronizeCompletedEventArgs>(streamingServiceClient_SynchronizeCompleted);
//            streamingServiceClient.ReadCompleted += new EventHandler<ReadCompletedEventArgs>(streamingServiceProxy_ReadCompleted);
//            streamingServiceClient.SynchronizeAsync();
//        }

//        private void streamingServiceClient_SynchronizeCompleted(object sender, SynchronizeCompletedEventArgs e)
//        {
//            readPosition = e.Result;
//            streamingServiceClient.ReadAsync(0, blockSize, readPosition, false);
//        }

//        private void streamingServiceProxy_ReadCompleted(object sender, ReadCompletedEventArgs e)
//        {
//            if (!opened)
//            {
//                // Initialize data structures to pass to the Media pipeline via the MediaStreamSource
//                Dictionary<MediaSourceAttributesKeys, string> mediaSourceAttributes = new Dictionary<MediaSourceAttributesKeys, string>();
//                Dictionary<MediaStreamAttributeKeys, string> mediaStreamAttributes = new Dictionary<MediaStreamAttributeKeys, string>();
//                List<MediaStreamDescription> mediaStreamDescriptions = new List<MediaStreamDescription>();


//                // Find the syncpoint of the first MpegFrame in the file.
//                int result = BitTools.FindBitPattern(e.buffer, new byte[2] { 255, 240 }, new byte[2] { 255, 240 });
//                if (result < 0)
//                {
//                    streamingServiceClient.ReadAsync(0, blockSize, readPosition, false);
//                    return;
//                }
//                stream.Write(e.buffer, result, e.buffer.Length - result);

//                // Mp3 frame validity check.
//                MpegFrame mpegLayer3Frame = new MpegFrame(stream);
//                if (mpegLayer3Frame.FrameSize <= 0)
//                {
//                    throw new InvalidOperationException("MpegFrame's FrameSize cannot be negative");
//                }

//                // Initialize the Mp3 data structures used by the Media pipeline with state from the first frame.
//                WaveFormatExtensible wfx = new WaveFormatExtensible();
//                this.MpegLayer3WaveFormat = new MpegLayer3WaveFormat();
//                this.MpegLayer3WaveFormat.WaveFormatExtensible = wfx;

//                this.MpegLayer3WaveFormat.WaveFormatExtensible.FormatTag = 85;
//                this.MpegLayer3WaveFormat.WaveFormatExtensible.Channels = (short)((mpegLayer3Frame.Channels == Channel.SingleChannel) ? 1 : 2);
//                this.MpegLayer3WaveFormat.WaveFormatExtensible.SamplesPerSec = mpegLayer3Frame.SamplingRate;
//                this.MpegLayer3WaveFormat.WaveFormatExtensible.AverageBytesPerSecond = mpegLayer3Frame.Bitrate / 8;
//                this.MpegLayer3WaveFormat.WaveFormatExtensible.BlockAlign = 1;
//                this.MpegLayer3WaveFormat.WaveFormatExtensible.BitsPerSample = 0;
//                this.MpegLayer3WaveFormat.WaveFormatExtensible.Size = 12;

//                this.MpegLayer3WaveFormat.Id = 1;
//                this.MpegLayer3WaveFormat.BitratePaddingMode = 0;
//                this.MpegLayer3WaveFormat.FramesPerBlock = 1;
//                this.MpegLayer3WaveFormat.BlockSize = (short)mpegLayer3Frame.FrameSize;
//                this.MpegLayer3WaveFormat.CodecDelay = 0;

//                mediaStreamAttributes[MediaStreamAttributeKeys.CodecPrivateData] = this.MpegLayer3WaveFormat.ToHexString();
//                this.audioStreamDescription = new MediaStreamDescription(MediaStreamType.Audio, mediaStreamAttributes);

//                mediaStreamDescriptions.Add(this.audioStreamDescription);

//                // Setting a 0 duration to avoid the math to calcualte the Mp3 file length in minutes and seconds.
//                // This was done just to simplify this initial version of the code for other people reading it.
//                mediaSourceAttributes[MediaSourceAttributesKeys.Duration] = TimeSpan.FromMinutes(5).Ticks.ToString(CultureInfo.InvariantCulture);
//                mediaSourceAttributes[MediaSourceAttributesKeys.CanSeek] = "0";

//                // Report that the Mp3MediaStreamSource has finished initializing its internal state and can now
//                // pass in Mp3 Samples.
//                this.ReportOpenMediaCompleted(mediaSourceAttributes, mediaStreamDescriptions);

//                this.currentFrameStartPosition = result;
//                this.currentFrameSize = mpegLayer3Frame.FrameSize;

//                opened = true;
//            }
//            else
//            {
//                stream.Write(e.buffer, 0, e.Result);
//                readPosition = e.position;
//                MediaStreamSample mediaStreamSample = new MediaStreamSample(mediaStreamDescription, stream, currentPosition, e.Result, currentTimeStamp, emptySampleDict);
//                currentTimeStamp += waveFormat.AudioDurationFromBufferSize((uint)e.Result);
//                currentPosition += e.Result;

//                ReportGetSampleCompleted(mediaStreamSample);
//            }
//        }

//        public void Synchronize()
//        {
//            streamingServiceClient.SynchronizeAsync();
//        }

//        /// <summary>
//        /// Parses the next sample from the requested stream and then calls ReportGetSampleCompleted
//        /// to inform its parent MediaElement of the next sample.
//        /// </summary>
//        /// <param name="mediaStreamType">
//        /// Should always be Audio for this MediaStreamSource.
//        /// </param>
//        protected override void GetSampleAsync(MediaStreamType mediaStreamType)
//        {
//            Dictionary<MediaSampleAttributeKeys, string> emptyDict = new Dictionary<MediaSampleAttributeKeys, string>();
//            MediaStreamSample audioSample = null;

//            if (this.currentFrameStartPosition + this.currentFrameSize + Id3Version1TagSize >= this.audioStream.Length)
//            {
//                // If you are near the end of the file, return a null stream, which
//                // tells the MediaStreamSource and MediaElement to close down.
//                audioSample = new MediaStreamSample(
//                    this.audioStreamDescription,
//                    null,
//                    0,
//                    0,
//                    0,
//                    emptyDict);
//                this.ReportGetSampleCompleted(audioSample);
//            }
//            else
//            {
//                // Common case. Return the next sample in the stream and find the
//                // one after it.
//                audioSample = new MediaStreamSample(
//                    this.audioStreamDescription,
//                    this.audioStream,
//                    this.currentFrameStartPosition,
//                    this.currentFrameSize,
//                    0,
//                    emptyDict);
//                this.ReportGetSampleCompleted(audioSample);

//                MpegFrame nextFrame = new MpegFrame(this.audioStream);
//                if (nextFrame.Version == 1 && nextFrame.Layer == 3)
//                {
//                    this.currentFrameStartPosition = this.audioStream.Position - 4;
//                    this.currentFrameSize = nextFrame.FrameSize;
//                }
//                else
//                {
//                    throw new InvalidOperationException("Frame Is Not MP3");
//                }
//            }
//        }

//        /// <summary>
//        ///  TODO FILL ME IN LATER
//        /// </summary>
//        protected override void CloseMedia()
//        {
//            startPosition = currentPosition = 0;
//            mediaStreamDescription = null;
//            streamingServiceClient.CloseAsync();
//        }

//        protected override void GetDiagnosticAsync(MediaStreamSourceDiagnosticKind diagnosticKind)
//        {
//            throw new NotImplementedException();
//        }

//        protected override void SeekAsync(long seekToTime)
//        {
//            this.ReportSeekCompleted(seekToTime);
//        }

//        protected override void SwitchMediaStreamAsync(MediaStreamDescription mediaStreamDescription)
//        {
//            throw new NotImplementedException();
//        }

//    }
//}