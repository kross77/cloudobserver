using System;
using System.Collections.Generic;

namespace CloudObserver.Silverlight.Formats.Audio
{
    /// <summary>
    /// Raw wave PCM format.
    /// </summary>
    [AudioFormat("PCM")]
    public class PcmAudioFormat : AudioFormatBase, IEquatable<PcmAudioFormat>
    {
        public static readonly PcmAudioFormat Pcm8kHz8bitMono = new PcmAudioFormat(8000, 8, 1);
        public static readonly PcmAudioFormat Pcm8kHz8bitStereo = new PcmAudioFormat(8000, 8, 2);
        public static readonly PcmAudioFormat Pcm8kHz16bitMono = new PcmAudioFormat(8000, 16, 1);
        public static readonly PcmAudioFormat Pcm8kHz16bitStereo = new PcmAudioFormat(8000, 16, 2);

        public static readonly PcmAudioFormat Pcm11kHz8bitMono = new PcmAudioFormat(11025, 8, 1);
        public static readonly PcmAudioFormat Pcm11kHz8bitStereo = new PcmAudioFormat(11025, 8, 2);
        public static readonly PcmAudioFormat Pcm11kHz16bitMono = new PcmAudioFormat(11025, 16, 1);
        public static readonly PcmAudioFormat Pcm11kHz16bitStereo = new PcmAudioFormat(11025, 16, 2);

        public static readonly PcmAudioFormat Pcm22kHz8bitMono = new PcmAudioFormat(22050, 8, 1);
        public static readonly PcmAudioFormat Pcm22kHz8bitStereo = new PcmAudioFormat(22050, 8, 2);
        public static readonly PcmAudioFormat Pcm22kHz16bitMono = new PcmAudioFormat(22050, 16, 1);
        public static readonly PcmAudioFormat Pcm22kHz16bitStereo = new PcmAudioFormat(22050, 16, 2);

        public static readonly PcmAudioFormat Pcm44kHz8bitMono = new PcmAudioFormat(44100, 8, 1);
        public static readonly PcmAudioFormat Pcm44kHz8bitStereo = new PcmAudioFormat(44100, 8, 2);
        public static readonly PcmAudioFormat Pcm44kHz16bitMono = new PcmAudioFormat(44100, 16, 1);
        public static readonly PcmAudioFormat Pcm44kHz16bitStereo = new PcmAudioFormat(44100, 16, 2);

        public static readonly PcmAudioFormat Pcm48kHz8bitMono = new PcmAudioFormat(48000, 8, 1);
        public static readonly PcmAudioFormat Pcm48kHz8bitStereo = new PcmAudioFormat(48000, 8, 2);
        public static readonly PcmAudioFormat Pcm48kHz16bitMono = new PcmAudioFormat(48000, 16, 1);
        public static readonly PcmAudioFormat Pcm48kHz16bitStereo = new PcmAudioFormat(48000, 16, 2);

        /// <summary>
        /// List of most popular PCM formats.
        /// </summary>
        public static readonly IEnumerable<PcmAudioFormat> StandardFormats = new PcmAudioFormat[]
        {
            Pcm8kHz8bitMono,
            Pcm8kHz8bitStereo,
            Pcm8kHz16bitMono,
            Pcm8kHz16bitStereo,

            Pcm11kHz8bitMono,
            Pcm11kHz8bitStereo,
            Pcm11kHz16bitMono,
            Pcm11kHz16bitStereo,

            Pcm22kHz8bitMono,
            Pcm22kHz8bitStereo,
            Pcm22kHz16bitMono,
            Pcm22kHz16bitStereo,

            Pcm44kHz8bitMono,
            Pcm44kHz8bitStereo,
            Pcm44kHz16bitMono,
            Pcm44kHz16bitStereo,

            Pcm48kHz8bitMono,
            Pcm48kHz8bitStereo,
            Pcm48kHz16bitMono,
            Pcm48kHz16bitStereo,
        };

        private int samplesPerSecond;
        private short bitsPerSample;
        private short channels;

        public int SamplesPerSecond
        {
            get { return samplesPerSecond; }
        }

        public short BitsPerSample
        {
            get { return bitsPerSample; }
        }

        public short Channels
        {
            get { return channels; }
        }

        public short BlockAlign
        {
            get { return (short)(Channels * (BitsPerSample / 8)); }
        }

        public int AverageBytesPerSecond
        {
            get { return BlockAlign * SamplesPerSecond; }
        }

        public override string Description
        {
            get { return ToString(); }
        }
        
        public static bool operator ==(PcmAudioFormat format1, PcmAudioFormat format2)
        {
            return format1.Equals(format2);
        }
        
        public static bool operator !=(PcmAudioFormat format1, PcmAudioFormat format2)
        {
            return !(format1 == format2);
        }
        
        public bool Equals(PcmAudioFormat other)
        {
            return ReferenceEquals(other, this)
                || (!ReferenceEquals(other, null)
                && this.SamplesPerSecond == other.SamplesPerSecond
                && this.BitsPerSample == other.BitsPerSample
                && this.Channels == other.Channels);
        }
        
        public override bool Equals(object obj)
        {
            if (!(obj is PcmAudioFormat))
                return false;
            return Equals((PcmAudioFormat)obj);
        }
        
        public override int GetHashCode()
        {
            return samplesPerSecond * bitsPerSample * channels;
        }
        
        public override string ToString()
        {
            string channelsText;
            switch (channels)
            {
                case 1:
                    channelsText = "Mono";
                    break;
                case 2:
                    channelsText = "Stereo";
                    break;
                default:
                    channelsText = channels + " channels";
                    break;
            }
            return string.Format("{0} Hz, {1} bit, {2}", samplesPerSecond, bitsPerSample, channelsText);
        }

        public PcmAudioFormat(int samplesPerSecond, short bitsPerSample, short channels)
        {
            this.samplesPerSecond = samplesPerSecond;
            this.bitsPerSample = bitsPerSample;
            this.channels = channels;
        }
    }
}