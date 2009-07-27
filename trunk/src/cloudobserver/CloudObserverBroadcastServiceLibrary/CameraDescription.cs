using System;

namespace CloudObserverBroadcastServiceLibrary
{
    class CameraDescription
    {
        private int cameraID;
        private string sessionID;
        private bool hasNewFrame;
        private byte[] frame;

        public CameraDescription(int CID, string SID)
        {
            cameraID = CID;
            sessionID = SID;
            hasNewFrame = false;
        }

        public byte[] GetFrame()
        {
            return frame;
        }

        public void SetNewFrame(byte[] newFrame)
        {
            frame = newFrame;
            hasNewFrame = true;
        }
    }
}