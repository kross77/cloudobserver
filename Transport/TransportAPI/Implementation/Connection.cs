using System;
using Transport.Interface;

namespace Transport.Implementation
{
    internal class Connection : IConnection
    {
        public void SubscribeToOperations(string topic, OperationCallback callback)
        {
            throw new NotImplementedException();
        }

        public void SubscribeToEvents(string topic, EventCallback callback)
        {
            throw new NotImplementedException();
        }

        public void UnSubscribeToOperations(string topic)
        {
            throw new NotImplementedException();
        }

        public void UnSubscribeToEvents(string topic)
        {
            throw new NotImplementedException();
        }

        public IOperationsPublisher GetOperationsPublisher(string topic)
        {
            return new OperationsPublisher();
        }

        public IEventsPublisher GetEventsPublisher(string topic)
        {
            return new EventsPublisher();
        }
    }
}