using System;

namespace CloudObserver.Services
{
    public abstract class IPCamera
    {
        public abstract void SetSource(string sourceUri);
        public abstract void SetFPSLimit(int fpsLimit);
        public abstract void SetCredentials(string userName, string password);
        public abstract void StartBroadcasting();
        public abstract void StopBroadcasting();
        public abstract int GetFramesCounter();
    }
}