using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Text;

namespace CloudObserver.Kernel.Contents
{
    public class FLVContent : Content
    {
        private List<FLVReader> readers;

        private byte[] header;
        private List<byte[]> scriptData;
        private List<byte[]> buffer;
        private uint bufferedTimestamp;

        private object locker = new Object();

        private const int HEADER_LENGTH = 13;
        private const byte SIGNATURE1 = 0x46;
        private const byte SIGNATURE2 = 0x4C;
        private const byte SIGNATURE3 = 0x56;
        private const byte VERSION = 1;
        private const int TAG_HEADER_LENGTH = 11;
        private const byte TAGTYPE_AUDIO = 8;
        private const byte TAGTYPE_VIDEO = 9;
        private const byte TAGTYPE_DATA = 18;

        public FLVContent(int id, string contentType, string ipAddress, int receiverPort, int senderPort)
            : base(id, contentType, ipAddress, receiverPort, senderPort)
        {
            readers = new List<FLVReader>();
            scriptData = new List<byte[]>();
            buffer = new List<byte[]>();
            bufferedTimestamp = 0;
        }

        protected override void OnReaderConnected(Stream stream)
        {
            lock (locker)
            {
                stream.Write(header, 0, header.Length);
                foreach (byte[] data in scriptData)
                    stream.Write(data, 0, data.Length);

                bool tagHeader = true;
                foreach (byte[] data in buffer)
                {
                    if (tagHeader)
                    {
                        // Get timestamp.
                        uint timestamp = ToUI24(data, 4);
                        // Update timestamp.
                        byte[] newTimestampValue = BitConverter.GetBytes(timestamp - bufferedTimestamp);
                        data[4] = newTimestampValue[2];
                        data[5] = newTimestampValue[1];
                        data[6] = newTimestampValue[0];
                    }
                    stream.Write(data, 0, data.Length);
                    tagHeader = !tagHeader;
                }
                readers.Add(new FLVReader(stream, bufferedTimestamp));
            }
        }

        protected override void OnWriterConnected(Stream stream)
        {
            // FLV header
            header = ReadBytes(stream, HEADER_LENGTH);
            // Signature
            if ((SIGNATURE1 != header[0]) || (SIGNATURE2 != header[1]) || (SIGNATURE3 != header[2]))
                throw new InvalidDataException("Not a valid FLV file!.");
            // Version
            if (VERSION != header[3])
                throw new InvalidDataException("Not a valid FLV file!.");
            // TypeFlags
            if (0 != (header[4] >> 3))
                throw new InvalidDataException("Not a valid FLV file!.");
            //audio = (((header[4] & 0x4) >> 2) == 1);
            if (0 != ((header[4] & 0x2) >> 1))
                throw new InvalidDataException("Not a valid FLV file!.");
            //video = ((header[4] & 0x1) == 1);
            // DataOffset
            uint dataOffset = ToUI32(header, 5);
            // PreviousTagSize0
            if (0 != ToUI32(header, 9))
                throw new InvalidDataException("Not a valid FLV file!.");

            // FLV body
            while (true)
            {
                // FLV tag header
                byte[] tagHeader = ReadBytes(stream, TAG_HEADER_LENGTH);
                // TagType
                if ((tagHeader[0] != TAGTYPE_AUDIO) && (tagHeader[0] != TAGTYPE_VIDEO) && (tagHeader[0] != TAGTYPE_DATA))
                    throw new InvalidDataException("Not a valid FLV file!.");
                // DataSize
                uint dataSize = ToUI24(tagHeader, 1);
                // Timestamp
                uint timestamp = ToUI24(tagHeader, 4);
                // TimestampExtended
                //uint timestampExtended = tagHeader[7];
                // StreamID
                if (0 != ToUI24(tagHeader, 8))
                    throw new InvalidDataException("Not a valid FLV file!.");
                // Data
                byte[] tagData = ReadBytes(stream, (int)dataSize + 4);

                lock (locker)
                {
                    if ((tagHeader[0] == TAGTYPE_VIDEO) && (1 == (tagData[0] & 0xF0) >> 4))
                    {
                        buffer.Clear();
                        bufferedTimestamp = timestamp;
                    }

                    if (tagHeader[0] == TAGTYPE_DATA)
                    {
                        scriptData.Add(tagHeader);
                        scriptData.Add(tagData);
                    }

                    buffer.Add(tagHeader);
                    buffer.Add(tagData);

                    foreach (FLVReader reader in readers)
                    {
                        // Update timestamp.
                        byte[] newTimestampValue = BitConverter.GetBytes(timestamp - reader.timestampDelta);
                        tagHeader[4] = newTimestampValue[2];
                        tagHeader[5] = newTimestampValue[1];
                        tagHeader[6] = newTimestampValue[0];

                        // Write tag.
                        reader.stream.Write(tagHeader, 0, tagHeader.Length);
                        reader.stream.Write(tagData, 0, tagData.Length);
                    }
                }
            }
        }

        protected override void Reset()
        {
            foreach (FLVReader reader in readers)
                reader.stream.Close();
            readers.Clear();
            buffer.Clear();
            bufferedTimestamp = 0;
            header = null;
        }

        private static byte[] ReadBytes(Stream stream, int bytesToRead)
        {
            byte[] result = new byte[bytesToRead];
            int bytesRead = 0;
            while (bytesToRead > 0)
            {
                int read = stream.Read(result, bytesRead, bytesToRead);
                if (read == 0)
                    throw new EndOfStreamException("End of stream reached.");
                bytesRead += read;
                bytesToRead -= read;
            }
            return result;
        }

        private static ushort ToUI16(byte[] value, int startIndex)
        {
            return (ushort)(value[startIndex] << 8 | value[startIndex + 1]);
        }

        private static uint ToUI24(byte[] value, int startIndex)
        {
            return (uint)(value[startIndex] << 16 | value[startIndex + 1] << 8 | value[startIndex + 2]);
        }

        private static uint ToUI32(byte[] value, int startIndex)
        {
            return (uint)(value[startIndex] << 24 | value[startIndex + 1] << 16 | value[startIndex + 2] << 8 | value[startIndex + 3]);
        }

        private class FLVReader
        {
            public Stream stream;
            public uint timestampDelta;

            public FLVReader(Stream stream, uint timestampDelta)
            {
                this.stream = stream;
                this.timestampDelta = timestampDelta;
            }
        }
    }
}
