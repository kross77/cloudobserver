using System;

namespace CloudObserver.Formats
{
    /// <summary>
    /// Defines a set of 4 character string constants representing multimedia format types.
    /// </summary>
    public class FormatIdentifiers
    {
        /// <summary>
        /// Not specified format.
        /// </summary>
        public const string FormatNone = "NONE";

        /// <summary>
        /// Raw PCM audio format.
        /// </summary>
        public const string FormatPcm = "PCM ";

        /// <summary>
        /// MPEG Layer 3 audio compression format.
        /// </summary>
        public const string FormatMp3 = "MP3 ";
    }
}