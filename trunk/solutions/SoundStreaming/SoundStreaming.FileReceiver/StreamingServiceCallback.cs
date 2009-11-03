using System;

namespace SoundStreaming.FileReceiver
{
    public class StreamingServiceCallback : IStreamingServiceCallback
    {
        public event EventHandler<DataCallbackReceivedEventArgs> DataCallbackReceived;
        public event EventHandler<SubscriptionResponseReceivedEventArgs> SubscriptionResponseReceived;

        public void DataCallback(byte[] data)
        {
            DataCallbackReceived.Invoke(this, new DataCallbackReceivedEventArgs(data));
        }

        public void SubscriptionResponse(byte[] response)
        {
            SubscriptionResponseReceived.Invoke(this, new SubscriptionResponseReceivedEventArgs(response));
        }
    }
}