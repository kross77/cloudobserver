using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace CloudObserver.Utils.FLVSlicer
{
    public class FLVSlicer
    {
        private Stream input;

        private byte[] header;
        public MemoryStream scriptTags = new MemoryStream();

        private List<FLVTag> frames = new List<FLVTag>();
        private List<FLVTag> keyFrames = new List<FLVTag>();
        
        private const byte AUDIO_TAG = 0x08;
        private const byte VIDEO_TAG = 0x09;
        private const byte SCRIPT_TAG = 0x12;
		private const int SECOND_TAG = 0xD;
		private const string SIGNATURE = "FLV";
		
		private const int SHORT = 0x3;
		private const string METADATA = "onMetaData";
		private const string DURATION = "duration";

        private const int BUFFER_SIZE = 8192;

        public FLVSlicer(Stream input)
        {
            if (!input.CanSeek)
                throw new ArgumentException("The stream must be seekable.");

            this.input = input;
            Init();
        }

        private void Init()
        {
            input.Position = 0;

            if (SIGNATURE != Encoding.UTF8.GetString(ReadBytes(input, SIGNATURE.Length), 0, SIGNATURE.Length))
                throw new InvalidDataException("Not a valid FLV file!.");

            int version = input.ReadByte();
            int infos = input.ReadByte();
            int typeFlagsReserved1 = (infos >> 3);
            int typeFlagsAudio = ((infos & 0x4) >> 2);
            int typeFlagsReserved2 = ((infos & 0x2) >> 1);
            int typeFlagsVideo = (infos & 0x1);
            uint dataOffset = ReadUInt32(input);
            input.Position += 4;

            int headerLength = (int)input.Position;
            header = new byte[headerLength];
            input.Position = 0;
            input.Read(header, 0, headerLength);
            scriptTags.Write(header, 0, headerLength);

            while (input.Position < input.Length)
            {
                long offset = input.Position;
                byte tagType = (byte)input.ReadByte();
                uint dataSize = ReadUInt24(input);
                uint timestamp = ReadUInt24(input);
                byte timestampExtended = (byte)input.ReadByte();
                uint streamID = ReadUInt24(input);
                int fb = input.ReadByte();
                long tagEnd = input.Position + dataSize + 3;
                long tagLength = tagEnd - offset;

                switch (tagType)
                {
                    case AUDIO_TAG:
                        int soundFormat = (fb & 0xF0) >> 4;
                        int soundRate = (fb & 0xC) >> 2;
                        int soundSize = (fb & 0x2) >> 1;
                        int soundType = (fb & 0x1);
                        break;
                    case VIDEO_TAG:
                        int keyframe = (fb & 0xF0) >> 4;
                        int codecID = (fb & 0xF0) >> 4;
                        FLVTag frameTag = new FLVTag(timestamp, offset);
                        if (keyframe == 1)
                            keyFrames.Add(frameTag);
                        frames.Add(frameTag);
                        break;
                    case SCRIPT_TAG:
                        CopyBytes(input, offset, tagLength, scriptTags);
                        break;
                }
                input.Position = tagEnd;
            }
        }

        private uint ReadUInt32(Stream stream)
        {
            return (uint)((stream.ReadByte() << 24) | (stream.ReadByte() << 16) | (stream.ReadByte() << 8) | stream.ReadByte());
        }

        private uint ReadUInt24(Stream stream)
        {
            return (uint)(stream.ReadByte() << 16 | stream.ReadByte() << 8 | stream.ReadByte());
        }

        private void WriteUInt24(Stream stream, uint value)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            stream.WriteByte(bytes[2]);
            stream.WriteByte(bytes[1]);
            stream.WriteByte(bytes[0]);
        }

        private ushort ReadUInt16(Stream stream)
        {
            return (ushort)(stream.ReadByte() << 8 | stream.ReadByte());
        }

        private byte[] ReadBytes(Stream stream, int length)
        {
            byte[] result = new byte[length];
            stream.Read(result, 0, length);
            return result;
        }

        private void CopyBytes(Stream input, long offset, long length, Stream output)
        {
            input.Position = offset;
            byte[] buffer = new byte[BUFFER_SIZE];
            do
            {
                int read = input.Read(buffer, 0, (length >= BUFFER_SIZE) ? BUFFER_SIZE : (int)length);
                output.Write(buffer, 0, read);
                length -= read;
            }
            while (length > 0);
        }

        public void GetAudio(Stream output)
        {
            output.Write(header, 0, header.Length);
            input.Position = SECOND_TAG;

            while (input.Position < input.Length)
            {
                long offset = input.Position;
                byte tagType = (byte)input.ReadByte();
                uint dataSize = ReadUInt24(input);
                uint timestamp = ReadUInt24(input);
                byte timestampExtended = (byte)input.ReadByte();
                uint streamID = ReadUInt24(input);
                int fb = input.ReadByte();
                long tagEnd = input.Position + dataSize + 3;
                long tagLength = tagEnd - offset;

                if ((tagType == AUDIO_TAG) || (tagType == SCRIPT_TAG))
                    CopyBytes(input, offset, tagLength, output);
                input.Position = tagEnd;
            }
        }

        public void GetVideo(Stream output)
        {
            output.Write(header, 0, header.Length);
            input.Position = SECOND_TAG;

            while (input.Position < input.Length)
            {
                long offset = input.Position;
                byte tagType = (byte)input.ReadByte();
                uint dataSize = ReadUInt24(input);
                uint timestamp = ReadUInt24(input);
                byte timestampExtended = (byte)input.ReadByte();
                uint streamID = ReadUInt24(input);
                int fb = input.ReadByte();
                long tagEnd = input.Position + dataSize + 3;
                long tagLength = tagEnd - offset;

                if ((tagType == VIDEO_TAG) || (tagType == SCRIPT_TAG))
                    CopyBytes(input, offset, tagLength, output);
                input.Position = tagEnd;
            }
        }

        public uint GetSlice(Stream output, uint startTimestamp, uint endTimestamp)
        {
            if (endTimestamp <= startTimestamp)
                throw new ArgumentException("End timing cannot be below or equal to starting time.");

            FLVTag startTag = FindTag(startTimestamp, true);
            FLVTag endTag = FindTag(endTimestamp, false);
            uint duration = endTag.Timestamp - startTag.Timestamp;
            UpdateMetaData(duration);

            CopyBytes(scriptTags, 0, scriptTags.Length, output);

            input.Position = startTag.Offset;
            while (input.Position < endTag.Offset)
            {
                long offset = input.Position;
                byte tagType = (byte)input.ReadByte();
                uint dataSize = ReadUInt24(input);
                uint timestamp = ReadUInt24(input) - startTag.Timestamp;
                byte timestampExtended = (byte)input.ReadByte();
                uint streamID = ReadUInt24(input);
                int fb = input.ReadByte();
                long tagEnd = input.Position + dataSize + 3;
                long tagLength = tagEnd - offset;

                if ((tagType == AUDIO_TAG) || (tagType == VIDEO_TAG))
                {
                    output.WriteByte(tagType);
                    WriteUInt24(output, dataSize);
                    WriteUInt24(output, timestamp);
                    CopyBytes(input, offset + 7, tagLength - 7, output);
                }
                input.Position = tagEnd;
            }
            return duration;
        }

        private void UpdateMetaData(uint duration)
        {
            long position = scriptTags.Position;
            scriptTags.Position = 25;

            ushort gap = ReadUInt16(scriptTags);
            string objectName = Encoding.UTF8.GetString(ReadBytes(scriptTags, gap));
            if (objectName == METADATA)
            {
                scriptTags.Position += 5;
                gap = ReadUInt16(scriptTags);
                objectName = Encoding.UTF8.GetString(ReadBytes(scriptTags, gap));
                if (objectName == DURATION)
                {
                    scriptTags.Position += 1;
                    byte[] temp = BitConverter.GetBytes((double)duration * 0.001);
                    Array.Reverse(temp);
                    scriptTags.Write(temp, 0, 8);
                }
                else throw new FormatException("Could not find duration field.");
            }
            else throw new FormatException("Could not find onMetaData tag.");
            scriptTags.Position = position;
        }

        private FLVTag FindTag(uint timing, bool seekable)
        {
            if (keyFrames.Count > 0)
            {
                FLVTag firstTag = keyFrames[0];
                FLVTag lastTag = keyFrames[keyFrames.Count - 1];

                if (seekable)
                    if (timing < firstTag.Timestamp)
                        return firstTag;

                if (timing > lastTag.Timestamp)
                    return lastTag;

                FLVTag previousItem = null;

                foreach (FLVTag item in seekable ? keyFrames : frames)
                {
                    if (previousItem != null)
                    {
                        if (previousItem.Timestamp <= timing && item.Timestamp >= timing)
                            return previousItem;
                    }
                    previousItem = item;
                }
            }
            else throw new Exception("Could not find any seekable frame as a starting point.");

            return null;
        }
    }
}
