using System.IO;

namespace CloudObserver
{
    public class FLVReader
    {
        public Stream stream;
        public FileStream dumpStream;
        public uint timestampDelta;

        public FLVReader(Stream stream, FileStream dumpStream, uint timestampDelta)
        {
            this.stream = stream;
            this.dumpStream = dumpStream;
            this.timestampDelta = timestampDelta;
        }
    }
}
