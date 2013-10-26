using System;

namespace Transport.Interface
{
    public interface IOperationsPublisher
    {
        void Send(byte[] data, TimeSpan timeout, Action<byte[]> onResult, Action<string> onError);
    }
}