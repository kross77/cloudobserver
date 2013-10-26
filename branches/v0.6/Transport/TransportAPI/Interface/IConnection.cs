using System;

namespace Transport.Interface
{
    public interface IConnection
    {
        void Connect(string address);

        void SubscribeToOperations(string topic, Action<byte[]> callback);
        void SubscribeToEvents(string topic, Action<byte[]> callback);

        IOperationsPublisher GetOperationsPublisher(string topic);
        IEventsPublisher GetEventsPublisher(string topic);
    }
}