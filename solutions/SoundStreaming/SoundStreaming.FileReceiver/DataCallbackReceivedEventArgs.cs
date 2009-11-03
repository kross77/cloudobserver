using System;

namespace SoundStreaming.FileReceiver
{
    public class DataCallbackReceivedEventArgs : EventArgs
    {
        public byte[] Data { get; private set; }

        public DataCallbackReceivedEventArgs(byte[] data)
        {
            Data = data;
        }
    }
}