using System;
using System.Collections.Generic;

namespace CloudObserverBroadcastServiceLibrary
{
    class ConnectedUser
    {
        private List<int> camerasList;
        private bool userChecked;
        private int userID;
        private string sessionID;

        public ConnectedUser(int UID, string SessionID)
        {
            sessionID = SessionID;
            userID = UID;
            userChecked = true;
            camerasList = new List<int>(5);
            //getUserCameras();
        }

        public void GetUserCameras(int cameraID) //must be for private using and without arguements!!!
        {
            //camerasList.Add();
            camerasList.Add(cameraID);
        }

        public bool IsUserChecked()
        {
            return userChecked;
        }

        public bool IsCameraAdded(int CameraID)
        {
            return (camerasList.Contains(CameraID));
        }
    }
}