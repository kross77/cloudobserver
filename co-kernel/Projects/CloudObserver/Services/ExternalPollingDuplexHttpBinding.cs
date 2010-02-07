using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    /// <summary>
    /// A binding derived from a System.ServiceModel.PollingDuplexHttpBinding used to communicate between services and Silverlight applications.
    /// </summary>
    public class ExternalPollingDuplexHttpBinding : PollingDuplexHttpBinding
    {
        private const int maxReceivedMessageSize = 2147483647; // 2 GB
        private const int maxArrayLength = 2147483647; // 2 GB

        /// <summary>
        /// Initializes a new instance of the CloudObserver.Services.ExternalPollingDuplexHttpBinding class.
        /// </summary>
        public ExternalPollingDuplexHttpBinding()
        {
            this.BypassProxyOnLocal = true;
            this.MaxReceivedMessageSize = maxReceivedMessageSize;
            this.OpenTimeout = TimeSpan.FromSeconds(30);
            this.CloseTimeout = TimeSpan.FromSeconds(30);
            this.ReceiveTimeout = TimeSpan.FromSeconds(30);
            this.SendTimeout = TimeSpan.FromSeconds(30);
            this.ReaderQuotas.MaxArrayLength = maxArrayLength;
        }
    }
}