using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Collections;

namespace CloudObserverBroadcastServiceLibrary
{
    public class CameraDescription
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

        public byte[] getFrame()
        {
            return frame;
        }

        public void setNewFrame(byte[] newFrame)
        {
            frame = newFrame;
        }
    }

    private class ConnectedUser
    {
        private List<int> CamerasList;
        private bool userChecked;
        private int userID;
        private string sessionID;

        public ConnectedUser(int UID, string SessionID)
        {
            sessionID = SessionID;
            userID = UID;
            userChecked = true;
            CamerasList = new List<int>(5);
            //getUserCameras();
        }

        public void getUserCameras(int cameraID) //must be for private using and without erguements!!!
        {
            //CamerasList.Add();
            CamerasList.Add(cameraID);
        }

        public bool IsUserChecked()
        {
            return userChecked;
        }

        public bool IsCameraAdded(int CameraID)
        {
            return(CamerasList.Contains(CameraID));
        }
    }

    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudObserverBroadcastServer : ICloudObserverBroadcastServer,IDisposable
    {

        private Dictionary<string,CameraDescription> SessionIDtoCameraDescription;
        private Dictionary<int,string> CameraIDtoSessionID;
        private Dictionary<string,ConnectedUser> SessionIDtoConnectedUser;

        CloudObserverBroadcastServer()
        {
            SessionIDtoCameraDescription = new Dictionary<string,CameraDescription>();
            CameraIDtoSessionID = new Dictionary<int,string>();
            SessionIDtoConnectedUser = new Dictionary<string,ConnectedUser>();
        }

        void bindMeToCamera(int clientID, int cameraID)
        {
            string currentSession = OperationContext.Current.SessionId;
            ConnectedUser connectingUser = new ConnectedUser(clientID, currentSession);
            if (connectingUser.IsUserChecked() && CameraIDtoSessionID.ContainsKey(cameraID))
            {
                connectingUser.getUserCameras(cameraID);//must be deleted
                SessionIDtoConnectedUser.Add(currentSession, connectingUser);
            }
            if (CameraIDtoSessionID.ContainsKey(cameraID))
            {
                //add him this camera.. at all - check service login and security logic
            }
        }

        void setMeAsCamera(int cameraID)
        {
            string currentSessionId = OperationContext.Current.SessionId;
            CloudObserverBroadcastServiceLibrary.CameraDescription newCamera;
            newCamera = new CameraDescription( cameraID,currentSessionId);
            SessionIDtoCameraDescription.Add(currentSessionId,newCamera);
            CameraIDtoSessionID.Add(cameraID,currentSessionId);
        }

        byte[] getNextFrame(int cameraID)
        {
            string currentSessionID = OperationContext.Current.SessionId;
            if (SessionIDtoConnectedUser.ContainsKey(currentSessionID))
            {
                string cameraSession = CameraIDtoSessionID[cameraID];
                return SessionIDtoCameraDescription[cameraSession].getFrame();
            }
            return (null);
        }

        void setNextFrame(byte[] frame)
        {
            string currentSessionID = OperationContext.Current.SessionId;
            if (SessionIDtoCameraDescription.ContainsKey(currentSessionID))
            {
                CameraDescription camera = SessionIDtoCameraDescription[currentSessionID];
                camera.setNewFrame(frame);
            }
        }
    }
}
