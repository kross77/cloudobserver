using System;

namespace Multimedia
{
    public class ConnectionsUpdatedEventArgs : EventArgs
    {
        private int connections;

        public int Connections
        {
            get { return this.connections; }
        }

        public ConnectionsUpdatedEventArgs(int connections)
        {
            this.connections = connections;
        }
    }
}