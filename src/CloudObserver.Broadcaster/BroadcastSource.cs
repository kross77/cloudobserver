using System;

namespace CloudObserver.Broadcaster
{
    public class BroadcastSource
    {
        private BroadcastSourceType broadcastSourceType;

        private string[] frames;
        public string[] Frames
        {
            get { return frames; }
        }

        private int retransmissionCameraID;
        public int RetransmissionCameraID
        {
            get { return retransmissionCameraID; }
        }

        private bool actualRetransmission;
        public bool ActualRetransmission
        {
            get { return actualRetransmission; }
        }

        private string uri;
        public string Uri
        {
            get { return uri; }
        }

        private bool provideCredentials;
        public bool ProvideCredentials
        {
            get { return provideCredentials; }
        }

        private string userName;
        public string UserName
        {
            get { return userName; }
        }

        private string password;
        public string Password
        {
            get { return password; }
        }

        public BroadcastSource(string[] files)
        {
            broadcastSourceType = BroadcastSourceType.LocalStorage;
            this.frames = files;
        }

        public BroadcastSource(int retransmissionCameraID, bool actualRetransmission)
        {
            broadcastSourceType = BroadcastSourceType.CloudObserverCamera;
            this.retransmissionCameraID = retransmissionCameraID;
            this.actualRetransmission = actualRetransmission;
        }

        public BroadcastSource(string uri, bool provideCredentials, string userName, string password)
        {
            broadcastSourceType = BroadcastSourceType.IPCamera;
            this.uri = uri;
            this.provideCredentials = provideCredentials;
            this.userName = userName;
            this.password = password;
        }

        public BroadcastSourceType GetBroadcastSourceType()
        {
            return broadcastSourceType;
        }

        public override string ToString()
        {
            switch (broadcastSourceType)
            {
                case BroadcastSourceType.LocalStorage:
                    return "LocalStorage";
                case BroadcastSourceType.CloudObserverCamera:
                    return "CloudObserverCamera";
                case BroadcastSourceType.IPCamera:
                    return "IPCamera";
                default:
                    return base.ToString();
            }
        }
    }
}