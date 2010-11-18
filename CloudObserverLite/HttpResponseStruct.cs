using System.Collections;
using System.IO;

namespace CloudObserverLite
{
    public struct HttpResponseStruct
    {
        public int status;
        public string version;
        public Hashtable headers;
        public int BodySize;
        public byte[] bodyData;
        public FileStream fileStream;
    }
}
