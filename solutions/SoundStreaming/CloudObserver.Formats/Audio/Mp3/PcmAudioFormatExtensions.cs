using System;
using System.Collections.Generic;

namespace CloudObserver.Formats.Audio.Mp3
{
    public static class PcmAudioFormatExtensions
    {
        public static MpegVersion GetCompatibleMpegVersion(this PcmAudioFormat sourceFormat)
        {
            foreach (MpegVersion version in MpegVersion.All)
                foreach (PcmAudioFormat soundFormat in version.CompatibleSourceFormats)
                    if (soundFormat == sourceFormat)
                        return version;
            return MpegVersion.None;
        }

        public static IEnumerable<Mp3BitRate> GetCompatibleMp3BitRates(this PcmAudioFormat sourceFormat)
        {
            return sourceFormat.GetCompatibleMpegVersion().CompatibleBitRates;
        }
    }
}