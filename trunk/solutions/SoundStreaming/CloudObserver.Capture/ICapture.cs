using System;

namespace CloudObserver.Capture
{
    /// <summary>
    /// Interface of a type which represents some capture class (e.g. DirectSound or DirectShow captures).
    /// </summary>
    public interface ICapture
    {
        /// <summary>
        /// Occurs when the new chunk of data has been captured.
        /// </summary>
        event EventHandler<ChunkCapturedEventArgs> ChunkCaptured;

        /// <summary>
        /// Starts capturing.
        /// </summary>
        void Start();

        /// <summary>
        /// Stops capturing.
        /// </summary>
        void Stop();
    }
}