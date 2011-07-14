using System.Collections;
using System.IO;

namespace CloudObserver
{
    public struct HttpResponseStruct
    {
        public int status;
        public string version;
        public Hashtable headers;
        public long bodySize;
        public byte[] bodyData;
        public FileStream fileStream;
    }
}
