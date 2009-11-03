using System;

namespace SoundStreaming.FileSender
{
    public class StreamingServiceCallback : IStreamingServiceCallback
    {
        public void DataCallback(byte[] data) { }

        public void SubscriptionResponse(byte[] response) { }
    }
}