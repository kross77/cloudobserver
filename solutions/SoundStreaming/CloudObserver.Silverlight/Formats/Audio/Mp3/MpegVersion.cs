using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace CloudObserver.Formats.Audio.Mp3
{
    /// <summary>
    /// MP3 MPEG versions.
    /// </summary>
    public struct MpegVersion : IEquatable<MpegVersion>
    {
        public static readonly MpegVersion Mpeg1 = new MpegVersion("MPEG-1",
            new PcmAudioFormat(32000, 16, 1),
            new PcmAudioFormat(32000, 16, 2),
            new PcmAudioFormat(44100, 16, 1),
            new PcmAudioFormat(44100, 16, 2),
            new PcmAudioFormat(48000, 16, 1),
            new PcmAudioFormat(48000, 16, 2));

        public static readonly MpegVersion Mpeg2 = new MpegVersion("MPEG-2",
            new PcmAudioFormat(16000, 16, 1),
            new PcmAudioFormat(16000, 16, 2),
            new PcmAudioFormat(22050, 16, 1),
            new PcmAudioFormat(22050, 16, 2),
            new PcmAudioFormat(24000, 16, 1),
            new PcmAudioFormat(24000, 16, 2));

        public static readonly MpegVersion None = new MpegVersion("(None)");

        private static IEnumerable<MpegVersion> cachedAll = null;

        public static IEnumerable<MpegVersion> All
        {
            get
            {
                if (cachedAll == null)
                    lock (typeof(MpegVersion))
                        if (cachedAll == null) cachedAll = GetAllInstance();
                return cachedAll;
            }
        }

        private static IEnumerable<MpegVersion> GetAllInstance()
        {
            return new ReadOnlyCollection<MpegVersion>(new MpegVersion[] { Mpeg2, Mpeg1 });
        }

        private string name;
        private IEnumerable<PcmAudioFormat> compatibleSourceFormats;

        public string Name
        {
            get { return name; }
        }
        
        public IEnumerable<Mp3BitRate> CompatibleBitRates
        {
            get
            {
                foreach (Mp3BitRate bitRate in Mp3BitRate.AllValues)
                    foreach (MpegVersion version in bitRate.CompatibleMpegVersions)
                        if (version == this) yield return bitRate;
            }
        }

        public IEnumerable<PcmAudioFormat> CompatibleSourceFormats
        {
            get { return compatibleSourceFormats; }
        }

        public static bool operator ==(MpegVersion version1, MpegVersion version2)
        {
            return version1.Equals(version2);
        }

        public static bool operator !=(MpegVersion version1, MpegVersion version2)
        {
            return !(version1 == version2);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is MpegVersion))
                return false;
            return base.Equals((MpegVersion)obj);
        }

        public override int GetHashCode()
        {
            return name.GetHashCode();
        }

        public bool Equals(MpegVersion other)
        {
            return other.name == name;
        }

        public MpegVersion(string name, params PcmAudioFormat[] compatibleSourceFormats)
        {
            this.name = name;
            this.compatibleSourceFormats = new ReadOnlyCollection<PcmAudioFormat>(compatibleSourceFormats);
        }
    }
}