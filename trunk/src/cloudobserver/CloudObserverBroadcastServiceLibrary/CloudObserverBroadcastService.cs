using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserverBroadcastServiceLibrary
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudObserverBroadcastService : ICloudObserverBroadcastService
    {
        Dictionary<int, byte[]> frames;

        public CloudObserverBroadcastService()
        {
            frames = new Dictionary<int, byte[]>();
        }

        public byte[] ReadFrame(int cameraID)
        {
            return frames[cameraID];
        }

        public void WriteFrame(int cameraID, byte[] frame)
        {
            frames[cameraID] = frame;
        }
    }
}