namespace Transport.Interface
{
    public interface IEventsPublisher
    {
        void Send(byte[] data);
    }
}