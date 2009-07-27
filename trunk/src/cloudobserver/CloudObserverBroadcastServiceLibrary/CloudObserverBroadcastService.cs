using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserverBroadcastServiceLibrary
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudObserverBroadcastService : ICloudObserverBroadcastService
    {
        private Dictionary<string, CameraDescription> SessionIDtoCameraDescription;
        private Dictionary<int, string> CameraIDtoSessionID;
        private Dictionary<string, ConnectedUser> SessionIDtoConnectedUser;

        public CloudObserverBroadcastService()
        {
            SessionIDtoCameraDescription = new Dictionary<string, CameraDescription>();
            CameraIDtoSessionID = new Dictionary<int, string>();
            SessionIDtoConnectedUser = new Dictionary<string, ConnectedUser>();
        }

        public void BindMeToCamera(int clientID, int cameraID)
        {
            string currentSession = OperationContext.Current.SessionId;
            ConnectedUser connectingUser = new ConnectedUser(clientID, currentSession);
            if (connectingUser.IsUserChecked() && CameraIDtoSessionID.ContainsKey(cameraID))
            {
                connectingUser.GetUserCameras(cameraID);//must be deleted
                SessionIDtoConnectedUser.Add(currentSession, connectingUser);
            }
            if (CameraIDtoSessionID.ContainsKey(cameraID))
            {
                //add him this camera.. at all - check service login and security logic
            }
        }

        public void SetMeAsCamera(int cameraID)
        {
            string currentSessionId = OperationContext.Current.SessionId;
            CloudObserverBroadcastServiceLibrary.CameraDescription newCamera;
            newCamera = new CameraDescription(cameraID, currentSessionId);
            SessionIDtoCameraDescription.Add(currentSessionId, newCamera);
            CameraIDtoSessionID.Add(cameraID, currentSessionId);
        }

        public byte[] GetNextFrame(int cameraID)
        {
            string currentSessionID = OperationContext.Current.SessionId;
            if (SessionIDtoConnectedUser.ContainsKey(currentSessionID))
            {
                string cameraSession = CameraIDtoSessionID[cameraID];
                return SessionIDtoCameraDescription[cameraSession].GetFrame();
            }
            return (null);
        }

        public void SetNextFrame(byte[] frame)
        {
            string currentSessionID = OperationContext.Current.SessionId;
            if (SessionIDtoCameraDescription.ContainsKey(currentSessionID))
            {
                CameraDescription camera = SessionIDtoCameraDescription[currentSessionID];
                camera.SetNewFrame(frame);
            }
        }
    }
}