﻿using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    public class InternalNetTcpBinding : NetTcpBinding
    {
        private const int maxReceivedMessageSize = 2147483647;
        private const int maxArrayLength = 2147483647;

        public InternalNetTcpBinding()
        {
            this.MaxReceivedMessageSize = maxReceivedMessageSize;
            this.OpenTimeout = TimeSpan.FromMinutes(5);
            this.CloseTimeout = TimeSpan.FromMinutes(5);
            this.ReceiveTimeout = TimeSpan.FromMinutes(30);
            this.SendTimeout = TimeSpan.FromMinutes(30);
            this.ReaderQuotas.MaxArrayLength = maxArrayLength;
        }
    }
}