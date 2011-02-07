using System;
using System.Net;
using System.Timers;
using System.Collections.Generic;
using System.ServiceModel;
using CloudObserverBroadcastServiceLibrary;

namespace CloudObserverVirtualCamerasServiceLibrary
{
     abstract class VirtualCamera
    {
         public abstract void StartBroadcasting();
         public abstract void StopBroadcasting();
         public abstract int GetFramesCounter();
         public abstract void SetFPS(int fps);
         public abstract void SetCredentials(string userName, string password);
         public abstract void SetSource(string source);
    }
}