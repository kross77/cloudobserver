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
            hasNewFrame = true;
        }
    }

    public class ConnectedUser
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

        public void getUserCameras(int cameraID) //must be for private using and without arguements!!!
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
    public class CloudObserverBroadcastService : ICloudObserverBroadcastService,IDisposable
    {

        private Dictionary<string,CameraDescription> SessionIDtoCameraDescription;
        private Dictionary<int,string> CameraIDtoSessionID;
        private Dictionary<string,ConnectedUser> SessionIDtoConnectedUser;

        public CloudObserverBroadcastService()
        {
            SessionIDtoCameraDescription = new Dictionary<string,CameraDescription>();
            CameraIDtoSessionID = new Dictionary<int,string>();
            SessionIDtoConnectedUser = new Dictionary<string,ConnectedUser>();
        }

        public void bindMeToCamera(int clientID, int cameraID, int ident)
        {
            //string currentSessionID = OperationContext.Current.SessionId;
            string currentSessionID = ident.ToString();
            ConnectedUser connectingUser = new ConnectedUser(clientID, currentSessionID);
            if (connectingUser.IsUserChecked() && CameraIDtoSessionID.ContainsKey(cameraID))
            {
                connectingUser.getUserCameras(cameraID);//must be deleted
                SessionIDtoConnectedUser.Add(currentSessionID, connectingUser);
            }
            if (CameraIDtoSessionID.ContainsKey(cameraID))
            {
                //add him this camera.. at all - check service login and security logic
            }
        }

        public void setMeAsCamera(int cameraID, int ident)
        {
            //string currentSessionId = OperationContext.Current.SessionId;
            string currentSessionID = ident.ToString();
            CloudObserverBroadcastServiceLibrary.CameraDescription newCamera;
            newCamera = new CameraDescription(cameraID, currentSessionID);
            SessionIDtoCameraDescription.Add(currentSessionID, newCamera);
            CameraIDtoSessionID.Add(cameraID, currentSessionID);
        }

        public byte[] getNextFrame(int cameraID, int ident)
        {
            //string currentSessionID = OperationContext.Current.SessionId;
            string currentSessionID = ident.ToString();
            if (SessionIDtoConnectedUser.ContainsKey(currentSessionID))
            {
                string cameraSession = CameraIDtoSessionID[cameraID];
                return SessionIDtoCameraDescription[cameraSession].getFrame();
            }
            return (null);
        }

        public void setNextFrame(byte[] frame, int ident)
        {
            //string currentSessionID = OperationContext.Current.SessionId;
            //string currentSessionID = ident.ToString();
            //if (SessionIDtoCameraDescription.ContainsKey(currentSessionID))
            //{
            //    CameraDescription camera = SessionIDtoCameraDescription[currentSessionID];
            //    camera.setNewFrame(frame);
            //}
        }

        public void clean()
        {
            SessionIDtoCameraDescription.Clear();
            CameraIDtoSessionID.Clear();
            SessionIDtoConnectedUser.Clear();
        }

        public void Dispose()
        {

        }
    }
}
