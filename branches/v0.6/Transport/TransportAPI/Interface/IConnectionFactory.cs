namespace Transport.Interface
{
    public interface IConnectionFactory
    {
        IConnection GetConnection(string address);
    }
}