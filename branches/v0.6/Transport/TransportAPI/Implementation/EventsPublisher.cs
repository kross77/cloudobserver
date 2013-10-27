using System;
using Transport.Interface;

namespace Transport.Implementation
{
    internal class EventsPublisher : IEventsPublisher
    {
        public void Send(byte[] data)
        {
            throw new NotImplementedException();
        }
    }
}