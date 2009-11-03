using System;

namespace SoundStreaming.DirectSoundSender
{
    public class StreamingServiceCallback : IStreamingServiceCallback
    {
        public void DataCallback(byte[] data) { }

        public void SubscriptionResponse(byte[] response) { }
    }
}