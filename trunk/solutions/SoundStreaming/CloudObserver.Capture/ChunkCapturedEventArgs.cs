using System;

namespace CloudObserver.Capture
{
    public class ChunkCapturedEventArgs : EventArgs
    {
        private byte[] chunkData;

        public byte[] ChunkData { get { return chunkData; } }

        public ChunkCapturedEventArgs(byte[] chunkData)
        {
            this.chunkData = chunkData;
        }
    }
}