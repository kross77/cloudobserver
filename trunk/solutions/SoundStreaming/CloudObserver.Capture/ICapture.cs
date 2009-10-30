using System;

namespace CloudObserver.Capture
{
    public interface ICapture
    {
        event EventHandler<ChunkCapturedEventArgs> ChunkCaptured;

        void Start();
        void Stop();
    }
}