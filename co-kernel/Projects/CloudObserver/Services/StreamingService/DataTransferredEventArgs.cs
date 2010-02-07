using System;

namespace CloudObserver.Services.StreamingService
{
    public class DataTransferredEventArgs : EventArgs
    {
        private int dataLength;

        public int DataLength { get { return dataLength; } }

        public DataTransferredEventArgs(int dataLength)
        {
            this.dataLength = dataLength;
        }
    }
}