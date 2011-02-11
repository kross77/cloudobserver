using System.Collections;

namespace CloudObserver
{
    public struct HttpRequestStruct
    {
        public string method;
        public string url;
        public string version;
        public Hashtable arguments;
        public bool execute;
        public Hashtable headers;
        public int bodySize;
        public byte[] bodyData;
    }
}
