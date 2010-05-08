using System;

namespace CloudObserver.Clients.Auxiliaries.Capture
{
    /// <summary>
    /// Provides data for the CloudObserver.Capture.ICapture.ChunkCaptured event. Containts captured chunk of data.
    /// </summary>
    public class ChunkCapturedEventArgs : EventArgs
    {
        private byte[] chunkData;

        /// <summary>
        /// Captured chunk of data.
        /// </summary>
        public byte[] ChunkData { get { return chunkData; } }

        /// <summary>
        /// Initializes a new instance of the CloudObserver.Capture.ChunkCapturedEventArgs class.
        /// </summary>
        /// <param name="chunkData">Captured chunk of data.</param>
        public ChunkCapturedEventArgs(byte[] chunkData)
        {
            this.chunkData = chunkData;
        }
    }
}
