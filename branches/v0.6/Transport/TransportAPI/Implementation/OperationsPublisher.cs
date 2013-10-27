using System;
using Transport.Interface;

namespace Transport.Implementation
{
    internal class OperationsPublisher :IOperationsPublisher
    {
        public void Send(byte[] data, TimeSpan timeout, Action<byte[]> onResult, Action<string> onError)
        {
            throw new NotImplementedException();
        }

    }
}