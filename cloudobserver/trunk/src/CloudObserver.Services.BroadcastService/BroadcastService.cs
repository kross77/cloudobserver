using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class BroadcastService : AbstractService, BroadcastServiceContract
    {
        Dictionary<int, byte[]> frames;

        public BroadcastService()
        {
            frames = new Dictionary<int, byte[]>();
        }

        public byte[] ReadFrame(int cameraID)
        {
            if (frames.ContainsKey(cameraID))
                return frames[cameraID];
            else
                return Properties.Resources.NoImageFrame;
        }

        public void WriteFrame(int cameraID, byte[] frame)
        {
            frames[cameraID] = frame;
        }
    }
}