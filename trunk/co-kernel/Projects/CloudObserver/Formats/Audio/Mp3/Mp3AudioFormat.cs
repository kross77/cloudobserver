using System;
using System.Collections.Generic;

namespace CloudObserver.Formats.Audio.Mp3
{
    [AudioFormat("MP3")]
    public partial class Mp3AudioFormat : AudioFormatBase, IEquatable<Mp3AudioFormat>
    {
        /// <summary>
        /// In this library the MP3 format can be acquired only by compressing this subset of
        /// PCM formats. However not each source format is compatible with each bit rate.
        /// Use Mp3BitRate.CompatibleSourceFormats property or PcmAudioFormat.GetCompatibleMp3BitRates() method
        /// to get allowed combinations.
        /// </summary>
        public static IEnumerable<PcmAudioFormat> AllSourceFormats
        {
            get
            {
                foreach (MpegVersion version in MpegVersion.All)
                    foreach (PcmAudioFormat sourceFormat in version.CompatibleSourceFormats)
                        yield return sourceFormat;
            }
        }

        /// <summary>
        /// PCM format of data from which the MP3 will be created.
        /// </summary>
        public PcmAudioFormat SourceFormat { get; private set; }

        /// <summary>
        /// MP3 bit rate.
        /// </summary>
        public Mp3BitRate mp3BitRate { get; private set; }

        public override string Description
        {
            get { return ToString(); }
        }

        public override string ToString()
        {
            return string.Format("{0} kbit/s MP3", mp3BitRate);
        }

        public static bool operator ==(Mp3AudioFormat format1, Mp3AudioFormat format2)
        {
            return object.ReferenceEquals(format1, format2)
                || (!ReferenceEquals(format1, null) && format1.Equals(format2));
        }

        public static bool operator !=(Mp3AudioFormat format1, Mp3AudioFormat format2)
        {
            return !(format1 == format2);
        }

        #region IEquatable<Mp3SoundFormat> Members

        public bool Equals(Mp3AudioFormat other)
        {
            return other != null
                && other.mp3BitRate == mp3BitRate
                && other.SourceFormat == SourceFormat;
        }

        #endregion

        public override bool Equals(object obj)
        {
            return this.Equals(obj as Mp3AudioFormat);
        }

        public override int GetHashCode()
        {
            return mp3BitRate.GetHashCode() * SourceFormat.GetHashCode();
        }

        /// <summary>
        /// Creates MP3 format.
        /// </summary>
        /// <param name="bitRate">MP3 bit rate (kbit/s).</param>
        /// <param name="sourceFormat">Format of PCM data from which MP3 data is created.</param>
        public Mp3AudioFormat(Mp3BitRate mp3BitRate, PcmAudioFormat sourceFormat)
        {
            this.mp3BitRate = mp3BitRate;
            this.SourceFormat = sourceFormat;
        }
    }
}