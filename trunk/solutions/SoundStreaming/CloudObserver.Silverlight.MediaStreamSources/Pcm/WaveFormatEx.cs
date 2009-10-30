using System;
using System.Globalization;

namespace CloudObserver.Silverlight.MediaStreamSources.Pcm
{
    public class WaveFormatEx
    {
        #region Data
        public short FormatTag { get; set; }
        public short Channels { get; set; }
        public int SamplesPerSec { get; set; }
        public int AvgBytesPerSec { get; set; }
        public short BlockAlign { get; set; }
        public short BitsPerSample { get; set; }
        public short Size { get; set; }
        public const uint SizeOf = 18;
        public byte[] ext { get; set; }
        #endregion Data

        /// <summary>
        /// Convert the data to a hex string
        /// </summary>
        /// <returns></returns>
        public string ToHexString()
        {
            string s = "";
            s += (string.Format(CultureInfo.InvariantCulture, "{0:X4}", FormatTag)).ToLittleEndian();
            s += (string.Format(CultureInfo.InvariantCulture, "{0:X4}", Channels)).ToLittleEndian();
            s += (string.Format(CultureInfo.InvariantCulture, "{0:X8}", SamplesPerSec)).ToLittleEndian();
            s += (string.Format(CultureInfo.InvariantCulture, "{0:X8}", AvgBytesPerSec)).ToLittleEndian();
            s += (string.Format(CultureInfo.InvariantCulture, "{0:X4}", BlockAlign)).ToLittleEndian();
            s += (string.Format(CultureInfo.InvariantCulture, "{0:X4}", BitsPerSample)).ToLittleEndian();
            s += (string.Format(CultureInfo.InvariantCulture, "{0:X4}", Size)).ToLittleEndian();
            return s;
        }

        /// <summary>
        /// Set the data from a byte array (usually read from a file)
        /// </summary>
        /// <param name="byteArray"></param>
        public void SetFromByteArray(byte[] byteArray)
        {
            if ((byteArray.Length + 2) < SizeOf)
            {
                throw new ArgumentException("Byte array is too small");
            }

            FormatTag = BitConverter.ToInt16(byteArray, 0);
            Channels = BitConverter.ToInt16(byteArray, 2);
            SamplesPerSec = BitConverter.ToInt32(byteArray, 4);
            AvgBytesPerSec = BitConverter.ToInt32(byteArray, 8);
            BlockAlign = BitConverter.ToInt16(byteArray, 12);
            BitsPerSample = BitConverter.ToInt16(byteArray, 14);
            if (byteArray.Length >= SizeOf)
            {
                Size = BitConverter.ToInt16(byteArray, 16);
            }
            else
            {
                Size = 0;
            }

            if (byteArray.Length > WaveFormatEx.SizeOf)
            {
                ext = new byte[byteArray.Length - WaveFormatEx.SizeOf];
                Array.Copy(byteArray, (int)WaveFormatEx.SizeOf, ext, 0, ext.Length);
            }
            else
            {
                ext = null;
            }
        }

        /// <summary>
        /// Ouput the data into a string.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            char[] rawData = new char[18];
            BitConverter.GetBytes(FormatTag).CopyTo(rawData, 0);
            BitConverter.GetBytes(Channels).CopyTo(rawData, 2);
            BitConverter.GetBytes(SamplesPerSec).CopyTo(rawData, 4);
            BitConverter.GetBytes(AvgBytesPerSec).CopyTo(rawData, 8);
            BitConverter.GetBytes(BlockAlign).CopyTo(rawData, 12);
            BitConverter.GetBytes(BitsPerSample).CopyTo(rawData, 14);
            BitConverter.GetBytes(Size).CopyTo(rawData, 16);
            return new string(rawData);
        }

        /// <summary>
        /// Calculate the duration of audio based on the size of the buffer
        /// </summary>
        /// <param name="cbAudioDataSize"></param>
        /// <returns></returns>
        public Int64 AudioDurationFromBufferSize(UInt32 cbAudioDataSize)
        {
            if (AvgBytesPerSec == 0)
            {
                return 0;
            }

            return (Int64)(cbAudioDataSize * 10000000 / AvgBytesPerSec);
        }

        /// <summary>
        /// Calculate the buffer size necessary for a duration of audio
        /// </summary>
        /// <param name="duration"></param>
        /// <returns></returns>
        public Int64 BufferSizeFromAudioDuration(Int64 duration)
        {
            Int64 size = duration * AvgBytesPerSec / 10000000;
            UInt32 remainder = (UInt32)(size % BlockAlign);
            if (remainder != 0)
            {
                size += BlockAlign - remainder;
            }

            return size;
        }

        public const Int16 FormatPCM = 1;
        public const Int16 FormatIEEE = 3;
    }
}