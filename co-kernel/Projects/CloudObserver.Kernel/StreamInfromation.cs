namespace CloudObserver.Kernel
{
    public struct StreamInformation
    {
        private string address;
        public string Address { get { return address; } }

        private string contentType;
        public string ContentType { get { return contentType; } }

        public StreamInformation(string address, string contentType)
        {
            this.address = address;
            this.contentType = contentType;
        }
    }
}
