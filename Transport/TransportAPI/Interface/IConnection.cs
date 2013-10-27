using System;

namespace Transport.Interface
{
    public delegate void Response(byte[] data);

    public interface IConnectionFactory
    {
        IConnection GetConnection(string address);
    }

    public interface IConnection
    {
        void SubscribeToOperations(string topic, Action<byte[], Response> callback);    
        void SubscribeToEvents(string topic, Action<byte[]> callback);

        void UnSubscribeToOperations(string topic);
        void UnSubscribeToEvents(string topic);

        IOperationsPublisher GetOperationsPublisher(string topic);
        IEventsPublisher GetEventsPublisher(string topic);
    }
}