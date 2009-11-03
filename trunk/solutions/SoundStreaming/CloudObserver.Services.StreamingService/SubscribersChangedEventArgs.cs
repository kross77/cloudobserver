using System;

namespace CloudObserver.Services.StreamingService
{
    public class SubscribersChangedEventArgs : EventArgs
    {
        private int subscribers;

        public int Subscribers { get { return subscribers; } }

        public SubscribersChangedEventArgs(int subscribers)
        {
            this.subscribers = subscribers;
        }
    }
}