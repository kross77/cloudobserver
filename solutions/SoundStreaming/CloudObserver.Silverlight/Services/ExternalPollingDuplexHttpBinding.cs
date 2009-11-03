using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    public class ExternalPollingDuplexHttpBinding : PollingDuplexHttpBinding
    {
        private const int maxReceivedMessageSize = 2147483647;
        private const int maxBufferSize = 2147483647;

        public ExternalPollingDuplexHttpBinding()
        {
            this.MaxReceivedMessageSize = maxReceivedMessageSize;
            this.MaxBufferSize = maxBufferSize;
            this.OpenTimeout = TimeSpan.FromMinutes(5);
            this.CloseTimeout = TimeSpan.FromMinutes(5);
            this.ReceiveTimeout = TimeSpan.FromMinutes(30);
            this.SendTimeout = TimeSpan.FromMinutes(30);
        }
    }
}