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

        public void BindMeToCamera(int clientID, int cameraID, string UID)
        {
            string currentSession = UID;
            //string currentSession = OperationContext.Current.SessionId;
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

        public void SetMeAsCamera(int cameraID, string UID)
        {
            string currentSession = UID;
            //string currentSession = OperationContext.Current.SessionId;
            CloudObserverBroadcastServiceLibrary.CameraDescription newCamera;
            newCamera = new CameraDescription(cameraID, currentSession);
            SessionIDtoCameraDescription.Add(currentSession, newCamera);
            CameraIDtoSessionID.Add(cameraID, currentSession);
        }

        public byte[] GetNextFrame(int cameraID, string UID)
        {
            string currentSession = UID;
            //string currentSession = OperationContext.Current.SessionId;
            if (SessionIDtoConnectedUser.ContainsKey(currentSession))
            {
                string cameraSession = CameraIDtoSessionID[cameraID];
                return SessionIDtoCameraDescription[cameraSession].GetFrame();
            }
            return (null);
        }

        public void SetNextFrame(byte[] frame,string UID)
        {
            string currentSession = UID;
            //string currentSession = OperationContext.Current.SessionId;
            if (SessionIDtoCameraDescription.ContainsKey(currentSession))
            {
                CameraDescription camera = SessionIDtoCameraDescription[currentSession];
                camera.SetNewFrame(frame);
            }
        }
    }
}