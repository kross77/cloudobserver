using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    /// <summary>
    /// A binding derived from a System.ServiceModel.NetTcpBinding used to communicate between services in cloud.
    /// </summary>
    public class InternalNetTcpBinding : NetTcpBinding
    {
        private const int maxReceivedMessageSize = 2147483647; // 2 GB
        private const int maxArrayLength = 2147483647; // 2 GB

        /// <summary>
        /// Initializes a new instance of the CloudObserver.Services.InternalNetTcpBinding class.
        /// </summary>
        public InternalNetTcpBinding()
        {
            this.MaxReceivedMessageSize = maxReceivedMessageSize;
            this.OpenTimeout = TimeSpan.FromSeconds(30);
            this.CloseTimeout = TimeSpan.FromSeconds(30);
            this.ReceiveTimeout = TimeSpan.FromSeconds(30);
            this.SendTimeout = TimeSpan.FromSeconds(30);
            this.ReaderQuotas.MaxArrayLength = maxArrayLength;
        }
    }
}