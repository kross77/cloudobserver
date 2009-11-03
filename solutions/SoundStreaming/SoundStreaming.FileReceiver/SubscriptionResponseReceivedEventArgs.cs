using System;

namespace SoundStreaming.FileReceiver
{
    public class SubscriptionResponseReceivedEventArgs : EventArgs
    {
        public byte[] Response { get; private set; }

        public SubscriptionResponseReceivedEventArgs(byte[] response)
        {
            Response = response;
        }
    }
}