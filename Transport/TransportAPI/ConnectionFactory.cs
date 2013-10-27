using Transport.Implementation;
using Transport.Interface;

namespace Transport
{
    public class ConnectionFactory : IConnectionFactory
    {
        public IConnection GetConnection(string address)
        {
            return new Connection();
        }
    }
}